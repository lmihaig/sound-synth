#include <note.h>

template <class T>
note<T>::note(unsigned int id, T on, T of, bool active, instrument_base<T> timbre) : id{id}, on{on}, off{off}, active{active}, timbre{timbre}
{
}