//
//  Obstacle.h
//  floppycock
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__Obstacle__
#define __floppycock__Obstacle__

#include "GameObject.h"
#include "ObstacleBlock.h"
#include <vector>
#include <memory>

class CockDynamicGameObject;
class ObstacleBlock;

class Obstacle : public GameObject
{
public:
    Obstacle(float x, float y, float width, float height, float speed);
    
    // Return true if the cock has passed this obstacle
    bool update(float deltaTime, CockDynamicGameObject &cock);
    
    std::vector<std::unique_ptr<ObstacleBlock>> & getBlocks();

private:
    std::vector<std::unique_ptr<ObstacleBlock>> m_blocks;
    std::unique_ptr<Rectangle> m_topBounds;
    std::unique_ptr<Rectangle> m_bottomBounds;
    float m_fSpeed;
    bool m_isPassed;
    
    void reset(float x, float width);
};

#endif /* defined(__floppycock__Obstacle__) */