#include <envelopeADSR.h>

template <class T>
envelopeADSR<T>::envelopeADSR(T attackLevel, T attackTime, T decayTime, T sustainLevel, T releaseTime) : attackLevel{attackLevel}, attackTime{attackTime}, decayTime{decayTime}, sustainLevel{sustainLevel}, releaseTime{releaseTime}
{
}

template <class T>
T envelopeADSR<T>::amplitude(const T currentTime, const T noteOnTime, const T noteOffTime)
{
    T amplitude = 0.0f;
    T releaseAmplitude = 0.0f;

    // ADS Phases -> Note is on
    if (noteOnTime > noteOffTime)
    {
        T noteLifetime = currentTime - noteOnTime;

        // Attack Phase
        if (noteLifetime <= attackTime)
            amplitude = (noteLifetime / attackTime) * attackLevel;

        // Decay Phase
        if (noteLifetime > attackTime && noteLifetime <= (attackTime + decayTime))
            amplitude = ((noteLifetime - attackTime) / decayTime) * (sustainLevel - attackLevel) + attackLevel;

        // Sustain Phase
        if (noteLifetime > (attackTime + decayTime))
            amplitude = sustainLevel;
    }
    // Release Phase -> Note is off
    else
    {
        T noteLifetime = noteOffTime - noteOnTime;

        if (noteLifetime <= attackTime)
            releaseAmplitude = (noteLifetime / attackTime) * attackLevel;

        if (noteLifetime > attackTime && noteLifetime <= (attackTime + decayTime))
            releaseAmplitude = ((noteLifetime - attackTime) / decayTime) * (sustainLevel - attackLevel) + attackLevel;

        if (noteLifetime > (attackTime + decayTime))
            releaseAmplitude = sustainLevel;

        amplitude = ((currentTime - noteOffTime) / releaseTime) * (0.0f - releaseAmplitude) + releaseAmplitude;
    }

    // Amplitude is too low, don't output anything
    if (amplitude <= 0.001f)
        amplitude = 0.0f;

    return amplitude;
}
