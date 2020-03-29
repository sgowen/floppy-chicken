//
//  CockDynamicGameObject.h
//  floppycock
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__CockDynamicGameObject__
#define __floppycock__CockDynamicGameObject__

#include "DynamicGameObject.h"
#include <memory>
#include <vector>

class CockDynamicGameObject : public DynamicGameObject
{
public:
    CockDynamicGameObject(float x, float y, float width, float height);
    
    void update(float deltaTime);
    
    void startFlying();
    
    void flap();
    
    void hit();
    
    float getStateTime();
    
    bool isFlying();
    
    bool isHit();
    
    bool isDead();

private:
    float m_fStateTime;
    float m_fTimeSinceFlap;
    bool m_isFlying;
    bool m_isHit;
    bool m_isDead;
};

#endif /* defined(__floppycock__CockDynamicGameObject__) */