#pragma once

#include "core/application.h"

typedef struct game{
    application_config config;                                          // Application configuration.                       

    b8 (*initialize)(struct game* game_inst);                           // Initialize the game.
    b8 (*update)(struct game* game_inst, f32 delta_time);               // Update the game.
    b8 (*render)(struct game* game_inst, f32 delta_time);               // Render the game.
    void (*on_resize)(struct game* game_inst, i16 width, i16 height);   // Resize the game.
    void* state;
} game; 