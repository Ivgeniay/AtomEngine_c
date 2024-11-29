#include <game.h>

#include <entry.h>

// TODO: REMOVE THIS
#include <core/kmemory.h>


//Define the function to create a game instance.
b8 create_game(game* out_game) {
    //KASSERT(out_game);
    out_game->config.name = "Atom Engine";
    out_game->config.start_pos_x = 100;
    out_game->config.start_pos_y = 100;
    out_game->config.start_width = 1280;
    out_game->config.start_height = 720;

    out_game->initialize = game_initialize;
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->on_resize = game_on_resize;

    out_game->state = kallocate(sizeof(game_state), MEMORY_TAG_GAME);

    return TRUE;
}
