#ifndef HEAP_VECTOR_H
#define HEAP_VECTOR_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

enum HEAP_ERROR {HEAP_EMPTY};

template <typename T>
class Heap
{
public:
    Heap();
    Heap(const T &t);
    Heap(const Heap<T> &h);
    ~Heap();

    Heap<T>& operator=(const Heap<T> &h);
    Heap<T>& operator>>(T &t);
    Heap<T>& operator<<(const T &t);

    bool empty();
    void clear();
    unsigned int size();


    template<typename U>
    friend ostream& operator<<(ostream& out, Heap<U> &h);

    template<typename U>
    friend istream& operator>>(istream& in, Heap<U> &h);

private:
    vector<T> *v;
    unsigned int findParent(unsigned int n);
    void reheapifyUp();
    void reheapifyDown();
    void initializeObject();
    void checkChildrenExist(bool &left, bool &right, unsigned int parent);
//    void compareChildren(const unsigned int *left, const unsigned int *right, unsigned int **chosen);

    // callback functions
    void copy(const Heap<T> &h);

};




template<typename T>
void Heap<T>::initializeObject()
{
    v = new vector<T>;
    v->reserve(26);
}


template<typename T>
void Heap<T>::copy(const Heap<T> &h)
{
    if (this != &h)
    {
        clear();
        v = h.v;
    }
}

template<typename T>
void Heap<T>::clear()
{
    v->clear();
}




// constructs the vector and reserves memory for the letters
template<typename T>
Heap<T>::Heap()
{
    initializeObject();
}

template<typename T>
Heap<T>::Heap(const T &t)
{
    initializeObject();
    v->push_back(t);
}

template<typename T>
Heap<T>::Heap(const Heap<T> &h)
{
    initializeObject();
    copy(h);
}

template<typename T>
Heap<T>::~Heap()
{
    clear();
}

template<typename T>
Heap<T>& Heap<T>::operator=(const Heap<T> &h)
{
    copy(h);
}

template<typename T>
Heap<T>& Heap<T>::operator>>(T &t)
{
    t = v->front();
}

template<typename T>
Heap<T>& Heap<T>::operator<<(const T &t)
{
    v->push_back(t);

    reheapifyUp();

    return *this;
}


template<typename T>
bool Heap<T>::empty()
{
    return !(v->size());
}

template<typename T>
unsigned int Heap<T>::size()
{
    return v->size();
}

// make sure it's not the root to begin with
template<typename T>
unsigned int Heap<T>::findParent(unsigned int n)
{
    if (n != 0)
    {
        return (n - 1)/2;
    }

    return 0;
}

template<typename T>
void Heap<T>::reheapifyUp()
{
    if (v->size() == 0)
    {
        cout << "reheapifyUp error exception\n";
        throw HEAP_EMPTY;
    }
    // inserted at the back
    // compare with the parent
    unsigned int parent, child;

    child = v->size() - 1;
    parent = findParent(child);

    while(v->at(child) > v->at(parent))
    {
        // if greater swap
        swap(v->at(child), v->at(parent));

        child = parent;
        parent = findParent(child);
    }
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template<typename T>
void Heap<T>::reheapifyDown()
{
    if (v->size() == 0)
    {
        cout << "reheapifyDown error exception\n";

        throw HEAP_EMPTY;
    }
    else if (v->size() == 1)
    {
        v->pop_back();
        return;
    }

    // assuming that the beginning is already taken care of
    unsigned int parent, childChosen;
    bool checkLeft, checkRight;

    // swap the last with the first
    swap(v->at(0), v->at(v->size() - 1));
    v->pop_back();

    parent = 0;
    checkChildrenExist(checkLeft, checkRight, parent);

    // if right exists, then left automatically exists
    if (checkRight)
    {   if (v->at(2*parent + 2) > v->at(2*parent + 1))
        {
            childChosen = 2*parent + 2;
        }
        else
        {
            childChosen = 2*parent + 1;
        }
    }
    else if (checkLeft && !checkRight)
    {
        childChosen = 2*parent + 1;
    }
    else
    {
        childChosen = parent;
    }

    while(v->at(childChosen) > v->at(parent))
    {
        // if greater swap
        swap(v->at(parent), v->at(childChosen));

        parent = childChosen;

        checkChildrenExist(checkLeft, checkRight, parent);

        // if right exists, then left automatically exists
        if (checkRight)
        {   if (v->at(2*parent + 2) > v->at(2*parent + 1))
            {
                childChosen = 2*parent + 2;
            }
            else
            {
                childChosen = 2*parent + 1;
            }
        }
        else if (checkLeft && !checkRight)
        {
            childChosen = 2*parent + 1;
        }
        else
        {
            childChosen = parent;
        }
    }

}

template<typename T>
void Heap<T>::checkChildrenExist(bool &left, bool &right, unsigned int parent)
{
    left = 2*parent + 1 < v->size() ? true : false;
    right = 2*parent + 2 < v->size() ? true : false;
}

//template<typename T>
//void Heap<T>::compareChildren(const unsigned int *left, const unsigned int *right, unsigned int **chosen)
//{

//}


template<typename U>
ostream& operator<<(ostream& out, Heap<U> &h)
{

    // printing heap key
//    for (unsigned int i = 0; i < h.v->size() - 1; ++i)
//    {
//        out << i << "|" << (i - 1) / 2 << "  ";
//    }

//    out << endl << endl;

//    // printing list as is
//    for (unsigned int i = 0; i < h.v->size(); ++i)
//    {
//        if (i % 5 == 0)
//            out << endl;
//        out << i << " " << h.v->at(i) << "\t";
//    }

//    out << endl << endl;

    unsigned int count = 0;
    while (!h.v->empty())
    {
        if (count % 5 == 0)
            out << endl;
        out << setw(3) << h.v->front() << " ";
//        h.v->pop_back();
        h.reheapifyDown();
        ++count;
    }

//    out << h.v->front();

//    h.v->pop_back();

    return out;
}

template<typename U>
istream& operator>>(istream& in, Heap<U> &h)
{
    while (in)
    {
        in >> h;
    }

    return in;
}





#endif // HEAP_VECTOR_H
