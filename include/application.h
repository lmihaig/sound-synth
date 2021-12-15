#pragma once
#include <synth.h>
#include <map>

template <class T>
class APPLICATION
{
    struct synthDataStruct
    {
        T frequency;
        Uint8 channels;
        Uint16 samples;
        int ticks;
        std::shared_ptr<std::vector<note<T>>> notes;
        std::shared_ptr<std::vector<std::vector<T>>> voiceBuffers;
    };

    synth<T> keyboardSynth;
    synthDataStruct synthData;

    std::map<SDL_Keycode, bool> pressedKeys;
    std::vector<std::vector<T>> voiceBuffers;
    std::shared_ptr<std::vector<note<T>>> notes;

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