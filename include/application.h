#pragma once
#include <note.h>
#include <map>
#include <mutex>
#include <vector>

template <class T>
class APPLICATION
{
    struct synthDataStruct
    {
        T frequency = 48000;
        T ticks;
        std::vector<note<T>> notes;
    };

    static std::mutex synthDataMutex;
    inline static synthDataStruct synthData;

    std::map<SDL_Keycode, bool> pressedKeys;

    bool initialised = false;
    bool running = true;

    const Uint16 samples = 1024;
    const Uint8 channels = 2;

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