#pragma once

#include "stdexcept"
#include "activity.h"
#define INITIAL_CAP 5

template <typename T> class ArrayIterator;

template <typename T> class DynamicArray {
public:
    /*
     * Default constructor
     * Initial capacity of 5
     */
    DynamicArray();

    // Rule of 3
    /* Copy constructor */
    DynamicArray(const DynamicArray& ot);

    /* Assigment operator */
    DynamicArray& operator=(const DynamicArray& ot);

    /* Destructor */
    ~DynamicArray();

    /*
     * Overrides the [] operator
     */
    T & operator[] (int index) const;

    /*
     * Adds an element at the back of the array
     */
    void push_back(const T &el);

    /*
     * Delete the element at the position pos
     */
    void erase(int index);

    /*
     * Sets an element at the position pos
     */
    void set(int pos, const T &el);

    /*
     * Gets the size of the array
     */
    int length() const;

    /*
     * Gets the element at the position pos
     */
    T& get(int pos) const;

    /*
     * Override the == operator
     */
    bool operator==(const DynamicArray &ot) const;

    /*
     * Methods for iterator
     */
    friend class ArrayIterator<T>;
    ArrayIterator<T> begin();
    ArrayIterator<T> end();

private:
    int size;
    int capacity;
    T *elems;

    void ensureCapacity();
};

template <typename T>
T &DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return elems[index];
}

template <typename T>
DynamicArray<T>::DynamicArray() {
    size = 0;
    capacity = INITIAL_CAP;
    elems = new T[INITIAL_CAP];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &ot) {
    size = ot.size;
    capacity = ot.capacity;
    elems = new T[capacity];
    for (int i = 0; i < size; i++) {
        elems[i] = ot.elems[i];
    }
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &ot) {
    if (this == &ot) {
        return *this;
    }
    delete[] elems;
    size = ot.size;
    capacity = ot.capacity;
    elems = new T[capacity];
    for (int i = 0; i < size; i++) {
        elems[i] = ot.elems[i];
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] elems;
}

template <typename T>
void DynamicArray<T>::push_back(const T &el) {
    ensureCapacity();
    elems[size++] = el;
}

template <typename T>
void DynamicArray<T>::set(int pos, const T &el) {
    elems[pos] = el;
}

template <typename T>
int DynamicArray<T>::length() const {
    return size;
}

template <typename T>
T& DynamicArray<T>::get(int pos) const {
    return elems[pos];
}

template <typename T>
void DynamicArray<T>::ensureCapacity() {
    if (size < capacity) {
        return; // we have enough space
    }
    T *aux = new T[capacity * 2];
    for (int i = 0; i < size; i++) {
        aux[i] = elems[i];
    }
    delete[] elems;
    capacity *= 2;
    elems = aux;
}

template <typename T>
void DynamicArray<T>::erase(int index) {
    for (int i = index; i < size; i++) {
        elems[i] = elems[i+1];
    }
    size--;
}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray &ot) const {
    if (size != ot.size) {
        return false;
    }
    for (int i = 0; i < size; i++) {
        if (!(elems[i] == ot.elems[i])) {
            return false;
        }
    }
    return true;
}


template <typename T>
ArrayIterator<T> DynamicArray<T>::begin() {
    return ArrayIterator<T>(*this);
}

template <typename T>
ArrayIterator<T> DynamicArray<T>::end() {
    return ArrayIterator<T>(*this, size);
}




template <typename T> class ArrayIterator {
private:
    const DynamicArray<T> &array;
    int pos = 0;

public:
    ArrayIterator(const DynamicArray<T> &array) noexcept;

    ArrayIterator(const DynamicArray<T> &array, int pos) noexcept;

    bool isValid() const noexcept;

    void next() noexcept;

    T& element() const noexcept;

    T& operator*();

    ArrayIterator<T>& operator++();

    bool operator==(const ArrayIterator<T> &ot) noexcept;

    bool operator!=(const ArrayIterator<T> &ot) noexcept;

};

template <typename T>
ArrayIterator<T>::ArrayIterator(const DynamicArray<T> &array) noexcept : array{array} {}

template <typename T>
ArrayIterator<T>::ArrayIterator(const DynamicArray<T> &array, int pos) noexcept : array{array}, pos{pos} {}

template <typename T>
bool ArrayIterator<T>::isValid() const noexcept {
    return pos < array.size;
}

template <typename T>
void ArrayIterator<T>::next() noexcept {
    pos++;
}

template <typename T>
T& ArrayIterator<T>::element() const noexcept {
    return array.elems[pos];
}

template <typename T>
T& ArrayIterator<T>::operator*() {
    return element();
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator++() {
    next();
    return *this;
}

template <typename T>
bool ArrayIterator<T>::operator==(const ArrayIterator<T> &ot) noexcept {
    return pos == ot.pos;
}

template <typename T>
bool ArrayIterator<T>::operator!=(const ArrayIterator<T> &ot) noexcept {
    return !(*this == ot);
}
