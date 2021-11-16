#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO);
    std::cout << "TEST";
    SDL_Quit();
    return 0;
}