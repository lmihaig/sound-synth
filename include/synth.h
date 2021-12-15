#pragma once
#include <note.h>
#include <vector>

template <class T>
class synth
{
public:
    std::vector<note<T>> synthData;
    void synthprint(int n);
};