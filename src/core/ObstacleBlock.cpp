//
//  Block.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/12/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "ObstacleBlock.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "pch.h"

ObstacleBlock::ObstacleBlock(float x, float y, float width, float height, float angle, Obstacle_Block_Type type) : GameObject(x, y, width, height, angle)
{
    m_type = type;
}

Obstacle_Block_Type ObstacleBlock::getType()
{
    return m_type;
}