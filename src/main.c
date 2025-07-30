// https://wiki.libsdl.org/SDL3/README-main-functions

#include <vulkan/vulkan.h>

#define SDL_MAIN_USE_CALLBACKS
#define SDL_WINDOW_ALLOW_HIGHDPI_renamed_SDL_WINDOW_HIGH_PIXEL_DENSITY
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_Log("SDL_AppInit\n");

    SDL_SetHint("SDL_VIDEO_DRIVER", "wayland");

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL video: %s\n.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Initialized SDL video.");

    SDL_DisplayID display_id = SDL_GetPrimaryDisplay();
    if (display_id == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get primary display: %s\n.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Found primary display with ID %d.", display_id);

    int width = SDL_GetFullscreenDisplayModes(display_id, NULL)[0]->w;
    int height = SDL_GetFullscreenDisplayModes(display_id, NULL)[0]->h;
    float refreshrate = SDL_GetFullscreenDisplayModes(display_id, NULL)[0]->refresh_rate;

    window = SDL_CreateWindow("SDL3-Vulkan Window", width, height, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Created borderless fullscreen window with resolution %dx%d@%f.", width, height, refreshrate);

    return SDL_APP_CONTINUE;
    
    if (SDL_SetWindowFullscreen(window, true) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not convert window to exclusive fullscreen: %s\n.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Converted window to exclusive fullscreen mode.");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    //SDL_Log("SDL_AppIterate\n");

    // Wayland requires a constant update loop for a window to show, 
    // so SDL_CreateWindow() does nothing on its own.
    // https://github.com/libsdl-org/SDL/issues/6074

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //SDL_Log("SDL_AppEvent\n");

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit\n");
    
    SDL_DestroyWindow(window);
    
    return;
}
