// https://wiki.libsdl.org/SDL3/README-main-functions

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <stdio.h>

SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    printf("[SDL Main Callback] Init\n");

    window = SDL_CreateWindow("Test", 800, 600, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    return 0;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    printf("[SDL Main Callback] Iterate\n");

    return 0;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    printf("[SDL Main Callback] Event\n");

    return 0;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    printf("[SDL Main Callback] Quit\n");

    SDL_DestroyWindow(window);
    
    return;
}
