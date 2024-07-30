#include <SDL2/SDL.h>

void setUpSurface(SDL_Surface* surface) {

}

void drawImage(SDL_Surface* surface) {
    for(int i = 0; i < 144; i++)
        for(int j = 0; j < 160; j++)
            ((uint8_t*)surface->pixels)[(160*i) + j] = (uint8_t)((i + 1) / 36);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Maroto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 160, 144, SDL_WINDOW_SHOWN);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    setUpSurface(surface);
    drawImage(surface);
    SDL_UpdateWindowSurface(window);

    SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

    SDL_Quit();
}