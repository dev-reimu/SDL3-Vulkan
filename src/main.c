// https://wiki.libsdl.org/SDL3/README-main-functions

#include <vulkan/vulkan.h>

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

#define SDL_HINT_VIDEO_WAYLAND_SCALE_TO_DISPLAY "SDL_VIDEO_WAYLAND_SCALE_TO_DISPLAY"

#include <stdio.h>

VkInstance *instance;
SDL_DisplayID display_id;
//SDL_DisplayMode *all_display_modes[];
const SDL_DisplayMode *display_mode;
SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    printf("[SDL Main Callback] Init\n");

    SDL_Init(SDL_INIT_VIDEO);

    display_id = SDL_GetPrimaryDisplay();

    // Query resolutions
    // int *count;
    // SDL_GetFullscreenDisplayModes(display_id, count);
    // printf("Found %d available resolutions.\n", *count);
    // if (*count <= 0) {
    //     SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get current display mode: %s\n", SDL_GetError());
    //     return 1;
    // }
    // for (int i = 0; i < *count; i++)
    //     printf("Resolution %d: %dx%d@%f\n", i, all_display_modes[i]->w, all_display_modes[i]->h, all_display_modes[i]->refresh_rate);

    // Create window with current resolution
    display_mode = SDL_GetCurrentDisplayMode(display_id);
    window = SDL_CreateWindow("SDL3-Vulkan Window", display_mode->w, display_mode->h, SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    //printf("[SDL Main Callback] Iterate\n");

    return 0;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //printf("[SDL Main Callback] Event\n");

    return 0;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    printf("[SDL Main Callback] Quit\n");

    vkDestroyInstance(*instance, NULL);
    SDL_DestroyWindow(window);
    
    return;
}
