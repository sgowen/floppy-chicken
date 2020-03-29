//
//  Assets.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "Assets.h"
#include "TextureRegion.h"
#include "CockDynamicGameObject.h"
#include "pch.h"

Assets * Assets::getInstance()
{
	static Assets *assets = new Assets();
	return assets;
}

TextureRegion Assets::getTapToFlopTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(TAP_TO_FLOP_TEXTURE_REGION_X, TAP_TO_FLOP_TEXTURE_REGION_Y, TAP_TO_FLOP_TEXTURE_REGION_WIDTH, TAP_TO_FLOP_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getBackgroundTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(BG_GAME_TEXTURE_REGION_X, BG_GAME_TEXTURE_REGION_Y, BG_GAME_TEXTURE_REGION_WIDTH, BG_GAME_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getForegroundTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(FG_GAME_TEXTURE_REGION_X, FG_GAME_TEXTURE_REGION_Y, FG_GAME_TEXTURE_REGION_WIDTH, FG_GAME_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getForegroundTopTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(FG_TOP_GAME_TEXTURE_REGION_X, FG_TOP_GAME_TEXTURE_REGION_Y, FG_TOP_GAME_TEXTURE_REGION_WIDTH, FG_TOP_GAME_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGameOverDialogTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(DIALOG_TEXTURE_REGION_X, DIALOG_TEXTURE_REGION_Y, DIALOG_TEXTURE_REGION_WIDTH, DIALOG_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getCockTextureRegion(CockDynamicGameObject &cock)
{
    static std::vector<TextureRegion> cockTextureRegions;
	if(cockTextureRegions.size() == 0)
	{
        cockTextureRegions.push_back(TextureRegion(COCK_TEXTURE_REGION_1_X, COCK_TEXTURE_REGION_1_Y, COCK_TEXTURE_REGION_WIDTH, COCK_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		cockTextureRegions.push_back(TextureRegion(COCK_TEXTURE_REGION_2_X, COCK_TEXTURE_REGION_2_Y, COCK_TEXTURE_REGION_WIDTH, COCK_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
		cockTextureRegions.push_back(TextureRegion(COCK_TEXTURE_REGION_3_X, COCK_TEXTURE_REGION_3_Y, COCK_TEXTURE_REGION_WIDTH, COCK_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
	}
    
	static float cycleTime = 0.9f;
	static std::vector<float> cockFrames;
	if(cockFrames.size() == 0)
	{
		cockFrames.push_back(0.3f);
		cockFrames.push_back(0.3f);
		cockFrames.push_back(0.3f);
	}
    
    return cockTextureRegions.at(getKeyFrameNumber(cock.getStateTime(), cycleTime, cockFrames));
}

TextureRegion Assets::getFencePostTextureRegion(Obstacle_Block_Type type)
{
    static TextureRegion textureRegionRoofOne = TextureRegion(BLOCK_TYPE_1_ROOF_TEXTURE_REGION_X, BLOCK_TYPE_1_ROOF_TEXTURE_REGION_Y, BLOCK_TYPE_1_ROOF_TEXTURE_REGION_WIDTH, BLOCK_TYPE_1_ROOF_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionOne = TextureRegion(BLOCK_TYPE_1_1_TEXTURE_REGION_X, BLOCK_TYPE_1_1_TEXTURE_REGION_Y, BLOCK_TYPE_1_1_TEXTURE_REGION_WIDTH, BLOCK_TYPE_1_1_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionOneTwo = TextureRegion(BLOCK_TYPE_1_2_TEXTURE_REGION_X, BLOCK_TYPE_1_2_TEXTURE_REGION_Y, BLOCK_TYPE_1_2_TEXTURE_REGION_WIDTH, BLOCK_TYPE_1_2_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionOneThree = TextureRegion(BLOCK_TYPE_1_3_TEXTURE_REGION_X, BLOCK_TYPE_1_3_TEXTURE_REGION_Y, BLOCK_TYPE_1_3_TEXTURE_REGION_WIDTH, BLOCK_TYPE_1_3_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    static TextureRegion textureRegionRoofTwo = TextureRegion(BLOCK_TYPE_2_ROOF_TEXTURE_REGION_X, BLOCK_TYPE_2_ROOF_TEXTURE_REGION_Y, BLOCK_TYPE_2_ROOF_TEXTURE_REGION_WIDTH, BLOCK_TYPE_2_ROOF_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    static TextureRegion textureRegionTwo = TextureRegion(BLOCK_TYPE_2_TEXTURE_REGION_X, BLOCK_TYPE_2_TEXTURE_REGION_Y, BLOCK_TYPE_2_TEXTURE_REGION_WIDTH, BLOCK_TYPE_2_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    
    switch (type)
    {
        case TYPE_1_ROOF:
            return textureRegionRoofOne;
        case TYPE_1_1:
            return textureRegionOne;
        case TYPE_1_2:
            return textureRegionOneTwo;
        case TYPE_1_3:
            return textureRegionOneThree;
        case TYPE_2_ROOF:
            return textureRegionRoofTwo;
        case TYPE_2:
        default:
            return textureRegionTwo;
    }
}

TextureRegion Assets::getTitleTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(TITLE_TEXTURE_REGION_X, TITLE_TEXTURE_REGION_Y, TITLE_TEXTURE_REGION_WIDTH, TITLE_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGameOverTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(GAME_OVER_TEXTURE_REGION_X, GAME_OVER_TEXTURE_REGION_Y, GAME_OVER_TEXTURE_REGION_WIDTH, GAME_OVER_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getOkButtonTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(OK_BUTTON_TEXTURE_REGION_X, OK_BUTTON_TEXTURE_REGION_Y, OK_BUTTON_TEXTURE_REGION_WIDTH, OK_BUTTON_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getLeaderboardsButtonTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(LEADERBOARDS_BUTTON_TEXTURE_REGION_X, LEADERBOARDS_BUTTON_TEXTURE_REGION_Y, LEADERBOARDS_BUTTON_TEXTURE_REGION_WIDTH, LEADERBOARDS_BUTTON_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getBronzeMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_BRONZE_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getSilverMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_SILVER_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGoldMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_GOLD_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getPlatinumMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_PLATINUM_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

TextureRegion Assets::getGrandPoobahMedalTextureRegion()
{
    static TextureRegion textureRegion = TextureRegion(MEDAL_GRAND_POOBAH_TEXTURE_REGION_X, MEDAL_TEXTURE_REGION_Y, MEDAL_TEXTURE_REGION_WIDTH, MEDAL_TEXTURE_REGION_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT);
    return textureRegion;
}

short Assets::getCurrentSoundId()
{
    return m_sCurrentSoundId;
}

void Assets::setCurrentSoundId(short soundId)
{
    m_sCurrentSoundId = soundId;
}

void Assets::resetCurrentSoundId()
{
    m_sCurrentSoundId = 0;
}

int Assets::getKeyFrameNumber(float stateTime, float cycleTime, std::vector<float> &frameDurations)
{
    if (stateTime > cycleTime && cycleTime > 0)
    {
        while(stateTime > cycleTime)
        {
            stateTime -= cycleTime;
        }
    }
    
    for (unsigned int i = 0; i < frameDurations.size(); i++)
    {
        if (stateTime < frameDurations.at(i))
        {
            return i;
        }
        
        stateTime -= frameDurations.at(i);
    }
    
    return 0;
}

Assets::Assets()
{
    // Hide Constructor for Singleton
}