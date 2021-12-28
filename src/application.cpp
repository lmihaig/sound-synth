#include <application.h>

template <class T>
std::mutex APPLICATION<T>::synthDataMutex;

template <class T>
APPLICATION<T> *APPLICATION<T>::app = nullptr;

template <class T>
APPLICATION<T> &APPLICATION<T>::instance(const int width, const int height)
{
    if (app == nullptr)
        app = new APPLICATION(width, height);
    return *app;
}

template <class T>
APPLICATION<T>::APPLICATION(const int width, const int height)
{
    initialise();

    window = SDL_CreateWindow("sound-synth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    synthData.frequency = 48000;
    synthData.ticks = 0;

    SDL_AudioSpec desired;
    SDL_AudioSpec obtained;

    SDL_zero(desired);
    desired.silence = 0;
    desired.freq = synthData.frequency;
    desired.channels = channels;
    desired.samples = samples;
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
                addNote(SDLK_z);
                break;
            case SDLK_s:
                addNote(SDLK_s);
                break;
            case SDLK_x:
                addNote(SDLK_x);
                break;
            case SDLK_c:
                addNote(SDLK_c);
                break;
            case SDLK_f:
                addNote(SDLK_f);
                break;
            case SDLK_v:
                addNote(SDLK_v);
                break;
            case SDLK_g:
                addNote(SDLK_g);
                break;
            case SDLK_b:
                addNote(SDLK_b);
                break;
            case SDLK_n:
                addNote(SDLK_n);
                break;
            case SDLK_j:
                addNote(SDLK_j);
                break;
            case SDLK_m:
                addNote(SDLK_m);
                break;
            case SDLK_k:
                addNote(SDLK_k);
                break;
            case SDLK_COMMA:
                addNote(SDLK_COMMA);
                break;
            case SDLK_l:
                addNote(SDLK_l);
                break;
            case SDLK_PERIOD:
                addNote(SDLK_PERIOD);
                break;
            case SDLK_SLASH:
                addNote(SDLK_SLASH);
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
int APPLICATION<T>::keyCodeToKeyID(SDL_KeyCode key)
{
    int id;
    switch (key)
    {
    case SDLK_z:
        id = 0;
        break;
    case SDLK_s:
        id = 1;
        break;
    case SDLK_x:
        id = 2;
        break;
    case SDLK_c:
        id = 3;
        break;
    case SDLK_f:
        id = 4;
        break;
    case SDLK_v:
        id = 5;
        break;
    case SDLK_g:
        id = 6;
        break;
    case SDLK_b:
        id = 7;
        break;
    case SDLK_n:
        id = 8;
        break;
    case SDLK_j:
        id = 9;
        break;
    case SDLK_m:
        id = 10;
        break;
    case SDLK_k:
        id = 12;
        break;
    case SDLK_COMMA:
        id = 13;
        break;
    case SDLK_l:
        id = 14;
        break;
    case SDLK_PERIOD:
        id = 15;
        break;
    case SDLK_SLASH:
        id = 16;
        break;
    }

    return 64 + id;
}

template <class T>
void APPLICATION<T>::addNote(SDL_KeyCode key)
{
    note<T> newNote(keyCodeToKeyID(key), synthData.ticks, 0, true);
    std::cout << newNote << " was played on " << synthData.currentInstrument;
    synthData.notes.emplace_back(newNote);
}

template <class T>
T APPLICATION<T>::clip(T sample)
{
    if (sample >= 0.0)
        return fmin(sample, 1.0);
    else
        return fmax(sample, 1.0);
}

template <class T>
void APPLICATION<T>::audioCallback(void *userdata, Uint8 *stream, int len)
{

    std::lock_guard<std::mutex> guard(synthDataMutex);
    synthDataStruct *curSynthData = reinterpret_cast<synthDataStruct *>(userdata);
    T secondPerTick = 1.0 / static_cast<T>(curSynthData->frequency);
    int sizePerSample = static_cast<int>(sizeof(T));

    SDL_memset(stream, 0, len);
    T *buffer = reinterpret_cast<T *>(stream);

    for (int i = 0; i < len / sizePerSample; i++)
    {
        T mixedOutput = 0;
        for (auto &n : curSynthData->notes)
        {
            bool noteFinished = false;
            mixedOutput += curSynthData->currentInstrument.sound(curSynthData->ticks, n, noteFinished);
            if (noteFinished)
                n.active = false;
        }
        // std::cout << mixedOutput << "\n";
        mixedOutput = clip(mixedOutput);
        buffer[i] = mixedOutput;
        buffer[i + 1] = mixedOutput;
    }
    curSynthData->ticks = curSynthData->ticks + secondPerTick;
}

template class APPLICATION<float>;
template class APPLICATION<double>;