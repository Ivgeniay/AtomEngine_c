#include "application.h"
#include "game_types.h"
#include "platform/platform.h"
#include "core/logger.h"
#include "core/kmemory.h"

typedef struct application_state {
    game* game_inst;
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initialized = FALSE;
static application_state app_state;

KAPI b8 application_create(game* game_inst){
    if(initialized){
        KERROR("Application already initialized.");
        return FALSE;
    }

    app_state.game_inst = game_inst; 

    initialize_logging(); // Initialize logging SUBSYSTEM.

    // TODO: delete this
    KFATAL("A test message: %f\n", 3.14f);
    KERROR("A test message: %f\n", 3.14f); 
    KDEBUG("A test message: %f\n", 3.14f);
    KTRACE("A test message: %f\n", 3.14f);
    KFATAL("Kek");

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if(!platform_startup(
        &app_state.platform, 
        game_inst->config.name,
        game_inst->config.start_pos_x,
        game_inst->config.start_pos_y,
        game_inst->config.start_width,
        game_inst->config.start_height)) 
        { 
            return FALSE;
        }

    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        KFATAL("Failed to initialize game instance.");
        return FALSE;
    }

    app_state.game_inst->on_resize(app_state.game_inst, app_state.width, app_state.height);

    initialized = TRUE;
    return TRUE;
}

KAPI b8 application_run(){
    KINFO("Application running.");
    KINFO(get_memory_usage_str());

    while(app_state.is_running) {
        if (!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = FALSE;
            //break;
        };

        if (!app_state.is_suspended)
        {
            if (!app_state.game_inst->update(app_state.game_inst, (f32)0))
            {
                KFATAL("Failed to update game instance.");
                app_state.is_running = FALSE;
                break;
            }

            if (!app_state.game_inst->render(app_state.game_inst, (f32)0))
            {
                KFATAL("Failed to render game instance.");
                app_state.is_running = FALSE;
                break;
            }


        //     if (!app_state.game_inst->update(app_state.game_inst, platform_get_time_since_start() - app_state.last_time))
        //     {
        //         app_state.is_running = FALSE;
        //         //break;
        //     }
         }
    }

    app_state.is_running = FALSE;
    platform_shutdown(&app_state.platform);
    return TRUE;
}