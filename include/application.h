#pragma once
#include <SDL.h>

class APPLICATION
{
    unsigned int maxPolyphony = 16;
    unsigned int channels = 2;
    unsigned int sampleRate = 48000;
    unsigned int frequencyBins = 512;

    bool initialised = false;
    bool running = true;

    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    void initialise();
    void handleEvents();

public:
    APPLICATION(size_t width, size_t height);
    ~APPLICATION();
    void run();
    void update();
};