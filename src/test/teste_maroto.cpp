#include <SDL/SDL.h>
#include <SDL/SDL_video.h>
#include <chrono>
#include <thread>

void setUpSurface(SDL_Surface* surface) {

}

void drawImage(SDL_Surface* surface, uint8_t delta) {
    for(int i = 0; i < 144; i++)
        for(int j = 0; j < 160; j++)
            ((uint8_t*)surface->pixels)[(160*i) + j] = i + delta;
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_SetVideoMode(160, 144, 8, 0);
    SDL_Surface* surface = SDL_GetVideoSurface();

    setUpSurface(surface);

    SDL_Event e;
    bool quit = false;
    uint8_t delta = 0;
    while( quit == false )
    { 
        while( SDL_PollEvent( &e ) )
        { 
            if( e.type == SDL_QUIT ) 
                quit = true; 
        }
        drawImage(surface, delta++);
        SDL_UpdateRect(surface, 0, 0, 160, 144);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    SDL_Quit();
}