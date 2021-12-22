#pragma once
#include <iostream>
#include <string>
#include <envelopeADSR.h>

template <class T>
class note;

template <typename T>
class instrument_base;

template <class T>
std::ostream &operator<<(std::ostream &os, const instrument_base<T> &n);

template <class T>
class instrument_base
{
    static constexpr float pi = 3.1415926535;
    T volume;
    T maxLifeTime;
    envelopeADSR<T> env;
    std::string name;

public:
    instrument_base(const T volume, const T maxLifeTime, envelopeADSR<T> env, const std::string name);
    virtual T sound(const T time, note<T> &n, bool &noteFinished);
    T hz_to_rad(const T hertz);
    T oscSine(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSquare(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscTriangle(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSaw(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0, const T steps = 50);
    T oscRand();

    T scale(const int noteID);

    bool operator==(const instrument_base<T> &rhs) const;
    bool operator!=(const instrument_base<T> &rhs) const;
    instrument_base<T> &operator=(const instrument_base<T> &copy);
    friend std::ostream &operator<<(std::ostream &os, const instrument_base<T> &inst);
};

template <class T>
class instrument_bell : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished)
    {
        T amp = env.amplitude(time, n.on, n.off);
        if (amp <= 0.0)
            noteFinished = true;

        T sound = 1.00 * oscSine(time - n.on, scale(n.id + 12), 5.0, 0.001) + 0.50 * oscSine(time - n.on, scale(n.id + 24)) + 0.25 * oscSine(time - n.on, scale(n.id + 36));
    };

public:
    instrument_bell() : instrument_base(1.0, 3.0, envelopeADSR(0.01, 1.0, 0.0, 1.0), "Bell"){};
};

template <class T>
class instrument_harmonica : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_piano : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_guitar : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_harp : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_flute : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_drum_kick : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_drum_snare : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};

template <class T>
class instrument_drum_hihat : public instrument_base<T>
{
    T sound(const T time, note<T> &n, bool &noteFinished);
};
