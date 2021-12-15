#pragma once
#include <iostream>
#include <string>
#include <envelopeADSR.h>

template <class T>
class note;
template <class T>
class instrument_base
{
    static constexpr float pi = 3.1415926535;
    T volume;
    T maxLifeTime;
    envelopeADSR<T> env;
    const std::string name;

public:
    instrument_base(const T volume, const T maxLifeTime, envelopeADSR<T> env, const std::string name);
    virtual T sound(const T time, note<T> n, bool &noteFinished);
    T hz_to_rad(const T hertz);
    T oscSine(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSquare(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscTriange(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSaw(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0, const T steps = 50);
    T oscRand();
};

template <class T>
class instrument_bell : public instrument_base<T>
{
};

template <class T>
class instrument_harmonica : public instrument_base<T>
{
};

template <class T>
class instrument_piano : public instrument_base<T>
{
};

template <class T>
class instrument_guitar : public instrument_base<T>
{
};

template <class T>
class instrument_harp : public instrument_base<T>
{
};

template <class T>
class instrument_flute : public instrument_base<T>
{
};

template <class T>
class instrument_drum_kick : public instrument_base<T>
{
};

template <class T>
class instrument_drum_snare : public instrument_base<T>
{
};

template <class T>
class instrument_drum_hihat : public instrument_base<T>
{
};
