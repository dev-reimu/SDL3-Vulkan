// https://wiki.libsdl.org/SDL3/README-main-functions

#define SDL_MAIN_USE_CALLBACKS
#define SDL_WINDOW_ALLOW_HIGHDPI_renamed_SDL_WINDOW_HIGH_PIXEL_DENSITY
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include "../headers/reimu-sdl-extensions.h"
#include "../headers/global_variables.h"

extern SDL_Window *window;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_Log("SDL_AppInit\n");

    // Linux specific -> Select X11 or Wayland
    const char* platform_name = SDL_GetPlatform();
    SDL_Log("Detected platform %s.", platform_name);
    if (SDL_strcmp(platform_name, "Linux") == 0) {
        SDL_Environment *env = SDL_GetEnvironment();
        if (SDL_GetEnvironmentVariable(env, "WAYLAND_DISPLAY")) {
            SDL_SetHint("SDL_VIDEO_DRIVER", "wayland");
            SDL_Log("Use Wayland.");
        }
        else if (SDL_GetEnvironmentVariable(env, "DISPLAY")) {
            SDL_SetHint("SDL_VIDEO_DRIVER", "x11");
            SDL_Log("Use X11.");
        }
    }

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Reimu_CheckError("Could not initialize SDL video");
    SDL_Log("Initialized SDL video.");
    
    // Get primary display
    SDL_DisplayID primary_display_id = SDL_GetPrimaryDisplay();
    SDL_Reimu_CheckError("Could not get primary display");   
    int primary_display_modes_count;
    SDL_DisplayMode *primary_display_mode = SDL_GetFullscreenDisplayModes(primary_display_id, &primary_display_modes_count)[0];
    SDL_Reimu_CheckError("Could not get display modes from primary display");
    SDL_Log("Found primary display with %d display modes.", primary_display_modes_count);

    // Create window
    window = SDL_CreateWindow("SDL3-Vulkan Window", primary_display_mode->w, primary_display_mode->h, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    SDL_Reimu_CheckError("Could not create window");
    SDL_Log("Created window: %dx%d@%f.", primary_display_mode->w, primary_display_mode->h, primary_display_mode->refresh_rate);

    return SDL_APP_CONTINUE;
}
