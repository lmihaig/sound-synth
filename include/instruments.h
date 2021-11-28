#pragma once
#include <iostream>
#include <envelopeADSR.h>

template <class T>
class instrument_base
{
    T volume;
    envelopeADSR<T> env;

public:
    static const std::string name;
    static const unsigned int id;
    instrument_base();
    virtual T sound(const T time);
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
