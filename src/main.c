// https://wiki.libsdl.org/SDL3/README-main-functions

#include <vulkan/vulkan.h>

#define SDL_MAIN_USE_CALLBACKS
#define SDL_WINDOW_ALLOW_HIGHDPI
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_Log("SDL_AppInit\n");

    // Program skips all code after SDL_INIT_VIDEO. I don't know how to fix this. Damn software.
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL video: %s\n.", SDL_GetError());
        return 1;
    }
    SDL_Log("Initialized SDL video.");

    SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
    if (display_id == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get primary display: %s\n.", SDL_GetError());
        return 1;
    }
    SDL_Log("Found primary display with ID %d.", display_id);

    const SDL_DisplayMode *display_mode = SDL_GetCurrentDisplayMode(display_id);
    if (display_mode == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get display properties of primary display: %s\n.", SDL_GetError());
        return 1;
    }
    SDL_Log("Found primary display properties.");

    window = SDL_CreateWindow("SDL3-Vulkan Window", 2880, 1800, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n.", SDL_GetError());
        return 1;
    }
    SDL_Log("Created exclusive fullscreen window with resolution %dx%d@%f.", display_mode->w, display_mode->h, display_mode->refresh_rate);

    return 0;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    //SDL_Log("SDL_AppIterate\n");

    return 0;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //SDL_Log("SDL_AppEvent\n");

    return 0;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit\n");
    
    SDL_DestroyWindow(window);
    
    return;
}
