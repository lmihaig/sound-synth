#pragma once
#include <note.h>
#include <vector>

// Type determines the quality of the audio short < int < float < double
template <class T>
class synth
{
public:
    void synthprint(int n);
};