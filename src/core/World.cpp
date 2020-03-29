//
//  World.cpp
//  floppycock
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#define GAME_SPEED 6

#include "pch.h"
#include "World.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "CockDynamicGameObject.h"
#include "TouchEvent.h"
#include "Assets.h"
#include "Obstacle.h"

World::World()
{
    m_cock = std::unique_ptr<CockDynamicGameObject>(new CockDynamicGameObject(SCREEN_WIDTH / 8 * 3, SCREEN_HEIGHT / 2, 4.0f, 2.0f));
    
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(GAME_RESET_OBSTACLE_X, SCREEN_HEIGHT / 2, 4, SCREEN_HEIGHT, GAME_SPEED)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 18, SCREEN_HEIGHT / 2, 4, SCREEN_HEIGHT, GAME_SPEED)));
    m_obstacles.push_back(std::unique_ptr<Obstacle>(new Obstacle(SCREEN_WIDTH / 8 * 24, SCREEN_HEIGHT / 2, 4, SCREEN_HEIGHT, GAME_SPEED)));
    
    m_foregroundLeft = std::unique_ptr<GameObject>(new GameObject(SCREEN_WIDTH_1_2, GAME_WORLD_BASE_1_2, SCREEN_WIDTH, GAME_WORLD_BASE, 0));
    m_foregroundRight = std::unique_ptr<GameObject>(new GameObject(SCREEN_WIDTH_3_2, GAME_WORLD_BASE_1_2, SCREEN_WIDTH, GAME_WORLD_BASE, 0));
    
    m_iScore = 0;
}

void World::startGame()
{
    m_cock->startFlying();
}

void World::update(float deltaTime)
{
    m_cock->update(deltaTime);
    
    if(m_cock->isHit() || m_cock->isDead())
    {
        return;
    }
    
    if(m_cock->isFlying())
    {
        for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = m_obstacles.begin(); itr != m_obstacles.end(); itr++)
        {
            if((*itr)->update(deltaTime, *m_cock))
            {
                Assets::getInstance()->setCurrentSoundId(SCORE_SOUND);
                m_iScore++;
            }
        }
    }
    
    float shiftX = deltaTime * GAME_SPEED;
    
    if(m_foregroundLeft->getPosition().getX() < m_foregroundRight->getPosition().getX())
    {
        m_foregroundLeft->getPosition().sub(shiftX, 0);
        m_foregroundRight->getPosition().set(m_foregroundLeft->getPosition().getX() + SCREEN_WIDTH, m_foregroundRight->getPosition().getY());
    }
    else
    {
        m_foregroundRight->getPosition().sub(shiftX, 0);
        m_foregroundLeft->getPosition().set(m_foregroundRight->getPosition().getX() + SCREEN_WIDTH, m_foregroundLeft->getPosition().getY());
    }
    
    if(m_foregroundLeft->getPosition().getX() < -SCREEN_WIDTH_1_2)
    {
        m_foregroundLeft->getPosition().set(SCREEN_WIDTH_3_2, m_foregroundLeft->getPosition().getY());
        m_foregroundRight->getPosition().set(SCREEN_WIDTH_1_2, m_foregroundRight->getPosition().getY());
    }
    else if(m_foregroundRight->getPosition().getX() < -SCREEN_WIDTH_1_2)
    {
        m_foregroundRight->getPosition().set(SCREEN_WIDTH_3_2, m_foregroundRight->getPosition().getY());
        m_foregroundLeft->getPosition().set(SCREEN_WIDTH_1_2, m_foregroundLeft->getPosition().getY());
    }
    
    m_foregroundLeft->updateBounds();
    m_foregroundRight->updateBounds();
}

void World::handleTouchUp(TouchEvent &touchEvent)
{
    m_cock->flap();
}

std::vector<std::unique_ptr<Obstacle>> & World::getObstacles()
{
    return m_obstacles;
}

GameObject & World::getForegroundLeft()
{
    return *m_foregroundLeft;
}

GameObject & World::getForegroundRight()
{
    return *m_foregroundRight;
}

CockDynamicGameObject & World::getCock()
{
    return *m_cock;
}

int World::getScore()
{
    return m_iScore;
}

bool World::isGameOver()
{
    return m_cock->isDead();
}