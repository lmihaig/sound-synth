#include <note.h>

template <class T>
note<T>::note(int id, T on, T off, bool active) : id{id}, on{on}, off{off}, active{active}
{
}

template <class T>
std::ostream &operator<<(std::ostream &os, const note<T> &n)
{
    os << "Note ID: " << n.id << "\n";
    return os;
}

template class note<float>;
template class note<double>;

template std::ostream &operator<<<>(std::ostream &o, const note<float> &n);
template std::ostream &operator<<<>(std::ostream &o, const note<double> &n);