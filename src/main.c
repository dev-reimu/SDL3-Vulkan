// https://wiki.libsdl.org/SDL3/README-main-functions

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <stdio.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    // Create window + audio devices
}

SDL_AppResult SDL_AppIterate(void *appstate) { printf("Run.\n"); }

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {}
