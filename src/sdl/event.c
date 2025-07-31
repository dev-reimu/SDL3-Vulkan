#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //SDL_Log("SDL_AppEvent");

    // switch (event->type)
    // {
    //     case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED:
    //         SDL_Log("SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED");
    //         SDL_DisplayMode *new_display_mode = Get_Display_Mode_From_Id(event->display.displayID);
    //         SDL_Reimu_CheckError(appstate, "Could not change to new display mode");
    //         break;
        
    //     default:
    //         break;
    // }

    return SDL_APP_CONTINUE;
}
