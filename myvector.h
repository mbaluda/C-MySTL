///\file myvector.h
///\brief The vector container
///
///It contains implementation of a dynamic array with the relative operators and iterators

#ifndef MYSTL_MYVECTOR_H
#define MYSTL_MYVECTOR_H

#define DEFAULT_CAPACITY 10

///Isolates MySTL Classes and functions names
namespace mystl {

///\class MyVector
///\brief A vector (dynamic array) class
///
///This class is meant as a programming exercise, It mimcs std::vector behaviour.
///It contains 2 inner classes: iterator and reverse_iterator
///
///\author Mauro Baluda
///Contact: mauro@bglug.it
template<class T>
class MyVector {

private:
    ///The capacity of the vector
    int _capacity;

    ///The size of the vector (number of elements contained)
    int _size;

    ///The actual vector content
    T* data;

public:
    ///Creates an empty vector
    MyVector(int s=DEFAULT_CAPACITY) : _capacity(s), _size(0) {
        try {
            data = new T[_capacity];
        } catch (const std::bad_alloc&) {}
    }

    ///Creates a list from another one using the operator=
    MyVector(const MyVector<T>& other): _capacity(other._capacity), _size(0) {
        try {
            data = new T[_capacity];
        } catch (const std::bad_alloc&) {}
        *this=other;
    }

    ///Deletes a vector after clearing his content
    ~MyVector() {
        delete[] data;
    }

    ///Operator []
    T& operator[](int n) {
        return(data[n]);
    }

    ///Operator =
    MyVector& operator=(const MyVector& other) {
        clear();
        reserve(other._capacity);

        _size=other.size();
        for(int i=0;i<_size;++i) {
            data[i]=other.data[i];
        }

        return(*this);
    }

    ///Returnes TRUE if the vector is empty
    bool empty() const {
        return(_size==0);
    }

    ///Returnes the size of the vector
    int size() const {
        return(_size);
    }

    ///Returnes the capacity of the vector
    int capacity() const {
        return(_capacity);
    }

    ///Deletes the content of the vector
    void clear() {
        _size=0;
    }

    ///Returnes the value of the first element of the vector
    T front() {
        if(_size==0) {
            throw std::out_of_range("Empty Vector");
        } else {
            return(data[0]);
        }
    }

    ///Returnes the value of the last element of the vector
    T back() {
        if(_size==0) {
            throw std::out_of_range("Empty Vector");
        } else {
            return(data[_size-1]);
        }
    }

    ///Inserts an element at the end of the vector
    void push_back(const T& val) {
        //in case of an empty vector
        if (_capacity==0) reserve(DEFAULT_CAPACITY);
        //in case of a full vector
        else if(_size==_capacity) {
            reserve(2*_capacity);
        }

        data[_size]=val;
        ++_size;
    }

    ///Enlarges a vector to new_capacity
    void reserve(int new_capacity) {
        if (new_capacity>_capacity) {
            try {
                T* temp = new T[new_capacity];
                for(int i=0;i<_size;++i) {
                    temp[i]=data[i];
                }
                delete[] data;
                data = temp;
                _capacity=new_capacity;
            } catch (const std::bad_alloc&) {}
        }
    }


    ///Deletes an element at the end of the vector
    void pop_back() {
        if(_size==0) {
            throw std::out_of_range("Empty Vector");
        } else {
            _size--;
        }
    }

    ///\class iterator
    ///\brief A forward iterator for MyVector
    class iterator{
    private:
        T* elem;

    public:
        iterator() : elem(0) {}
        ///Creates an iterator from a pointer
        iterator(T* p) : elem(p) {}
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
            ++elem;
            return(*this);
        }

        ///Operator ++ (postfix)
        iterator& operator++(int) {
            iterator& tmp(*this);
            ++(*this);
            return(tmp);
        }

        ///Operator -- (prefix)
        iterator& operator--() {
            elem--;
            return(*this);
        }

        ///Operator -- (postfix)
        iterator& operator--(int) {
            iterator tmp(*this);
            --(*this);
            return(tmp);
        }

        ///Operator *: returns by reference
        T& operator*() {
            return(*elem);
        }
    };

    ///\class reverse_iterator
    ///\brief A reverse iterator for MyVector
    class reverse_iterator{
    private:
        T* elem;

    public:
        reverse_iterator() : elem(0) {}
        ///Creates a reverse_iterator from a pointer to an element
        reverse_iterator(T* p) : elem(p) {}
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
                --elem;
            }
            return(*this);
        }

        ///Operator ++ (postfix)
        reverse_iterator& operator++(int) {
            reverse_iterator tmp(*this);
            --(*this);
            return(tmp);
        }

        ///Operator -- (prefix)
        iterator& operator--() {
            --elem;
            return(*this);
        }

        ///Operator -- (postfix)
        iterator& operator--(int) {
            iterator tmp(*this);
            ++(*this);
            return(tmp);
        }

        ///Operator *: returns by reference
        T& operator*() {
            return(*elem);
        }
    };

    ///Creates an iterator pointing to the first element of the vector
    iterator begin() {
        return(iterator(data));
    }

    ///Creates an iterator pointing after the end of the vector (0)
    iterator end() {
        return(iterator(&data[_size]));
    }

    ///Creates a reverse_iterator pointing to the last element of the vector
    reverse_iterator rbegin() {
        return(reverse_iterator(&data[_size-1]));
    }

    ///Creates a reverse_iterator pointing before the beginning of the vector (0)
    reverse_iterator rend() {
        return(reverse_iterator(&data[-1]));
    }
};

}
#endif
