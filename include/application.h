#pragma once
#include <SDL.h>
#include <synth.h>
#include <note.h>
#include <map>
#include <vector>

template <class T>
class APPLICATION
{
    synth<T> keyboardSynth;

    std::map<SDL_Keycode, bool> pressedKeys;
    std::vector<vector<T>> voiceBuffers;
    std::shared_ptr<std::vector<note<T>>> notes;
    const unsigned int maxVoices = 16;
    const unsigned int frequency = 48000;
    const Uint8 channels = 2; // Stereo sound
    const Uint16 samples = 1024;

    bool initialised = false;
    bool running = true;

    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    void initialise();
    void handleEvents();

public:
    APPLICATION(const int width, const int height);
    ~APPLICATION();
    void run();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
};