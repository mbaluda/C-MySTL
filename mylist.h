///\file mylist.h
///\brief The list container
///
///It contains implementation of a double linked list with the relative operators and iterators

#ifndef MYSTL_MYLIST_H
#define MYSTL_MYLIST_H

#include <stdexcept>

///Isolates MySTL Classes and functions names
namespace mystl {

///\class MyList
///\brief A double linked list class
///
///This class is meant as a programming exercise, It mimcs std::list behaviour.
///It contains 3 inner classes: Elem, iterator and reverse_iterator
///
///\author Mauro Baluda
///Contact: mauro@bglug.it
template<class T>
class MyList {

private:

    ///\class Elem
    ///\brief An element of the list
    class Elem {
    public:
        ///Creates an element and stores his value
        Elem(const T& val): next(0), prev(0), val(val) {}
        ///Deletes an element and all the subsequent ones
        ~Elem() {
            delete next;
        }
        ///Extract the value from an element
        T& getVal() {
            return(val);
        }
        ///The next element in the list
        Elem* next;
        ///The previous element in the list
        Elem* prev;
    private:
        T val;
    };

    ///The first element of the list
    Elem* _front;
    ///The last element of the list
    Elem* _back;
    ///The size of the list
    int _size;

public:
    ///Creates an empty list
    MyList() : _front(0), _back(0), _size(0) {}

    ///Creates a list from another one using the operator=
    MyList(const MyList& other): _front(0), _back(0), _size(0) {
        *this=other;
    }

    ///Operator= Copy element by element
    MyList& operator=(const MyList& other) {
        clear();
        //typename is required for the compiler to know what we mean cfr.:Stourstrup C.13.5
        for (typename mystl::MyList<T>::iterator it = other._front; it != other._back; ++it) {
            this->push_back(*it);
        }

        return(*this);
    }

    ///Deletes a list after clearing his content
    ~MyList() {
        clear();
    }

    ///Returnes TRUE if the list is empty
    bool empty() const {
        return(_front==0);
    }

    ///Returnes the size of the list
    int size() {
        return(_size);
    }

    ///Deletes te content of the list
    void clear() {
        delete _front;
        _front=0;
        _back=0;
        _size=0;
    }

    ///Returnes the value of the first element of the list
    T front() {
        if(_front==0) {
            throw std::out_of_range("Empty List");
        } else {
            return(_front->getVal());
        }
    }

    ///Returnes the value of the last element of the list
    T back() {
        if(_back==0) {
            throw std::out_of_range("Empty List");
        } else {
            return(_back->getVal());
        }
    }

    ///Inserts an element at the beginning of the list
    void push_front(const T& val) {
        try {
            if(_front==0) {
                _front = new Elem(val);
                _back = _front;
            } else {
                Elem* tmp = new Elem(val);
                tmp->next = _front;
                _front->prev = tmp;
                _front = tmp;
            }
        } catch (const std::bad_alloc&) {}
        ++_size;
    }

    ///Inserts an element at the end of the list
    void push_back(const T& val) {
        try {
            if(_front==0) {
                _front = new Elem(val);
                _back = _front;
            } else {
                Elem* tmp = new Elem(val);
                tmp->prev = _back;
                _back->next = tmp;
                _back = tmp;
            }
        } catch (const std::bad_alloc&) {}
        ++_size;
    }

    ///Deletes an element at the beginning of the list
    void pop_front() {
        if(_front==0) {
            throw std::out_of_range("Empty List");
        } else {
            Elem* tmp = _front;
            _front = _front->next;

            _front->prev=0;
            tmp->next = 0;
            delete tmp;
            _size--;
        }
    }

    ///Deletes an element at the end of the list
    void pop_back() {
        if(_back==0) {
            throw std::out_of_range("Empty List");
        } else {
            Elem* tmp = _back;
            _back = _back->prev;

            _back->next=0;
            tmp->prev = 0;
            delete tmp;
            _size--;
        }
    }

    ///\class iterator
    ///\brief A forward iterator for MyList
    class iterator {
    private:
        Elem* elem;

    public:
        iterator() : elem(0) {}
        ///Creates an iterator from a pointer to an element
        iterator(Elem* p) : elem(p) {}
        ~iterator() {}

        ///Operator =
        iterator& operator=(const iterator& other) {
            elem = other.elem;
            return(*this);
        }

        ///Operator ==
        bool operator==(const iterator& other) {
            return(elem == other.elem);
        }

        ///Operator !=
        bool operator!=(const iterator& other) {
            return(elem != other.elem);
        }

        ///Operator ++ (prefix)
        iterator& operator++() {
            if (elem != 0) {
                elem = elem->next;
            }
            return(*this);
        }

        ///Operator ++ (postfix)
        iterator& operator++(int) {
            iterator& tmp=*this;
            ++(*this);
            return(tmp);
        }

        ///Operator *: returns by reference
        T& operator*() {
            return(elem->getVal());
        }
    };

    ///\class reverse_iterator
    ///\brief A reverse iterator for MyList
    class reverse_iterator {
    private:
        Elem* elem;

    public:
        reverse_iterator() : elem(0) {}
        ///Creates a reverse_iterator from a pointer to an element
        reverse_iterator(Elem* p) : elem(p) {}
        ~reverse_iterator() {}

        ///Operator =
        reverse_iterator& operator=(const reverse_iterator& other) {
            elem = other.elem;
            return(*this);
        }

        ///Operator ==
        bool operator==(const reverse_iterator& other) {
            return(elem == other.elem);
        }
        ///Operator !=
        bool operator!=(const reverse_iterator& other) {
            return(elem != other.elem);
        }

        ///Operator ++ (prefix)
        reverse_iterator& operator++() {
            if (elem != 0) {
                elem = elem->prev;
            }
            return(*this);
        }

        ///Operator ++ (postfix)
        reverse_iterator& operator++(int) {
            reverse_iterator tmp(*this);
            ++(*this);
            return(tmp);
        }

        ///Operator *: returns by reference
        T& operator*() {
            return(elem->getVal());
        }
    };

    ///Creates an iterator pointing to the first element of the list
    iterator begin() {
        return(iterator(_front));
    }
    ///Creates an iterator pointing after the end of the list (0)
    iterator end() {
        return(iterator(0));
    }
    ///Creates a reverse_iterator pointing to the last element of the list
    reverse_iterator rbegin() {
        return(reverse_iterator(_back));
    }
    ///Creates a reverse_iterator pointing before the beginning of the list (0)
    reverse_iterator rend() {
        return(reverse_iterator(0));
    }
};
}
#endif
