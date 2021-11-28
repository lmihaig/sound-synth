#include <application.h>
#include <synth.h>
#include <iostream>

APPLICATION::APPLICATION(size_t width, size_t height) : initialised{false}, window{nullptr}, running{false}
{
    initialise();

    window = SDL_CreateWindow("sound-synth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

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
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    initialised = true;
}

void APPLICATION::run()
{

    running = true;
    while (running)
    {
        handleEvents();
    }
}

void APPLICATION::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // Detect which key is pressed down
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_a:
                std::cout << "A IS PRESSED\n";
                break;
            case SDLK_s:
                std::cout << "S IS PRESSED\n";
                break;
            }
            break;

        // Detect which key has been released
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
                // Select which instrument to use
                // case SDLK_1:
                //     changeInstrument(1);
                //     break;
                // case SDLK_2:
                //     changeInstrument(2);
                //     break;
                // case SDLK_3:
                //     changeInstrument(3);
                //     break;
                // case SDLK_4:
                //     changeInstrument(4);
                //     break;
                // case SDLK_5:
                //     changeInstrument(5);
                //     break;
                // case SDLK_6:
                //     changeInstrument(6);
                //     break;
                // case SDLK_7:
                //     changeInstrument(7);
                //     break;
                // case SDLK_8:
                //     changeInstrument(8);
                //     break;
                // case SDLK_9:
                //     changeInstrument(9);
                //     break;

            case SDLK_a:
                std::cout << "A IS RELEASED\n";
                break;
            case SDLK_s:
                std::cout << "S IS RELEASED\n";
                break;
            }
            break;

        // Detect if the user tries to close the window and if so stop running, which will call the destructor
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                running = false;
                break;
            }
            break;
        }
    }
}