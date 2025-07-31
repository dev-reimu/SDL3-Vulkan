// https://wiki.libsdl.org/SDL3/README-main-functions

#define SDL_MAIN_USE_CALLBACKS
#define SDL_WINDOW_ALLOW_HIGHDPI_renamed_SDL_WINDOW_HIGH_PIXEL_DENSITY
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_vulkan.h>

#include <vulkan/vulkan.h>

#include <string.h>

#include "../headers/reimu-sdl-extensions.h"
#include "../headers/global_variables.h"

extern SDL_Window *window;

char output[2048];

char *fmt_int(char *str, int i) {
    int i_copy = i;
    int int_length = 0;
    while (i_copy != 0) {
        i_copy /= 10;
        int_length++;
    }

    char extended_str[strlen(str)+int_length];
    strcpy(extended_str, str);
    SDL_Log("str = %s", str);

    char int_buffer[int_length];
    SDL_itoa(i, int_buffer, 10);

    char *result = (char*)SDL_malloc(sizeof(str)+sizeof(int_buffer)); 
    strcat(extended_str, int_buffer);

    return result;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    SDL_Log("SDL_AppInit\n");

    // Linux specific -> Select X11 or Wayland
    const char* platform_name = SDL_GetPlatform();
    SDL_Log("Detected platform %s.", platform_name);
    if (SDL_strcmp(platform_name, "Linux") == 0) {
        SDL_Environment *env = SDL_GetEnvironment();
        if (SDL_GetEnvironmentVariable(env, "WAYLAND_DISPLAY")) {
            SDL_SetHint("SDL_VIDEO_DRIVER", "wayland");
            SDL_Log("Using Wayland.");
        }
        else if (SDL_GetEnvironmentVariable(env, "DISPLAY")) {
            SDL_SetHint("SDL_VIDEO_DRIVER", "x11");
            SDL_Log("Using X11.");
        }
    }

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Reimu_CheckError("Successfully initialized SDL video", "Failed to initialize SDL video");
    
    // Find primary display
    SDL_DisplayID primary_display_id = SDL_GetPrimaryDisplay();
    SDL_Reimu_CheckError(fmt_int("Successfully found primary display with ID ", primary_display_id), 
                        "Failed to find primary display");

    // Get primary display properties
    int primary_display_modes_count;
    SDL_DisplayMode *primary_display_mode = SDL_GetFullscreenDisplayModes(primary_display_id, &primary_display_modes_count)[0];
    SDL_Reimu_CheckError("Successfully found {primary_display_modes_count} display modes from primary display", 
                        "Failed to get display modes from primary display");

    // Create window
    window = SDL_CreateWindow("SDL3-Vulkan Window", primary_display_mode->w, primary_display_mode->h, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    SDL_Reimu_CheckError("Successfully created window with {resolution@refreshrate} resolution", 
                        "Failed to create window");

    return SDL_APP_CONTINUE;
}
