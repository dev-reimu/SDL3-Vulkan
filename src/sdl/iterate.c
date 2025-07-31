#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppIterate(void *appstate) {
    //SDL_Log("SDL_AppIterate");

    // Wayland requires a constant update loop for a window to show, 
    // so SDL_CreateWindow() does nothing on its own.
    // https://github.com/libsdl-org/SDL/issues/6074

    return SDL_APP_CONTINUE;
}
