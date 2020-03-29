//
//  World.h
//  floppycock
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__World__
#define __floppycock__World__

#include <memory>
#include <vector>
#include "Obstacle.h"

class GameObject;
class Obstacle;
class CockDynamicGameObject;
class TouchEvent;

class World
{
public:
    World();
    
    void startGame();
    
    void update(float deltaTime);
    
    void handleTouchUp(TouchEvent &touchEvent);
    
    std::vector<std::unique_ptr<Obstacle>> & getObstacles();
    
    GameObject& getForegroundLeft();
    
    GameObject& getForegroundRight();
    
    CockDynamicGameObject & getCock();
    
    int getScore();
    
    bool isGameOver();
    
private:
    std::vector<std::unique_ptr<Obstacle>> m_obstacles;
    std::unique_ptr<CockDynamicGameObject> m_cock;
    std::unique_ptr<GameObject> m_foregroundLeft;
    std::unique_ptr<GameObject> m_foregroundRight;
    int m_iScore;
};

#endif /* defined(__floppycock__World__) */