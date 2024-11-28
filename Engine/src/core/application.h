#pragma once

#include "defines.h" 

struct game;

// Application configuration.
typedef struct application_config {
    i16 start_pos_x;                    // Window starting position x axis, if applicable. 
    i16 start_pos_y;                    // Window starting position y axis, if applicable. 
    i16 start_width;                    // Window starting width, if applicable. 
    i16 start_height;                   // Window starting height, if applicable. 
    char* name;                         // The application name used in windowing, if applicable.
} application_config;

KAPI b8 application_create(struct game* game_inst);

KAPI b8 application_run();