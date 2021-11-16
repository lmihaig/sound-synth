#pragma once
#include <portaudio.h>

class synth
{
    PaStream *stream;

public:
    synth(PaStream *, PaStreamCallback, osc);
    ~synth();
};