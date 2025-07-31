// https://wiki.libsdl.org/SDL3/README-main-functions

#include <vulkan/vulkan.h>

#define SDL_MAIN_USE_CALLBACKS
#define SDL_WINDOW_ALLOW_HIGHDPI_renamed_SDL_WINDOW_HIGH_PIXEL_DENSITY
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_vulkan.h>
#include <vulkan/vulkan.h>

SDL_DisplayMode* Get_Display_Mode_From_Id(SDL_DisplayID display_id) {
    int display_modes_count;
    SDL_DisplayMode *display_mode = SDL_GetFullscreenDisplayModes(display_id, &display_modes_count)[0];
    if (display_modes_count <= 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get display modes from display with ID %d: %s.", display_id, SDL_GetError());
        SDL_AppQuit(NULL, SDL_APP_FAILURE);
    }
    return display_mode;
}

bool Change_Window_Display_Mode(SDL_Window *window, SDL_DisplayMode *display_mode) {
    //SDL_SetWindowSize(window, display_mode->w, display_mode->h);
    if (SDL_SetWindowFullscreenMode(window, display_mode) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not set new display mode: %s.", SDL_GetError());
        return false;
    }
    SDL_SyncWindow(window);
    SDL_Log("Changed window to new display mode: %dx%d@%f.", display_mode->w, display_mode->h, display_mode->refresh_rate);
    return true;
}

SDL_Window *window;
SDL_DisplayID current_display_id;
SDL_DisplayMode *current_display_mode;

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
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL video: %s.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Initialized SDL video.");
    
    // Get primary display
    SDL_DisplayID primary_display_id = SDL_GetPrimaryDisplay();
    if (primary_display_id == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get primary display: %s.", SDL_GetError());
    }    
    int primary_display_modes_count;
    SDL_DisplayMode *primary_display_mode = SDL_GetFullscreenDisplayModes(primary_display_id, &primary_display_modes_count)[0];
    if (primary_display_modes_count <= 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not get display modes from display with ID %d: %s.", primary_display_id, SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Found primary display with ID %d and %d display modes. Picking %dx%d@%f.", primary_display_id, primary_display_modes_count, primary_display_mode->w, primary_display_mode->h, primary_display_mode->refresh_rate);
    current_display_id = primary_display_id;
    current_display_mode = primary_display_mode;

    // Create window
    window = SDL_CreateWindow("SDL3-Vulkan Window", primary_display_mode->w, primary_display_mode->h, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_VULKAN | SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Created borderless fullscreen window with primary display properties.");
    
    // Convert window to Fullscreen Exclusive
    if (SDL_SetWindowFullscreen(window, true) == false) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not convert window to exclusive fullscreen: %s.", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Log("Converted window to exclusive fullscreen mode.");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    //SDL_Log("SDL_AppIterate");

    // Wayland requires a constant update loop for a window to show, 
    // so SDL_CreateWindow() does nothing on its own.
    // https://github.com/libsdl-org/SDL/issues/6074

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    //SDL_Log("SDL_AppEvent");

    switch (event->type)
    {
        case SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED:
            SDL_Log("SDL_EVENT_DISPLAY_DESKTOP_MODE_CHANGED");
            SDL_DisplayMode *new_display_mode = Get_Display_Mode_From_Id(event->display.displayID);
            if (Change_Window_Display_Mode(window, new_display_mode) == false) {
                return SDL_APP_FAILURE;
            }
            break;
        
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit");
    
    SDL_DestroyWindow(window);
    
    return;
}
