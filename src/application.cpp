#include <application.h>
#include <synth.h>
#include <iostream>
// , synth{Synth(maxPolyphony)}
APPLICATION::APPLICATION(size_t width, size_t height) : initialised{false}, window{nullptr}, running{false}
{
    initialise();

    window = SDL_CreateWindow("sound-synth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window)
    {
        std::cerr << "Application's window creation failed: " << SDL_GetError() << "\n";
        return;
    }

    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;
    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desired, &obtained, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
}

APPLICATION::~APPLICATION()
{
    SDL_GL_DeleteContext(context);
    SDL_CloseAudioDevice(audioDevice);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void APPLICATION::initialise()
{
    try
    {
        if (initialised)
            throw 99;
    }
    catch (int x)
    {
        std::cerr << "Application already initialised: " << SDL_GetError() << "\n";
    }

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    try
    {
        if (result != 0)
            throw 100;
    }
    catch (int x)
    {
        std::cerr << "Application's initialisation failed: " << SDL_GetError() << "\n";
    }
    initialised = true;
}

void APPLICATION::run()
{

    try
    {
        if (!initialised)
            throw 101;
    }
    catch (int x)
    {
        std::cerr << "Application is trying to run but is not initialised" << SDL_GetError() << "\n";
    }

    running = true;
    while (running)
    {
        // handleEvents();
    }
}