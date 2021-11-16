#include <SDL.h>
#include <iostream>

int main()
{
    SDL_Init(SDL_INIT_AUDIO);
    std::cout << "TEST";
    SDL_Quit();
    return 0;
}