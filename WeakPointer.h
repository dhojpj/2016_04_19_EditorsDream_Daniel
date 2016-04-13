#ifndef WEAKPOINTER_H
#define WEAKPOINTER_H

// purpose of this class is to create corresponding "weak pointers" of types
// that will slow down the program, so we use unsigned ints instead

#include <iostream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

template<typename T>
class WeakPointer
{
public:
    WeakPointer();
    WeakPointer(const Heap &h);
    ~WeakPointer();

private:
    Heap<int> *heapWithPointers;
    Heap<T> *heapRawData;

    void initialize();
    void clear();

//    vector<T> *v;
//    unsigned int findParent(unsigned int n);

//    bool reheap; // if the heap is MAX (descending order) or MIN (ascending order)
//    sort heap_sort[4]; // function pointers
//    HEAP_TYPE reheapUp, reheapDown; // to call function pointers

//    void reheapifyUp();
//    void reheapifyDown();
//    void reheapifyUp_MAX(unsigned int &p, unsigned int &c);
//    void reheapifyDown_MAX(unsigned int &p, unsigned int &c);
//    void reheapifyUp_MIN(unsigned int &p, unsigned int &c);
//    void reheapifyDown_MIN(unsigned int &p, unsigned int &c);

//    void chooseChild_MAX(const bool &left, const bool &right,  const unsigned int &parent, unsigned int &child);
//    void chooseChild_MIN(const bool &left, const bool &right,  const unsigned int &parent, unsigned int &child);
//    void checkChildrenExist(bool &left, bool &right, const unsigned int &parent);

//    void initializeObject();
//    void copy(const Heap<T> &h);



};

template<typename T>
void WeakPointer<T>::initialize()
{
    heapWithPointers = new Heap<int>;

    if (!(heapRawData))
    {
        for (unsigned int i = 0; i < heapRawData->size(); ++i)
        {
            heapWithPointers[i] = i;
        }
    }
}

template<typename T>
void WeakPointer<T>::clear()
{
    heapWithPointers->clear();
    heapRawData->clear();
}

template<typename T>
WeakPointer<T>::WeakPointer()
{
    initialize();
}

template<typename T>
WeakPointer<T>::WeakPointer(const Heap &h)
{
    heapRawData = h;
    initialize();
}

template<typename T>
WeakPointer<T>::~WeakPointer()
{
    clear();
}


#endif // WEAKPOINTER_H
