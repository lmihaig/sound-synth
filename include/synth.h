#pragma once
#include <note.h>
#include <vector>
#include <SDL.h>

template <class T>
class synth
{
public:
    const int frequency = 48000;
    const Uint8 channels = 2; // Stereo sound
    const Uint16 samples = 1024;
    int ticks;
    std::shared_ptr<std::vector<note<T>>> notes;
};