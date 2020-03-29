//
//  game.h
//  floppycock
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

void on_surface_created(int pixelWidth, int pixelHeight);

void on_surface_changed(int pixelWidth, int pixelHeight, int dpWidth, int dpHeight);

void init();

void on_resume();

void on_pause();

void update(float deltaTime);

void present();

void on_touch_down(float raw_touch_x, float raw_touch_y);

void on_touch_dragged(float raw_touch_x, float raw_touch_y);

void on_touch_up(float raw_touch_x, float raw_touch_y);

short get_current_music_id();

short get_current_sound_id();

int get_state();

void clear_state();

int get_score();

void set_best_score(int best_score);

bool handle_on_back_pressed();

void clean_up();

#endif /* GAME_H */