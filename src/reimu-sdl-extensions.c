#include <SDL3/SDL.h>

#include <string.h>

// https://www.studyplan.dev/sdl2/sdl2-error-handling
void SDL_Reimu_CheckError(const char* success_message, const char *error_message) {
    const char* sdl_error = SDL_GetError();
    if (*sdl_error == '\0') {
        SDL_Log("%s.", success_message);
    }
    else {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s. SDL error: %s.", error_message, sdl_error);
        SDL_Quit();
    }
}
