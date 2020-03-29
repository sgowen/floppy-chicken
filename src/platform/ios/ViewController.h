//
//  ViewController.h
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "iAd/ADBannerView.h"
#import <GooglePlus/GooglePlus.h>

@interface ViewController : GLKViewController <ADBannerViewDelegate, GPPSignInDelegate, GPGLeaderboardControllerDelegate>
{
    // Nothing to do here
}

@property (strong, nonatomic) IBOutlet ADBannerView *adBannerView;

@end