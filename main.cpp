#include <iostream>
#include <portaudio.h>


int main()
{
    std::cout << "test" << Pa_GetVersion();
    return 0;
}