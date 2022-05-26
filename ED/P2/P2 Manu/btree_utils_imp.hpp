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
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO (done)
    if(t->is_empty()){
        height = -1;
        return height;
    }else{
        int left_val = compute_height<T>(t->left());
        int right_val =compute_height<T>(t->right());
        if (right_val > left_val){
            height = right_val+1;
        }else{
            height = left_val+1;
        }
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO (done)
    if(!t->is_empty()){
        ret_val = (compute_size<T>(t->right()) + compute_size<T>(t->left()));
        ret_val++;
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    if(!tree->is_empty()){
        retVal = p(tree->item());

        retVal = retVal and prefix_process<T>(tree->left(),p);

        retVal = retVal and prefix_process<T>(tree->right(),p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    if(!tree->is_empty()){

        retVal = infix_process<T>(tree->left(),p);
        retVal = retVal and p(tree->item());
        retVal = retVal and infix_process<T>(tree->right(),p);

    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    if(!tree->is_empty()){

        retVal = postfix_process<T>(tree->left(), p);
		retVal = retVal and postfix_process<T>(tree->right(), p);
		retVal = retVal and p(tree->item());

    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO
    typename BTree<T>::Ref subtree;
    std::queue<typename BTree<T>::Ref> q;

    q.push(tree);

    while (!q.empty() && go_on){
        subtree = q.front();
        if (!subtree->is_empty()){
            go_on = p(subtree->item());
            q.push(subtree->left());
            q.push(subtree->right());
        }
        q.pop();
    }

    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto p = [&out](T const& value){
        out << value << ' ';
        return true; 
    };

    prefix_process<T>(tree, p);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a infix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto p = [&out](T const& value){
        out << value << ' ';
        return true; 
    };

    infix_process<T>(tree, p);

    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto p = [&out](T const& value){
        out << value << ' ';
        return true; 
    };

    postfix_process<T>(tree, p);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remenber: the lambda must return true.

    auto p = [&out](T const& value){
        out << value << ' ';
        return true; 
    };

    breadth_first_process<T>(tree, p);

    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the prefix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [&found, it, &count] (T const& value){
        count++;
    
        if(value==it){
            found = true;
        }
        return !found;
    };

    prefix_process<T>(tree, p);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the infix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [&found, it, &count] (T const& value){
        count++;

        if(it == value){
            found = true;
        }
        return !found;
    };

    infix_process<T>(tree, p);
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the postfix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [&found, it, &count] (T const& value){
        count++;

        if(it == value){
            found = true;
        }
        return !found;
    };

    postfix_process<T>(tree, p);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the breadth_first_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [&found, it, &count] (T const& value){
        count++;

        if(it == value){
            found = true;
        }
        return !found;
    };

    breadth_first_process<T>(tree, p);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    if(!tree->is_empty()){
        if(!tree->left()->is_empty()){
            if(check_btree_in_order<T>(tree->left())){
                if(tree->left()->item() > tree->item()){
                    ret_val = false;
                }
            } else {
                ret_val = false;
            }
        }

        //Se puede añadir un if comprobando ret_val para que en el caso de que sea false, no seguir comparando
        if(!tree->right()->is_empty()){
            if(check_btree_in_order<T>(tree->right())){
                if(tree->right()->item() < tree->item()){
                    ret_val = false;
                }
            } else {
                ret_val = false;
            }
        }


    }
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO (done)
    if(!tree->is_empty()){
        if(v < tree->item()){
            ret_val = has_in_order(tree->left(), v);
        }else if(v > tree->item()){
            ret_val = has_in_order(tree->right(), v);
        }else{
            ret_val = true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO (done)
    if(tree->is_empty()){ //case 0
        tree->create_root(v);
    }else if(v < tree->item()){ //case 1
        if(tree->left()->is_empty()){
            tree->set_left(BTree<T>::create(v));
        }else{
            insert_in_order(tree->left(),v);
        }
    }else if(v > tree->item()){ //case 2
        if(tree->right()->is_empty()){
            tree->set_right(BTree<T>::create(v));
        }else{
            insert_in_order(tree->right(),v);
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
