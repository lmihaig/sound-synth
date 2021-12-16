#include <application.h>

template <class T>
APPLICATION<T>::APPLICATION(const int width, const int height)
{
    initialise();

    window = SDL_CreateWindow("sound-synth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    synthData.frequency = keyboardSynth.frequency;
    synthData.samples = keyboardSynth.samples;
    synthData.ticks = 0;
    synthData.notes = keyboardSynth.notes;

    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;

    SDL_zero(desired);
    desired.silence = 0;
    desired.freq = keyboardSynth.frequency;
    desired.channels = keyboardSynth.channels;
    desired.samples = keyboardSynth.samples;
    desired.userdata = &synthData;
    desired.callback = audioCallback;
    desired.format = AUDIO_S32SYS;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 1);

    // Default state is paused, this unpauses it
    SDL_PauseAudioDevice(audioDevice, 0);
}
template <class T>
APPLICATION<T>::~APPLICATION()
{
    SDL_GL_DeleteContext(context);
    SDL_CloseAudioDevice(audioDevice);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
template <class T>
void APPLICATION<T>::initialise()
{
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);

    initialised = true;
}
template <class T>
void APPLICATION<T>::run()
{

    running = true;
    while (running)
    {
        handleEvents();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}
template <class T>
void APPLICATION<T>::handleEvents()
{
    std::lock_guard<std::mutex> guard(synthDataMutex);
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        // Detect which key is pressed down
        case SDL_KEYDOWN:
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
            case SDLK_z:
                std::cout << "Z IS PRESSED\n";
                break;
            case SDLK_s:
                std::cout << "S IS PRESSED\n";
                break;
            case SDLK_x:
                std::cout << "X IS PRESSED\n";
                break;
            case SDLK_c:
                std::cout << "C IS PRESSED\n";
                break;
            case SDLK_f:
                std::cout << "F IS PRESSED\n";
                break;
            case SDLK_v:
                std::cout << "V IS PRESSED\n";
                break;
            case SDLK_g:
                std::cout << "G IS PRESSED\n";
                break;
            case SDLK_b:
                std::cout << "B IS PRESSED\n";
                break;
            case SDLK_n:
                std::cout << "N IS PRESSED\n";
                break;
            case SDLK_j:
                std::cout << "J IS PRESSED\n";
                break;
            case SDLK_m:
                std::cout << "M IS PRESSED\n";
                break;
            case SDLK_k:
                std::cout << "K IS PRESSED\n";
                break;
            case SDLK_COMMA:
                std::cout << ", IS PRESSED\n";
                break;
            case SDLK_l:
                std::cout << "L IS PRESSED\n";
                break;
            case SDLK_PERIOD:
                std::cout << ". IS PRESSED\n";
                break;
            case SDLK_SLASH:
                std::cout << "/ IS PRESSED\n";
                break;
            }
            break;

        // Detect which key has been released
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_z:
                std::cout << "Z IS RELEASED\n";
                break;
            case SDLK_s:
                std::cout << "S IS RELEASED\n";
                break;
            case SDLK_x:
                std::cout << "X IS RELEASED\n";
                break;
            case SDLK_c:
                std::cout << "C IS RELEASED\n";
                break;
            case SDLK_f:
                std::cout << "F IS RELEASED\n";
                break;
            case SDLK_v:
                std::cout << "V IS RELEASED\n";
                break;
            case SDLK_g:
                std::cout << "G IS RELEASED\n";
                break;
            case SDLK_b:
                std::cout << "B IS RELEASED\n";
                break;
            case SDLK_n:
                std::cout << "N IS RELEASED\n";
                break;
            case SDLK_j:
                std::cout << "J IS RELEASED\n";
                break;
            case SDLK_m:
                std::cout << "M IS RELEASED\n";
                break;
            case SDLK_k:
                std::cout << "K IS RELEASED\n";
                break;
            case SDLK_COMMA:
                std::cout << ", IS RELEASED\n";
                break;
            case SDLK_l:
                std::cout << "L IS RELEASED\n";
                break;
            case SDLK_PERIOD:
                std::cout << ". IS RELEASED\n";
                break;
            case SDLK_SLASH:
                std::cout << "/ IS RELEASED\n";
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

template <class T>
void APPLICATION<T>::audioCallback(void *userdata, Uint8 *stream, int len)
{
    std::lock_guard<std::mutex> guard(synthDataMutex);
    synthDataStruct *synthData = reinterpret_cast<synthDataStruct *>(userdata);
    T secondPerTick = 1.0 / static_cast<T>(synthData->frequency);
    int sizePerSample = static_cast<int>(sizeof(T));

    SDL_memset(stream, 0, len);
    T *buffer = reinterpret_cast<T *>(stream);

    for (int i = 0; i < len / sizePerSample; i++)
    {
        T mixedOutput = 0;
        for (auto &n : *synthData->notes)
        {
            bool noteFinished = false;
            // T sound = 0;
            // if (n.timbre != nullptr)
            //     sound = n.timbre.sound(synthData->ticks, n, noteFinished);
            mixedOutput += n.timbre.sound(synthData->ticks, n, noteFinished);
            if (noteFinished)
                n.active = false;
        }

        buffer[i] = mixedOutput;
        buffer[i + 1] = mixedOutput;
    }
    synthData->ticks = synthData->ticks + secondPerTick;
}

template class APPLICATION<short>;
template class APPLICATION<int>;
template class APPLICATION<float>;
template class APPLICATION<double>;