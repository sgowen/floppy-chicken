//
//  Block.h
//  floppycock
//
//  Created by Stephen Gowen on 2/12/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__ObstacleBlock__
#define __floppycock__ObstacleBlock__

#include "GameObject.h"
#include "ObstacleBlockType.h"

class ObstacleBlock : public GameObject
{
public:
    ObstacleBlock(float x, float y, float width, float height, float angle, Obstacle_Block_Type type);

    Obstacle_Block_Type getType();

private:
    Obstacle_Block_Type m_type;
};

#endif /* defined(__floppycock__ObstacleBlock__) */