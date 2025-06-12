#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Tic Tac Toe",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 200, 200, 255, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
