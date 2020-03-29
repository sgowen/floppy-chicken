//
//  CockDynamicGameObject.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "CockDynamicGameObject.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"

CockDynamicGameObject::CockDynamicGameObject(float x, float y, float width, float height) : DynamicGameObject(x, y, width, height, 0)
{
    m_velocity->set(0, 0);
    m_acceleration->set(0, -60);
	m_bounds->getLowerLeft().set(x - width / 4, y - height / 4);
    m_bounds->setWidth(width / 2);
	m_bounds->setHeight(height / 2);
    
    m_fStateTime = 0;
    m_fTimeSinceFlap = 0;
    m_fAngle = 360;
    m_isFlying = false;
    m_isHit = false;
    m_isDead = false;
}

void CockDynamicGameObject::startFlying()
{
    m_isFlying = true;
}

void CockDynamicGameObject::update(float deltaTime)
{
    m_fStateTime += deltaTime;
    
    if(m_isFlying)
    {
        m_fTimeSinceFlap += deltaTime;
        
        if(m_fTimeSinceFlap > 0.15f)
        {
            m_fAngle -= deltaTime * 200;
            
            if (m_fAngle < 270)
            {
                m_fAngle = 270;
            }
        }
        
        if (!m_isDead)
        {
            m_velocity->add(m_acceleration->getX() * deltaTime, m_acceleration->getY() * deltaTime);
            m_position->add(m_velocity->getX() * deltaTime, m_velocity->getY() * deltaTime);
            m_bounds->getLowerLeft().set(getPosition().getX() - getWidth() / 4, getPosition().getY() - getHeight() / 4);
            m_bounds->setAngle(getAngle());
            
            if(m_position->getY() > SCREEN_HEIGHT - 1.4f)
            {
                m_position->set(m_position->getX(), SCREEN_HEIGHT - 1.4f);
            }
            else if(m_position->getY() < GAME_WORLD_BASE)
            {
                m_isDead = true;
                Assets::getInstance()->setCurrentSoundId(LAND_SOUND);
            }
        }
    }
}

void CockDynamicGameObject::flap()
{
    if(!m_isHit && !m_isDead)
    {
        m_velocity->set(0, 24.0f);
        
        m_fTimeSinceFlap = 0;
        
        m_fAngle = 384;
        
        Assets::getInstance()->setCurrentSoundId(FLAP_SOUND);
    }
}

void CockDynamicGameObject::hit()
{
    m_isHit = true;
    m_velocity->set(0, 0);
    Assets::getInstance()->setCurrentSoundId(HIT_SOUND);
}

float CockDynamicGameObject::getStateTime()
{
    return m_fStateTime;
}

bool CockDynamicGameObject::isFlying()
{
    return m_isFlying;
}

bool CockDynamicGameObject::isHit()
{
    return m_isHit;
}

bool CockDynamicGameObject::isDead()
{
    return m_isDead;
}