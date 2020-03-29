//
//  Renderer.h
//  floppycock
//
//  Created by Stephen Gowen on 2/13/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__Renderer__
#define __floppycock__Renderer__

#define TAP_TO_FLOP_X SCREEN_WIDTH / 8 * 3 + 3.5f
#define TAP_TO_FLOP_Y SCREEN_HEIGHT / 2 + 2.5f
#define TAP_TO_FLOP_WIDTH 4.0f
#define TAP_TO_FLOP_HEIGHT 4.0f

#define WORLD_BACKGROUND_X SCREEN_WIDTH_1_2
#define WORLD_BACKGROUND_Y 17.62025314f
#define WORLD_BACKGROUND_WIDTH SCREEN_WIDTH
#define WORLD_BACKGROUND_HEIGHT 28.7594938f

#define SCORE_FONT_X SCREEN_WIDTH_1_2
#define SCORE_FONT_Y SCREEN_HEIGHT / 4 * 3
#define SCORE_FONT_WIDTH 4.0f
#define SCORE_FONT_HEIGHT 3.091f

#define TITLE_X SCREEN_WIDTH_1_2
#define TITLE_Y SCREEN_HEIGHT / 5 * 4
#define TITLE_WIDTH SCREEN_WIDTH / 8 * 7
#define TITLE_HEIGHT 5.78571429

#define GAME_OVER_X SCREEN_WIDTH_1_2
#define GAME_OVER_Y SCREEN_HEIGHT / 3 * 2 + 1
#define GAME_OVER_WIDTH SCREEN_WIDTH / 8 * 7
#define GAME_OVER_HEIGHT SCREEN_WIDTH / 8

#define DIALOG_GAME_OVER_X SCREEN_WIDTH_1_2
#define DIALOG_GAME_OVER_Y SCREEN_HEIGHT_1_2
#define DIALOG_GAME_OVER_WIDTH SCREEN_WIDTH_3_2 / 2
#define DIALOG_GAME_OVER_HEIGHT 5.25f

#define SCORE_FONT_IN_WINDOW_X 14.2f
#define SCORE_FONT_IN_WINDOW_Y 16.5f
#define BEST_FONT_IN_WINDOW_X 14.2f
#define BEST_FONT_IN_WINDOW_Y 14.7f
#define FONT_IN_WINDOW_WIDTH 1.45583954f
#define FONT_IN_WINDOW_HEIGHT 1.125f

#define MEDAL_X SCREEN_WIDTH_1_2 - 4.5f
#define MEDAL_Y SCREEN_HEIGHT_1_2 - 0.5f
#define MEDAL_WIDTH 1.4f
#define MEDAL_HEIGHT 2.8f

#include <memory>
#include "Obstacle.h"
#include "ObstacleBlock.h"
#include "Font.h"

class World;
class GameButton;

class Renderer
{
public:
    Renderer();
    
    virtual void renderWorldBackground(World &world) = 0;
    
    virtual void renderWorldForeground(World &world, float titleAlpha) = 0;
    
    virtual void renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore) = 0;
    
protected:
    std::unique_ptr<Font> m_font;
    
    virtual void renderObstacle(Obstacle &obstacle) = 0;
    
    virtual void renderGameObject(GameObject &go, TextureRegion tr) = 0;
};

#endif /* defined(__floppycock__Renderer__) */