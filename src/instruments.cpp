#include <instruments.h>

template <class T>
instrument_base<T> &instrument_base<T>::operator=(const instrument_base<T> &copy)
{
    if (this != &copy)
    {
        this->volume = copy.volume;
        this->maxLifeTime = copy.maxLifeTime;
        this.env = copy.env;
        this.name = copy.name;
    }
    return *this;
}

template <class T>
bool instrument_base<T>::operator==(const instrument_base<T> &rhs) const
{
    return volume == rhs.volume && maxLifeTime == rhs.maxLifeTime && env == rhs.env && name == rhs.name;
}

template <class T>
bool instrument_base<T>::operator!=(const instrument_base<T> &rhs) const
{
    return !(rhs == *this);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const instrument_base<T> &inst)
{
    os << "Instrument: " << inst.name << "\n";

    return os;
}

template <class T>
instrument_base<T>::instrument_base(const T volume, const T maxLifeTime, envelopeADSR<T> env, const std::string name) : volume{volume}, maxLifeTime{maxLifeTime}, name{name}
{
}

template <class T>
T instrument_base<T>::sound(const T time, note<T> n, bool &noteFinished)
{
    return 0;
}

template <class T>
T instrument_base<T>::hz_to_rad(T hertz)
{
    return hertz * 2 * pi;
}

template <class T>
T instrument_base<T>::oscSine(const T time, const T frequency, const T lowfreq, const T lowamp)
{
    T freq = hz_to_rad(frequency) * time + lowamp * frequency * (sin(hz_to_rad(lowfreq) * time));
    return sin(freq);
}

template <class T>
T instrument_base<T>::oscRand()
{
    return 2.0 * ((T)rand() / (T)RAND_MAX) - 1.0;
}

template class instrument_base<short>;
template class instrument_base<int>;
template class instrument_base<float>;
template class instrument_base<double>;