#pragma once
#include <iostream>
#include <string>
#include <envelopeADSR.h>

template <class T>
class note;

template <class T>
class instrument_base;

template <class T>
std::ostream &operator<<(std::ostream &os, const instrument_base<T> &n);

template <class T>
class instrument_base
{
protected:
    static constexpr float pi = 3.1415926535;
    T maxLifeTime;
    envelopeADSR<T> env;
    std::string name;

public:
    friend std::ostream &operator<<<>(std::ostream &os, const instrument_base<T> &inst);
    instrument_base(const T maxLifeTime, envelopeADSR<T> env, const std::string name);
    instrument_base(const instrument_base<T> &copy);
    bool operator==(const instrument_base<T> &rhs) const;
    bool operator!=(const instrument_base<T> &rhs) const;
    instrument_base<T> &operator=(const instrument_base<T> &copy);

    virtual T sound(const T time, note<T> &n, bool &noteFinished);
    T hz_to_rad(const T hertz);
    T oscSine(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSquare(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscTriangle(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0);
    T oscSaw(const T time, const T frequency, const T lowfreq = 0, const T lowamp = 0, const T steps = 50);
    T oscRand();

    T scale(const int noteID);
};

template <class T>
class instrument_bell : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        T amp = this->env.amplitude(time, n.on, n.off);
        if (amp <= 0.0)
            noteFinished = true;

        T sound = 1.00 * this->oscSine(time - n.on, this->scale(n.id + 12), 5.0, 0.001) + 0.50 * this->oscSine(time - n.on, this->scale(n.id + 24)) + 0.25 * this->oscSine(time - n.on, this->scale(n.id + 36));

        return sound * amp;
    };

    instrument_bell() : instrument_base<T>(3.0, envelopeADSR<T>(1.0, 0.01, 1.0, 0.0, 1.0), "Bell"){};
};

template <class T>
class instrument_harmonica : public instrument_base<T>
{
public:
    T sound(const T time, note<T> &n, bool &noteFinished) override
    {
        return 0;
    };

    instrument_harmonica() : instrument_base<T>(1, -1.0, envelopeADSR<T>(1, 0, 1.0, 0.95, 0.1), "Harmonica"){};
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
