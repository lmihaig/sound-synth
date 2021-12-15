#pragma once
#include <instruments.h>
template <class T>
class note
{
public:
    unsigned int id;
    T on;
    T off;
    bool active;
    instrument_base<T> timbre;
    note(unsigned int id = 0, T on = 0.0, T off = 0.0, bool active = false, instrument_base<T> timbre = nullptr);
};