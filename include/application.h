#pragma once
#include <note.h>
#include <mutex>
#include <vector>
#include <algorithm>

template <class T>
class APPLICATION
{
    const Uint16 samples = 512;
    const Uint8 channels = 2;

    struct synthDataStruct
    {
        T frequency;
        T ticks;
        instrument_bell<T> currentInstrument;
        std::vector<note<T>> notes;
    };

    static std::mutex synthDataMutex;
    inline static synthDataStruct synthData;

    bool initialised = false;
    bool running = true;

    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    static APPLICATION *app;

    void initialise();
    void handleEvents();
    void addNote(SDL_KeyCode key);
    void removeNote(SDL_KeyCode key);
    void changeInstrument();
    int keyCodeToKeyID(SDL_KeyCode keyCode);
    APPLICATION(const int width, const int height);

public:
    static APPLICATION &instance(const int width, const int height);
    ~APPLICATION();
    void run();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
};