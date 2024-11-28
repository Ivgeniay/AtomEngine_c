#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "game_types.h" 

extern b8 create_game(game* out_game);


// Entry point for the application.
int main(void) { 
    game game_inst; // Request the game instance from the application;
    if (!create_game(&game_inst)) {
        KFATAL("Failed to create game instance.");
        return -1;
    }

    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
        KFATAL("Game instance is missing required functions.");
        return -2;
    }

    if (!application_create(&game_inst)) {
        KINFO("Failed to create application.");
        return -3;
    }

    if (!application_run()) {       //Begin the game loop.
        KINFO("Application did not shutdown gracefully.");
        return -4;
    }

    return 0;
}