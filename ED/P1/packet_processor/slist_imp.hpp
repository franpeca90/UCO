/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include "slist.hpp"
#include <sstream>
#include <stdexcept>
#include <cassert>

template <class T>
SNode<T>::SNode (T const& it)
{
    //TODO
    _item = it;
    _next = nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //TODO
    _item = it;
    _next = next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //TODO
    //hint: if std::shared_ptr is used for the references, nothing todo.

    //
}

template <class T>
typename SNode<T>::Ref SNode<T>::create(T const& it, SNode<T>::Ref next)
{
    return std::make_shared<SNode<T>> (it, next);
}

template <class T>
T SNode<T>::item() const
{
    T it;
    //TODO
    it = _item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //TODO
    if(_next != nullptr){has=true;}
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //TODO
    n = _next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //TODO
    _item = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //TODO
    _next = n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //TODO
    _head = nullptr;
    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //TODO 

    //

}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //TODO
    h = _head;
    //
    return h;
}

template<class T>
typename SList<T>::Ref SList<T>::create()
{
    return std::make_shared<SList<T>> ();
}

template<class T>
typename SList<T>::Ref SList<T>::create(std::istream& in) noexcept(false)
{
    auto list = SList<T>::create();
    std::string token;
    in >> token;

    //TODO
    //Hint: use std::istriongstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception if a input
    // format error was found.
    std::string f_data;
    in >> f_data;
    
    if(f_data != "[]" or f_data != "["){
        if(f_data == "["){
            while(in >> f_data and f_data != "]"){
                std::istringstream tem_data(f_data);
                if(tem_data){
                    T aux;
                    tem_data >> aux;

                    if(list->is_empty()){
                        list->insert(aux);
                    } else {
                        while(list->has_next()){
                            list->goto_next();
                        }
                        list->insert(aux);
                    }

                }else{
                    throw std::runtime_error("Wrong input format.");
                }
            }
        }
    } else {
        throw std::runtime_error("Wrong input format.");
    }
    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //TODO
    size_t aux = size();
    if (aux != 0){
        ret_val = false;
    }
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //TODO
    typename SNode<T>::Ref aux = head();
    while(aux != nullptr){
        ret_val++;
        aux = aux->next();
    }
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //TODO
    f = _head->item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(!is_empty());
    T c;
    //TODO
    c = _current->item();
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO
    if(_current->has_next()==true){ret_val=true;}
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //TODO
    ret_val = _current->next()->item();
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //TODO
    //Hint: you can reuse SList::find() but remebering restore cursors to
    //assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    typename SNode<T>::Ref aux = head();
    while(aux != nullptr){
        if(aux->item() == it){
            found = true;
        }
        aux = aux->next();
    }
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //TODO
    if(!is_empty()){
        out << "[";

        typename SNode<T>::Ref aux = head();
        while(aux != nullptr){
            out << " ";
            out << aux->item();

            aux = aux->next();
        }

        out << "]";

    } else {
        out << "[]";
    }
    //
}

template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //TODO
    _current->set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO
    //Remeber to update current if current is in the head.
    typename SNode<T>::Ref aux;
    if(this->is_empty()){
        aux = SNode<T>::create(new_it);
    } else {
        aux = SNode<T>::create(new_it, _head);
    }

    _head = aux;
    _current = _head;

    //
    assert(front()==new_it);
    assert(size() == (old_size+1));
}

template<class T>
void SList<T>::insert(T const& new_it)
{
#ifndef NDEBUG
    bool old_is_empty = is_empty();
    size_t old_size = size();
    T old_item;
    if (!old_is_empty)
        old_item = current();
#endif
    //TODO

    typename SNode<T>::Ref aux;
    if(!is_empty()){
        aux = SNode<T>::create(new_it, _current->next());
		_current->set_next(aux);
    } else {
   
		aux = SNode<T>::create(new_it);

        _head = aux;
        _current = aux;
    }

    assert(!old_is_empty || (front()==new_it && current()==new_it));
    assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
    assert(size()==(old_size+1));
}

template<class T>
void SList<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_head_next = head()->next();
#endif
    //TODO
    _head = _head->next();
    _current = _head;
    //
    assert(is_empty() || head() == old_head_next);
    assert(size() == (old_size-1));
}


template<class T>
void SList<T>::remove()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    bool old_has_next = has_next();
    T old_next;
    if (has_next())
        old_next=next();
#endif
    //TODO
    //Case 1: current is the head.
    if(_current = head()){
        _head = head()->next();
        _current = _head;
    }
    //Case 2: remove in a middle position.
    else if (_current->has_next()){
        typename SNode<T>::Ref aux = head();
        while(aux != nullptr or aux->next()==_current){
            aux = aux->next();
        }
        aux->set_next(_current->next());
        _current = _current->next();
    }
    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.
    else if (!_current->has_next()){
        typename SNode<T>::Ref aux = head();
        while(aux != nullptr or aux->next()==_current){
            aux = aux->next();
        }
        aux->set_next(nullptr);
        _current = aux;
    }


    //
    assert(!old_has_next || current()==old_next);
    assert(size() == (old_size-1));
}

template<class T>
void SList<T>::goto_next()
{
    assert(has_next());
#ifndef NDEBUG
    auto old_next = next();
#endif
    //TODO
    _current = _current->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //TODO
    _current = _head;
    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //TODO
    typename SNode<T>::Ref aux = head();
    while(aux != nullptr and found != true){
        if(aux->item() == it){
            found = true;
        }
        aux = aux->next();
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

template<class T>
bool SList<T>::find_next(T const& it)
{
    assert(has_next());
    bool found = false;
    //TODO
    goto_next();
    typename SNode<T>::Ref aux = _current;
    while(aux != nullptr and found != true){
        if(aux->item() == it){
            found = true;
        }
        aux = aux->next();
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

