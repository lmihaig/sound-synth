#include <SDL.h>
#include <iostream>

// need argc and argv for windows compatibility 
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_AUDIO);
    std::cout << "TEST";
    SDL_Quit();
    return 0;
}