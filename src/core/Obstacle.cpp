//
//  Obstacle.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#define BLOCK_HEIGHT 1
#define BLOCK_HEIGHT_X4 4

#include "pch.h"
#include "Obstacle.h"
#include "CockDynamicGameObject.h"
#include "ObstacleBlock.h"
#include "OverlapTester.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "ObstacleBlockType.h"
#include <random>

Obstacle::Obstacle(float x, float y, float width, float height, float speed) : GameObject(x, y, width, height, 0)
{
    m_fSpeed = speed;
    
    reset(x, width);
}

bool Obstacle::update(float deltaTime, CockDynamicGameObject &cock)
{
    if(OverlapTester::doRectanglesOverlap(cock.getBounds(), *m_topBounds) || OverlapTester::doRectanglesOverlap(cock.getBounds(), *m_bottomBounds))
    {
        cock.hit();
    }
    
    getPosition().sub(m_fSpeed * deltaTime, 0);
    
    if(getPosition().getX() < GAME_OFF_SCREEN_OBSTACLE_X)
    {
        getPosition().set(GAME_RESET_OBSTACLE_X, getPosition().getY());
        reset(GAME_RESET_OBSTACLE_X, getWidth());
    }
    
    updateBounds();
    
    Vector2D &lowerLeftTop = m_topBounds->getLowerLeft();
    lowerLeftTop.set(m_position->getX() - m_topBounds->getWidth() / 2, m_topBounds->getLowerLeft().getY());
    
    Vector2D &lowerLeftBottom = m_bottomBounds->getLowerLeft();
    lowerLeftBottom.set(m_position->getX() - m_bottomBounds->getWidth() / 2, m_bottomBounds->getLowerLeft().getY());
    
    for (std::vector<std::unique_ptr<ObstacleBlock>>::iterator itr = m_blocks.begin(); itr != m_blocks.end(); itr++)
    {
        (*itr)->getPosition().set(getPosition().getX(), (*itr)->getPosition().getY());
    }
    
    if(!m_isPassed && cock.getPosition().getX() > getPosition().getX())
    {
        m_isPassed = true;
        return true;
    }
    
    return false;
}

std::vector<std::unique_ptr<ObstacleBlock>> & Obstacle::getBlocks()
{
    return m_blocks;
}

void Obstacle::reset(float x, float width)
{
    m_isPassed = false;
    
    m_blocks.clear();
    
    int random_integer = rand() % 9;
	switch (random_integer)
	{
        case 0:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,  180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 18.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 16.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 12.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  8.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 27, width, 6));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 19));
            break;
        case 1:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,  180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 16.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 14.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 10.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  6.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 25, width, 8));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 17));
            break;
        case 2:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 14.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 12.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  8.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 23, width, 10));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 15));
            break;
        case 3:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 12.5f, width, BLOCK_HEIGHT,    0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 10.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  6.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 21, width, 12));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 13));
            break;
        case 4:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 20.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 19.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 10.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 8.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 19, width, 14));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 11));
            break;
        case 5:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 20.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 19.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 18.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 17.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  8.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  6.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  2.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_1)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, -2.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 17, width, 16));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 9));
            break;
        case 6:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 20.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 19.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 18.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 17.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 16.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 15.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  6.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 15, width, 18));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 7));
            break;
        case 7:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 20.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 19.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 18.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 17.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 16.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 15.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 14.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 13.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  4.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  2.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_2)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 13, width, 20));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 5));
            break;
        case 8:
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 31.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 30.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 29.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 28.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 27.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 26.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 25.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 24.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 23.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 22.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 21.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 20.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 19.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 18.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 17.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 16.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 15.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 14.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 13.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 12.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_2)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x, 11.5f, width, BLOCK_HEIGHT, 180, Obstacle_Block_Type::TYPE_2_ROOF)));
            
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  2.5f, width, BLOCK_HEIGHT,   0, Obstacle_Block_Type::TYPE_1_ROOF)));
            m_blocks.push_back(std::unique_ptr<ObstacleBlock>(new ObstacleBlock(x,  0.0f, width, BLOCK_HEIGHT_X4, 0, Obstacle_Block_Type::TYPE_1_3)));
            
            m_topBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 11, width, 22));
            m_bottomBounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, 0, width, 3));
            break;
	}
}