#include <synth.h>
#include <portaudio.h>
#include <iostream>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (256)

synth::synth(PaStream *stream, PaStreamCallback paCallback, osc oscillators)
{
    this->stream = stream;
    PaStreamParameters outputParameters;
    PaError err;

    //  initialise PortAudio
    err = Pa_Initialize();
    if (err != paNoError)
    {
        std::cout << "Failed to initialize\n";
    }

    // get output device
    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice)
    {
        std::cout << "No default output device\n";
    }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = 0.050;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    // register a stream for the output device
    err = Pa_OpenStream(&stream, NULL, &outputParameters, SAMPLE_RATE,
                        FRAMES_PER_BUFFER, paNoFlag, paCallback, &oscillators);
    if (err != paNoError)
    {
        std::cout << "Failed to open stream\n ";
    }

    // starts the stream
    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        std::cout << "StartStream failed\n";
    }
}

synth::~synth()
{
    // stops and closes the stream

    PaError err;
    err = Pa_StopStream(this->stream);
    if (err != paNoError)
    {
        std::cout << "StopStream failed\n";
    }

    err = Pa_CloseStream(this->stream);
    if (err != paNoError)
    {
        std::cout << "Failed to close stream\n";
    }
    Pa_Terminate();
}
