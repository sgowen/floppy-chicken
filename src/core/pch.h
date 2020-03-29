//
//  pch.h
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef PCH_H
#define PCH_H

#define LOGGING_ON 1

#define SCREEN_WIDTH 18
#define SCREEN_WIDTH_1_2 9
#define SCREEN_WIDTH_3_2 27
#define SCREEN_HEIGHT 32
#define SCREEN_HEIGHT_1_2 16

// Game World Definitions
#define GAME_WORLD_BASE 3.24050624f
#define GAME_WORLD_BASE_1_2 GAME_WORLD_BASE / 2
#define GAME_RESET_OBSTACLE_X SCREEN_WIDTH / 8 * 12
#define GAME_OFF_SCREEN_OBSTACLE_X -SCREEN_WIDTH / 8 * 6

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0f * M_PI)
#define RADIANS_TO_DEGREES(angle) ((angle) / M_PI * 180.0f)

#ifdef TECHNE_GAMES_OPENGL_ES

#elif defined TECHNE_GAMES_DIRECT_3D
#define DEGREES_TO_RADIANS_WP(angle) -((angle) / 180.0f * M_PI)
#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <agile.h>
#include <wrl.h>
#include <xaudio2.h>
#include <mmreg.h>
#pragma comment( lib, "xaudio2.lib")
#pragma comment( lib, "mfplat.lib")
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#endif /* PCH_H */