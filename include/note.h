#pragma once
#include <instruments.h>

template <typename T>
class note;

template <class T>
std::ostream &operator<<(std::ostream &os, const note<T> &n);
template <class T>
class note
{
public:
    int id;
    T on;
    T off;
    bool active;
    instrument_base<T> timbre;
    note(int id = 0, T on = 0.0, T off = 0.0, bool active = false, instrument_base<T> &timbre = nullptr);
    friend std::ostream &operator<<(std::ostream &os, const note<T> &n);
};