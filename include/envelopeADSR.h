#pragma once

// Type determines the quality of the audio short < int < float < double
template <class T>
class envelopeADSR
{
    T attackLevel;
    T attackTime;
    T decayTime;
    T sustainLevel;
    T releaseTime;

public:
    envelopeADSR(T attackLevel = 1.f, T attackTime = .15f, T decayTime = .2f, T sustainLevel = .8f, T releaseTime = .65f);
    virtual T amplitude(const T currentTime, const T noteOnTime, const T noteOffTime);
};