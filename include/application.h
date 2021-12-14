#pragma once
#include <SDL.h>
#include <synth.h>
class APPLICATION
{
    synth<double> keyboardsynth;
    synth<double> sequencer;

    std::vector<int> userdata;
    const unsigned int sampleRate = 48000;
    const unsigned int frequencyBins = 512;
    const Uint8 channels = 2;
    const Uint16 bufferSize = 1024;

    bool initialised = false;
    bool running = true;

    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    void initialise();
    void handleEvents();

public:
    APPLICATION(const int width, const int height);
    ~APPLICATION();
    void run();
    void update();
    static void audiocallback(void *userdata, Uint8 *stream, int len);
};