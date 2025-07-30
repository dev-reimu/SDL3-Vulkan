// https://wiki.libsdl.org/SDL3/README-main-functions

#include <vulkan/vulkan.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

#include <stdio.h>

VkInstance *instance;
SDL_DisplayID display_id;
const SDL_DisplayMode *display_mode;
SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    printf("SDL_AppInit\n");

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL video: %s\n", SDL_GetError());
        return 1;
    }
    printf("Initialized SDL video.");

    display_id = SDL_GetPrimaryDisplay();
    if (display_id == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get primary display: %s\n", SDL_GetError());
        return 1;
    }
    printf("Found primary display with ID %d", display_id);

    display_mode = SDL_GetCurrentDisplayMode(display_id);
    if (display_mode == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get display properties of primary display: %s\n", SDL_GetError());
        return 1;
    }
    printf("Found primary display properties.");

    window = SDL_CreateWindow("SDL3-Vulkan Window", display_mode->w, display_mode->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    printf("Created exclusive fullscreen window with resolution %dx%d@%f", display_mode->w, display_mode->h, display_mode->refresh_rate);

    return 0;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    //printf("SDL_AppIterate\n");

    return 0;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //printf("SDL_AppEvent\n");

    return 0;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    printf("SDL_AppQuit\n");

    vkDestroyInstance(*instance, NULL);
    SDL_DestroyWindow(window);
    
    return;
}
