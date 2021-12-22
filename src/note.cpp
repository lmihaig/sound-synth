#include <note.h>

template <class T>
note<T>::note(int id, T on, T off, bool active, instrument_base<T> &timbre) : id{id}, on{on}, off{off}, active{active}, timbre{timbre}
{
}

template <class T>
std::ostream &operator<<(std::ostream &os, const note<T> &n)
{
    os << "Note ID:" << n.id << "\n";
    os << n.timbre;
    return os;
}

template class note<short>;
template class note<int>;
template class note<float>;
template class note<double>;