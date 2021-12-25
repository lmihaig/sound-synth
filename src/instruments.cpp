#include <instruments.h>
#include <cmath>

template <class T>
instrument_base<T> &instrument_base<T>::operator=(const instrument_base<T> &copy)
{
    if (this != &copy)
    {
        this->volume = copy.volume;
        this->maxLifeTime = copy.maxLifeTime;
        this->env = copy.env;
        this->name = copy.name;
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
T instrument_base<T>::sound(const T time, note<T> &n, bool &noteFinished)
{
    std::cout << "TEST";
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
    T freq = hz_to_rad(frequency) * time + lowamp * frequency * (std::sin(hz_to_rad(lowfreq) * time));
    return std::sin(freq);
}

template <class T>
T instrument_base<T>::oscSquare(const T time, const T frequency, const T lowfreq, const T lowamp)
{
    T freq = hz_to_rad(frequency) * time + lowamp * frequency * (std::sin(hz_to_rad(lowfreq) * time));
    return std::sin(freq) > 0 ? 1.0 : -1.0;
}

template <class T>
T instrument_base<T>::oscTriangle(const T time, const T frequency, const T lowfreq, const T lowamp)
{
    T freq = hz_to_rad(frequency) * time + lowamp * frequency * (std::sin(hz_to_rad(lowfreq) * time));
    return std::asin(std::sin(freq)) * (2 / pi);
}

template <class T>
T instrument_base<T>::oscSaw(const T time, const T frequency, const T lowfreq, const T lowamp, const T steps)
{
    T freq = hz_to_rad(frequency) * time + lowamp * frequency * (std::sin(hz_to_rad(lowfreq) * time));
    T output = 0;
    for (T n = 1; n < steps; n++)
        output += (std::sin(n * freq)) / n;
    return output * (2 / pi);
}

template <class T>
T instrument_base<T>::oscRand()
{
    return 2.0 * ((T)rand() / (T)RAND_MAX) - 1.0;
}

template <class T>
T instrument_base<T>::scale(const int noteID)
{
    return 8 * std::pow(1.0594630943592952645618252949463, noteID);
}

template class instrument_base<float>;
template class instrument_base<double>;

template std::ostream &operator<<<>(std::ostream &o, const instrument_base<float> &n);
template std::ostream &operator<<<>(std::ostream &o, const instrument_base<double> &n);