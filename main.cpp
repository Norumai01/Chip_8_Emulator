#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 1000, HEIGHT = 1000;

SDL_Window* InitializeSDL() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello SDL WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return window;
    }
    return window;
}

void EventLoop(SDL_Window* window) {
    SDL_Event event;
    
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) break;
            if (SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) break;
            }
        }
    }
}

void CleanUp(SDL_Window* window) {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    SDL_Window* window = InitializeSDL();
    if (window == NULL) {
        return 1;
    }
    
    EventLoop(window);
    CleanUp(window);

    return EXIT_SUCCESS;
}