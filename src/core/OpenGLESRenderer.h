//
//  OpenGLESRenderer.h
//  floppycock
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __floppycock__OpenGLESRenderer__
#define __floppycock__OpenGLESRenderer__

#include "Renderer.h"

extern "C"
{
#include "platform_gl.h"
}

class OpenGLESRenderer : public Renderer
{
public:
    OpenGLESRenderer();
    
    virtual void renderWorldBackground(World &world);
    
    virtual void renderWorldForeground(World &world, float titleAlpha);
    
    virtual void renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore);
    
private:
    std::unique_ptr<SpriteBatcher> m_spriteBatcher;
    std::unique_ptr<SpriteBatcher> m_spriteBatcherWithColor;
    GLuint m_gameTexture;
    
    virtual void renderObstacle(Obstacle &obstacle);
    
    virtual void renderGameObject(GameObject &go, TextureRegion tr);
};

#endif /* defined(__floppycock__OpenGLESRenderer__) */