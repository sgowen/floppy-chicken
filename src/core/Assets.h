//
//  Assets.h
//  floppycock
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__Assets__
#define __floppycock__Assets__

// Texture Definitions
#define GAME_TEXTURE_WIDTH 1024
#define GAME_TEXTURE_HEIGHT 1024

// Texture Region Definitions
#define TAP_TO_FLOP_TEXTURE_REGION_X 264
#define TAP_TO_FLOP_TEXTURE_REGION_Y 144
#define TAP_TO_FLOP_TEXTURE_REGION_WIDTH 64
#define TAP_TO_FLOP_TEXTURE_REGION_HEIGHT 64

#define BG_GAME_TEXTURE_REGION_X 0
#define BG_GAME_TEXTURE_REGION_Y 0
#define BG_GAME_TEXTURE_REGION_WIDTH 178
#define BG_GAME_TEXTURE_REGION_HEIGHT 237

#define FG_GAME_TEXTURE_REGION_X 32
#define FG_GAME_TEXTURE_REGION_Y 296
#define FG_GAME_TEXTURE_REGION_WIDTH 256
#define FG_GAME_TEXTURE_REGION_HEIGHT 32

#define FG_TOP_GAME_TEXTURE_REGION_X 32
#define FG_TOP_GAME_TEXTURE_REGION_Y 256
#define FG_TOP_GAME_TEXTURE_REGION_WIDTH 256
#define FG_TOP_GAME_TEXTURE_REGION_HEIGHT 32

#define DIALOG_TEXTURE_REGION_X 264
#define DIALOG_TEXTURE_REGION_Y 40
#define DIALOG_TEXTURE_REGION_WIDTH 144
#define DIALOG_TEXTURE_REGION_HEIGHT 56

#define COCK_TEXTURE_REGION_1_X 808
#define COCK_TEXTURE_REGION_1_Y 8
#define COCK_TEXTURE_REGION_2_X 848
#define COCK_TEXTURE_REGION_2_Y 8
#define COCK_TEXTURE_REGION_3_X 888
#define COCK_TEXTURE_REGION_3_Y 8
#define COCK_TEXTURE_REGION_WIDTH 32
#define COCK_TEXTURE_REGION_HEIGHT 16

#define BLOCK_TYPE_1_ROOF_TEXTURE_REGION_X 944
#define BLOCK_TYPE_1_ROOF_TEXTURE_REGION_Y 8
#define BLOCK_TYPE_1_ROOF_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_1_ROOF_TEXTURE_REGION_HEIGHT 8

#define BLOCK_TYPE_1_1_TEXTURE_REGION_X 944
#define BLOCK_TYPE_1_1_TEXTURE_REGION_Y 24
#define BLOCK_TYPE_1_1_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_1_1_TEXTURE_REGION_HEIGHT 32

#define BLOCK_TYPE_1_2_TEXTURE_REGION_X 944
#define BLOCK_TYPE_1_2_TEXTURE_REGION_Y 64
#define BLOCK_TYPE_1_2_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_1_2_TEXTURE_REGION_HEIGHT 32

#define BLOCK_TYPE_1_3_TEXTURE_REGION_X 944
#define BLOCK_TYPE_1_3_TEXTURE_REGION_Y 104
#define BLOCK_TYPE_1_3_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_1_3_TEXTURE_REGION_HEIGHT 32

#define BLOCK_TYPE_2_ROOF_TEXTURE_REGION_X 984
#define BLOCK_TYPE_2_ROOF_TEXTURE_REGION_Y 8
#define BLOCK_TYPE_2_ROOF_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_2_ROOF_TEXTURE_REGION_HEIGHT 8

#define BLOCK_TYPE_2_TEXTURE_REGION_X 984
#define BLOCK_TYPE_2_TEXTURE_REGION_Y 24
#define BLOCK_TYPE_2_TEXTURE_REGION_WIDTH 32
#define BLOCK_TYPE_2_TEXTURE_REGION_HEIGHT 8

#define GAME_OVER_TEXTURE_REGION_X 0
#define GAME_OVER_TEXTURE_REGION_Y 704
#define GAME_OVER_TEXTURE_REGION_WIDTH 512
#define GAME_OVER_TEXTURE_REGION_HEIGHT 66

#define TITLE_TEXTURE_REGION_X 0
#define TITLE_TEXTURE_REGION_Y 792
#define TITLE_TEXTURE_REGION_WIDTH 392
#define TITLE_TEXTURE_REGION_HEIGHT 144

#define OK_BUTTON_TEXTURE_REGION_X 272
#define OK_BUTTON_TEXTURE_REGION_Y 112
#define OK_BUTTON_TEXTURE_REGION_WIDTH 40
#define OK_BUTTON_TEXTURE_REGION_HEIGHT 13

#define LEADERBOARDS_BUTTON_TEXTURE_REGION_X 328
#define LEADERBOARDS_BUTTON_TEXTURE_REGION_Y 104
#define LEADERBOARDS_BUTTON_TEXTURE_REGION_WIDTH 80
#define LEADERBOARDS_BUTTON_TEXTURE_REGION_HEIGHT 32

#define MEDAL_BRONZE_TEXTURE_REGION_X 264
#define MEDAL_SILVER_TEXTURE_REGION_X 288
#define MEDAL_GOLD_TEXTURE_REGION_X 312
#define MEDAL_PLATINUM_TEXTURE_REGION_X 336
#define MEDAL_GRAND_POOBAH_TEXTURE_REGION_X 360
#define MEDAL_TEXTURE_REGION_Y 0
#define MEDAL_TEXTURE_REGION_WIDTH 16
#define MEDAL_TEXTURE_REGION_HEIGHT 32

#define FONT_TEXTURE_REGION_X 0
#define FONT_TEXTURE_REGION_Y 336
#define FONT_GLYPHS_PER_ROW 16
#define FONT_GLYPH_WIDTH 44
#define FONT_GLYPH_HEIGHT 34

// Sound Definitions
#define FLAP_SOUND 1
#define SCORE_SOUND 2
#define HIT_SOUND 3
#define LAND_SOUND 4

#include <vector>
#include "ObstacleBlockType.h"

class TextureRegion;
class CockDynamicGameObject;

class Assets
{
public:
	static Assets * getInstance();
    
    static TextureRegion getTapToFlopTextureRegion();
    
    static TextureRegion getBackgroundTextureRegion();
    
    static TextureRegion getForegroundTextureRegion();
    
    static TextureRegion getForegroundTopTextureRegion();
    
    static TextureRegion getTitleTextureRegion();
    
    static TextureRegion getGameOverDialogTextureRegion();
    
    static TextureRegion getCockTextureRegion(CockDynamicGameObject &cock);
    
    static TextureRegion getFencePostTextureRegion(Obstacle_Block_Type type);
    
    static TextureRegion getGameOverTextureRegion();
    
    static TextureRegion getOkButtonTextureRegion();
    
    static TextureRegion getLeaderboardsButtonTextureRegion();
    
    static TextureRegion getBronzeMedalTextureRegion();
    
    static TextureRegion getSilverMedalTextureRegion();
    
    static TextureRegion getGoldMedalTextureRegion();
    
    static TextureRegion getPlatinumMedalTextureRegion();
    
    static TextureRegion getGrandPoobahMedalTextureRegion();
    
    short getCurrentSoundId();
    
    void setCurrentSoundId(short soundId);
    
    void resetCurrentSoundId();

private:
    Assets();
    
    static int getKeyFrameNumber(float stateTime, float cycleTime, std::vector<float> &frameDurations);
    
    short m_sCurrentSoundId;
};

#endif /* defined(__floppycock__Assets__) */