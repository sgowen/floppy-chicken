//
//  ViewController.mm
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#define ACH_BRONZE @"CgkI-POVnfYIEAIQAw"
#define ACH_SILVER @"CgkI-POVnfYIEAIQBA"
#define ACH_GOLD @"CgkI-POVnfYIEAIQBQ"
#define ACH_PLATINUM @"CgkI-POVnfYIEAIQBg"
#define ACH_GRAND_POOBAH @"CgkI-POVnfYIEAIQBw"
#define LEAD_FLOPPY_CHICKEN @"CgkI-POVnfYIEAIQAA"

#import "ViewController.h"
#include "game.h"
#include "Assets.h"
#include "Music.h"
#include "Sound.h"
#include "AppPrefs.h"

@interface ViewController ()
{
    bool isAttemptingToSubmitAndOrViewLeaderboard;
}

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) Sound *flapSound;
@property (strong, nonatomic) Sound *scoreSound;
@property (strong, nonatomic) Sound *hitSound;
@property (strong, nonatomic) Sound *landSound;
@property (assign, nonatomic) BOOL bannerIsVisible;

- (void)setupGL;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    isAttemptingToSubmitAndOrViewLeaderboard = false;
    
    [self.adBannerView setDelegate:self];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    
    if (!self.context)
    {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    view.userInteractionEnabled = YES;
    
    [self setupGL];
    
    self.flapSound = [[Sound alloc] initWithSoundNamed:@"flap.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:3];
    self.scoreSound = [[Sound alloc] initWithSoundNamed:@"score.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:2];
    self.hitSound = [[Sound alloc] initWithSoundNamed:@"hit.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    self.landSound = [[Sound alloc] initWithSoundNamed:@"land.caf" fromBundle:[NSBundle mainBundle] andMaxNumOfSimultaneousPlays:1];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onPause)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onResume)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    
    GPPSignIn *signIn = [GPPSignIn sharedInstance];
    signIn.clientID = @"306614467064-tbdcq6edatic68fgeopvqdbeoglm1u2c.apps.googleusercontent.com";
    signIn.scopes = [NSArray arrayWithObjects:
                     @"https://www.googleapis.com/auth/games",
                     @"https://www.googleapis.com/auth/appstate",
                     nil];
    signIn.language = [[NSLocale preferredLanguages] objectAtIndex:0];
    signIn.delegate = self;
    signIn.shouldFetchGoogleUserID = YES;
    
//    [signIn trySilentAuthentication];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_down(pos.x, pos.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_dragged(pos.x, pos.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [touches anyObject];
    CGPoint pos = [touch locationInView: [UIApplication sharedApplication].keyWindow];
    on_touch_up(pos.x, pos.y);
}

#pragma <ADBannerViewDelegate> methods

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    if (!self.bannerIsVisible)
    {
        [UIView beginAnimations:@"animateAdBannerOn" context:NULL];
        
        // Assumes the banner view is just off the top of the screen.
        
        banner.frame = CGRectOffset(banner.frame, 0, banner.frame.size.height);
        
        [UIView commitAnimations];
        
        self.bannerIsVisible = YES;
    }
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    if (self.bannerIsVisible)
    {
        [UIView beginAnimations:@"animateAdBannerOff" context:NULL];
        
        // Assumes the banner view is placed at the top of the screen.
        
        banner.frame = CGRectOffset(banner.frame, 0, -banner.frame.size.height);
        
        [UIView commitAnimations];
        
        self.bannerIsVisible = NO;
    }
}

#pragma GLKView and GLKViewController delegate methods

- (void)update
{
    int gameState = get_state();
    switch (gameState)
    {
        case 0:
            update(self.timeSinceLastUpdate);
            break;
        case 1:
            init();
            break;
        case 2:
            [self dismissViewControllerAnimated:true completion:nil];
            break;
        case 3:
            clear_state();
            [self handleFinalScore];
            break;
        case 4:
            clear_state();
            [self submitBestScoreToLeaderboard];
            break;
        default:
            break;
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    present();
    [self handleSoundId:get_current_sound_id()];
}

#pragma <GPPSignInDelegate> methods

- (void)finishedWithAuth:(GTMOAuth2Authentication *)auth error:(NSError *)error
{
    NSLog(@"Finished with auth.");
    if (error == nil && auth)
    {
        NSLog(@"Success signing in to Google! Auth object is %@", auth);
        
        [[GPGManager sharedInstance] signIn:[GPPSignIn sharedInstance] reauthorizeHandler:^(BOOL requiresKeychainWipe, NSError *error)
         {
             // If you hit this, auth has failed and you need to authenticate.
             // Most likely you can refresh behind the scenes
             if (requiresKeychainWipe)
             {
                 [[GPPSignIn sharedInstance] signOut];
             }
             
             [[GPPSignIn sharedInstance] authenticate];
         }];
        
        if(isAttemptingToSubmitAndOrViewLeaderboard)
        {
            isAttemptingToSubmitAndOrViewLeaderboard = false;
            [self submitBestScoreToLeaderboard];
        }
    }
    else
    {
        NSLog(@"Failed to log into Google\n\tError=%@\n\tAuthObj=%@",error,auth);
    }
}

#pragma <GPGLeaderboardControllerDelegate> methods

- (void)leaderboardViewControllerDidFinish: (GPGLeaderboardController *)viewController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

#pragma private methods

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    self.preferredFramesPerSecond = 60;
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    
    CGSize newSize = CGSizeMake(screenSize.width, screenSize.height);
    newSize.width = roundf(newSize.width);
	newSize.height = roundf(newSize.height);
    
    NSLog(@"dimension %f x %f", newSize.width, newSize.height);
    
    init();
    on_surface_created(newSize.width, newSize.height);
    on_surface_changed(newSize.width, newSize.height, [UIScreen mainScreen].applicationFrame.size.width, [UIScreen mainScreen].applicationFrame.size.height);
    on_resume();
}

- (void)handleSoundId:(short)soundId
{
    switch (soundId)
    {
        case FLAP_SOUND:
            [self.flapSound play];
            break;
        case SCORE_SOUND:
            [self.scoreSound play];
            break;
        case HIT_SOUND:
            [self.hitSound play];
            break;
        case LAND_SOUND:
            [self.landSound play];
            break;
        default:
            break;
    }
}

- (void)handleFinalScore
{
    int score = get_score();
    int bestScore = [[AppPrefs getInstance] getBestScore];
    if(score > bestScore)
    {
        [[AppPrefs getInstance] setBestScore:score];
    }
    set_best_score([[AppPrefs getInstance] getBestScore]);
}

- (void)submitBestScoreToLeaderboard
{
    BOOL isSignedIn = [[GPGManager sharedInstance] hasAuthorizer];
    if(isSignedIn)
    {
        GPGScore *myScore = [[GPGScore alloc] initWithLeaderboardId:LEAD_FLOPPY_CHICKEN];
        myScore.value = [[AppPrefs getInstance] getBestScore];
        
        [myScore submitScoreWithCompletionHandler: ^(GPGScoreReport *report, NSError *error)
         {
             if (error)
             {
                 NSLog(@"Got an Error: %@", [error description]);
             }
             else
             {
                 NSLog(@"Report Description: %@", [report description]);
             }
             
             GPGLeaderboardController *leadController = [[GPGLeaderboardController alloc] initWithLeaderboardId:LEAD_FLOPPY_CHICKEN];
             leadController.leaderboardDelegate = self;
             [self presentViewController:leadController animated:YES completion:nil];
         }];
    }
    else
    {
        isAttemptingToSubmitAndOrViewLeaderboard = true;
        [[GPPSignIn sharedInstance] authenticate];
    }
}

- (void)onResume
{
    on_resume();
}

- (void)onPause
{
    on_pause();
}

@end