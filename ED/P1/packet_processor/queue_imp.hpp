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
    input_ = Stack<T>::create();
    output_ = Stack<T>::create();
    //
    assert(is_empty());
}

template<class T>
bool
Queue<T>::is_empty () const
{
    bool ret_val = true;
    //TODO
    bool aux1 = input_->is_empty();
    bool aux2 = output_->is_empty();
    if(aux1==false or aux2==false){
        ret_val=false;
    }
    //
    return ret_val;
}

template<class T>
size_t
Queue<T>::size () const
{
    size_t ret_val = 0;
    //TODO
    if(this->is_empty()!=true){
        ret_val = input_->size() + output_->size();
    }
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
    if(output_->is_empty()){
        const_cast<Queue<T>*>(this)->flush_input_to_output();
    }
    ret_val = output_->top();
    //
    return ret_val;
}

template<class T>
T Queue<T>::back() const
{
    assert(! is_empty());
    T ret_val;
    //TODO
    if(!input_->is_empty()){
        ret_val = input_->top();
    } else {
        ret_val = back_;
    }

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
    input_->push(new_it);
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
    if(output_->is_empty()){
        flush_input_to_output();
    }

    output_->pop();

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
    back_=back();
    T aux = old_back;
    while(!input_->is_empty()){
        output_->push(back());
        input_->pop();
    }
    //
    assert(old_back == back());

}
