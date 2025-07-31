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
    SDL_Reimu_CheckError("Failed to initialize SDL video.");
    SDL_Log("Successfully initialized SDL video.");
    
    // Find primary display
    SDL_DisplayID primary_display_id = SDL_GetPrimaryDisplay();
    SDL_Reimu_CheckError("Failed to find primary display.");
    SDL_Log("Successfully found primary display with ID %d.", primary_display_id);

    // Get display modes from primary display
    int primary_display_modes_count;
    SDL_DisplayMode **primary_display_mode = SDL_GetFullscreenDisplayModes(primary_display_id, &primary_display_modes_count);
    SDL_Reimu_CheckError("Failed to get display modes from primary display.");
    SDL_Log("Successfully found %d display modes: ", primary_display_modes_count);
    for (int i = 0; i < primary_display_modes_count; i++) {
        SDL_Log("%d. %dx%d@%d", i, primary_display_mode[i]->w, primary_display_mode[i]->h, (int)primary_display_mode[i]->refresh_rate);
    }

    // Create window
    window = SDL_CreateWindow("SDL3-Vulkan Window", primary_display_mode[0]->w, primary_display_mode[0]->h, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    SDL_Reimu_CheckError("Failed to create window.");
    SDL_Log("Successfully created window: %dx%d@%d.", primary_display_mode[0]->w, primary_display_mode[0]->h, (int)primary_display_mode[0]->refresh_rate);

    return SDL_APP_CONTINUE;
}
