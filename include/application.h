#pragma once
#include <synth.h>
#include <map>
#include <mutex>

template <class T>
class APPLICATION
{
    struct synthDataStruct
    {
        T frequency;
        T ticks;
        Uint16 samples;
        std::shared_ptr<std::vector<note<T>>> notes;
    };

    static std::mutex synthDataMutex;
    static synthDataStruct synthData;
    synth<T> keyboardSynth;

    std::map<SDL_Keycode, bool> pressedKeys;

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