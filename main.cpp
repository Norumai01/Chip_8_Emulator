#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 1680, HEIGHT = 1050;

// Create an public accessible class for window screen and rendering graphic.
struct SDLContext {
    SDL_Window* window;
    SDL_Renderer* renderer;
};

// Starts up everything, if mess up, return message. 
SDLContext InitializeSDL() {
    SDLContext context = {NULL, NULL};
    //SDL_setenv("SDL_VIDEODRIVER", "invalid_driver", 1); // Test error checker.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL initialization failed: %s\n", SDL_GetError());
        return context;
    }

    context.window = SDL_CreateWindow("Hello SDL WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (!context.window) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return context;
    }

    context.renderer = SDL_CreateRenderer(context.window, -1, SDL_RENDERER_ACCELERATED);
    if (!context.renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return context;
    }

    return context;
}

void EventLoop(SDLContext& context) {
    SDL_Event event;
    
    // Set color (white)
    SDL_SetRenderDrawColor(context.renderer, 255, 255, 255, 255);
    // Fill the entire rendering target with current color.
    SDL_RenderClear(context.renderer);
    // Present the renderer
    SDL_RenderPresent(context.renderer);
    
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) break;
            if (SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) break;
            }
        }
    }
}

void CleanUp(SDLContext& context) {
    // Clear up resource of renderer.
    SDL_DestroyRenderer(context.renderer);
    context.renderer = NULL;
    // Clear up resource of winddow.
    SDL_DestroyWindow(context.window);
    context.window = NULL;
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    SDLContext context = InitializeSDL();
    if (!context.window || !context.renderer) {
        CleanUp(context);
        return 1;
    }
    
    EventLoop(context);
    CleanUp(context);

    return EXIT_SUCCESS;
}