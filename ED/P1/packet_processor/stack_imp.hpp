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
#include "stack.hpp"


template<class T>
Stack<T>::Stack ()
{
    //TODO

    //
    assert(is_empty());
}

template<class T>
typename Stack<T>::Ref Stack<T>::create()
{
    return std::make_shared<Stack<T>>();
}

template<class T>
typename Stack<T>::Ref Stack<T>::create(std::istream & in) noexcept(false)
{
    auto stack = Stack<T>::create();
    //TODO
    //Hint: unfold the list used as implementation.

    //
    return stack;
}

template<class T>
bool Stack<T>::is_empty () const
{
    bool ret_val = true;
    //TODO

    //
    return ret_val;
}

template<class T>
size_t Stack<T>::size () const
{
    size_t ret_val = 0;
    //TODO

    //
    return ret_val;
}

template<class T>
T Stack<T>::top() const
{
    assert(! is_empty());
    T it;
    //TODO

    //
    return it;
}

template<class T>
void Stack<T>::fold(std::ostream& out) const
{
    //TODO
    //Hint: fold the list used as implementation.

    //
}
template<class T>
void Stack<T>::push(const T& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO

    //
    assert(top()==new_it);
    assert(size()==(old_size+1));
}

template<class T>
void Stack<T>::pop()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(! is_empty());
    //TODO

    //
    assert(size()==(old_size-1));
}
