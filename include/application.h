#pragma once
#include <note.h>
#include <mutex>
#include <vector>

template <class T>
class APPLICATION
{
    const Uint16 samples = 1024;
    const Uint8 channels = 2;

    struct synthDataStruct
    {
        T frequency;
        T ticks;
        std::vector<note<T>> notes;
        instrument_bell<T> currentInstrument;
    };

    static std::mutex synthDataMutex;
    inline static synthDataStruct synthData;

    bool initialised = false;
    bool running = true;

    SDL_Renderer *renderer = nullptr;
    SDL_Window *window = nullptr;
    SDL_GLContext context;
    SDL_AudioDeviceID audioDevice;

    void initialise();
    void handleEvents();
    void addNote(SDL_KeyCode key);
    int keyCodeToKeyID(SDL_KeyCode keyCode);
    void removeNote();
    void changeInstrument();

public:
    APPLICATION(const int width, const int height);
    ~APPLICATION();
    void run();
    static void audioCallback(void *userdata, Uint8 *stream, int len);
};