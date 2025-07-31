#include <SDL3/SDL.h>

// https://www.studyplan.dev/sdl2/sdl2-error-handling
void SDL_Reimu_CheckError(void *appstate, char *potential_error_message) {
    const char* sdl_error = SDL_GetError();
    if (*sdl_error != '\0') {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s. SDL error: %s.", potential_error_message, sdl_error);
        SDL_Quit();
    }
}
