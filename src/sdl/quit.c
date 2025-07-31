#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

extern SDL_Window *window;

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("SDL_AppQuit");
    
    SDL_DestroyWindow(window);
    
    return;
}
