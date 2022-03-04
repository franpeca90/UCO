/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include "queue.hpp"

template<class T>
Queue<T>::Queue ()
{
    //TODO    

    //
    assert(is_empty());
}

template<class T>
bool
Queue<T>::is_empty () const
{
    bool ret_val = true;
    //TODO

    //
    return ret_val;
}

template<class T>
size_t
Queue<T>::size () const
{
    size_t ret_val = 0;
    //TODO

    //
    return ret_val;
}

template<class T>
T
Queue<T>::front() const
{
    assert(! is_empty());
    T ret_val;
    //TODO

    //
    return ret_val;
}

template<class T>
T Queue<T>::back() const
{
    assert(! is_empty());
    T ret_val;
    //TODO

    //
    return ret_val;
}

template<class T>
void
Queue<T>::enque(const T& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO
    //Remenber we enque into the input stack.
    //Hint: maybe you need to update the back item.

    //
    assert(back()==new_it);
    assert(size()==(old_size+1));
}

template<class T>
void
Queue<T>::deque()
{
    assert(! is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO
    //Remenber we deque from the output stack and if the output stack is empty
    //we need flush the input stack into the output stack first.

    //
    assert(size()==(old_size-1));
}


template<class T>
void
Queue<T>::flush_input_to_output()
{
    assert(!input_->is_empty());
#ifndef NDEBUG
    T old_back = back();
#endif
    //TODO
    //Remenber: the first item pushed into output is
    // the new back() of the queue.

    //
    assert(old_back == back());
}
