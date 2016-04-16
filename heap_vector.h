#ifndef HEAP_VECTOR_H
#define HEAP_VECTOR_H
#include <iostream>
#include <cstdlib>
//#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <typeinfo>
using namespace std;

enum HEAP_ERROR {HEAP_EMPTY};
enum HEAP_TYPE {MAX_UP, MAX_DOWN, MIN_UP, MIN_DOWN, CHILD_MAX, CHILD_MIN};

template <typename T>
class Heap
{
public:
    typedef void (Heap::*sort)(unsigned int &p, unsigned int &c);
    Heap(bool reheapType = true);
    Heap(const T &t);
    Heap(const Heap<T> &h);
    ~Heap();

    Heap<T>& operator=(const Heap<T> &h);
    Heap<T>& operator>>(T &t);
    Heap<T>& operator<<(const T &t);

    bool empty();
    void clear();
    unsigned int size();

    void setType(bool reheapType);
    bool getType() const;

    template<typename U>
    friend ostream& operator<<(ostream& out, Heap<U> &h);

    template<typename U>
    friend istream& operator>>(istream& in, Heap<U> &h);

private:
    vector<size_t> *v_weak_pointers;
    vector<T> *v_raw_data;
    unsigned int findParent(unsigned int n);
    bool reheap; // MIN (ascending order) false or MAX (descending order) true

    sort heap_sort[4]; // function pointers
    HEAP_TYPE reheapUp, reheapDown; // to call function pointers

    void reheapifyUp();
    void reheapifyDown();
    void reheapifyUp_MAX(unsigned int &p, unsigned int &c);
    void reheapifyDown_MAX(unsigned int &p, unsigned int &c);
    void reheapifyUp_MIN(unsigned int &p, unsigned int &c);
    void reheapifyDown_MIN(unsigned int &p, unsigned int &c);

    void chooseChild_MAX(const bool &left, const bool &right,  const unsigned int &parent, unsigned int &child);
    void chooseChild_MIN(const bool &left, const bool &right,  const unsigned int &parent, unsigned int &child);
    void checkChildrenExist(bool &left, bool &right, const unsigned int &parent);

    void initializeObject();
    void copy(const Heap<T> &h);

};

// constructor calls upon this
template<typename T>
void Heap<T>::initializeObject()
{
    v_weak_pointers = new vector<size_t>;
    v_weak_pointers->reserve(10);

    v_raw_data = new vector<T>;
    v_raw_data->reserve(10);

    setType(reheap);

    heap_sort[MAX_UP] = &Heap<T>::reheapifyUp_MAX;
    heap_sort[MAX_DOWN] = &Heap<T>::reheapifyDown_MAX;
    heap_sort[MIN_UP] = &Heap<T>::reheapifyUp_MIN;
    heap_sort[MIN_DOWN] = &Heap<T>::reheapifyDown_MIN;
}

template<typename T>
void Heap<T>::setType(bool reheapType)
{
    reheap = reheapType;

    if (reheap)
    {
        reheapUp = MAX_UP;
        reheapDown = MAX_DOWN;
    }
    else
    {
        reheapUp = MIN_UP;
        reheapDown = MIN_DOWN;
    }
}

template<typename T>
bool Heap<T>::getType() const
{
    return reheap;
}

// constructs the vector and reserves memory for the letters
template<typename T>
Heap<T>::Heap(bool reheapType)
{
    reheap = reheapType;
    initializeObject();
}

template<typename T>
Heap<T>::Heap(const T &t)
{
    initializeObject();
    *this << t;
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
    if (this != &h)
    {
        clear();
        copy(h);
    }

    return *this;
}


template<typename T>
Heap<T>& Heap<T>::operator>>(T &t)
{
    t = v_raw_data->at(v_weak_pointers->front());
    reheapifyDown();

    return *this;
}

template<typename T>
Heap<T>& Heap<T>::operator<<(const T &t)
{
    v_raw_data->push_back(t);

    v_weak_pointers->push_back(v_raw_data->size() - 1);
    reheapifyUp();

    return *this;
}

template<typename T>
bool Heap<T>::empty()
{
    return !(v_weak_pointers->size());
}

template<typename T>
unsigned int Heap<T>::size()
{
    return v_weak_pointers->size();
}

template<typename T>
void Heap<T>::copy(const Heap<T> &h)
{
    if (this != &h)
    {
        clear();

        setType(h.getType());

        v_weak_pointers = h.v_weak_pointers;
        v_raw_data = h.v_raw_data;
    }
}

template<typename T>
void Heap<T>::clear()
{
    v_weak_pointers->clear();
    v_raw_data->clear();
//    reheap = true;
//    setType(reheap);
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
    if (v_weak_pointers->size() == 0)
    {
        cout << "reheapifyUp error exception\n";
        throw HEAP_EMPTY;
    }
    // inserted at the back
    // compare with the parent
    unsigned int parent, child;

    child = v_weak_pointers->size() - 1; // the position it was inserted at (the end of tree)
    parent = findParent(child);

    (this->*heap_sort[reheapUp])(parent, child);

}

template<typename T>
void Heap<T>::reheapifyDown()
{
    if (v_weak_pointers->size() == 0)
    {
        cout << "reheapifyDown error exception\n";

        throw HEAP_EMPTY;
    }
    else if (v_weak_pointers->size() == 1)
    {
        v_weak_pointers->pop_back(); // we leave the raw data alone until destructor time
        return;
    }

    // assuming that the beginning is already taken care of
    unsigned int parent, childChosen;

    // swap the last with the first
    swap(v_weak_pointers->at(0), v_weak_pointers->at(v_weak_pointers->size() - 1));

    v_weak_pointers->pop_back();

    parent = 0;

    (this->*heap_sort[reheapDown])(parent, childChosen);

}

// called by reheapifyUp() using the heap_sort function pointer array
template<typename T>
void Heap<T>::reheapifyUp_MAX(unsigned int &p, unsigned int &c)
{
    while(v_raw_data->at(v_weak_pointers->at(c)) > v_raw_data->at(v_weak_pointers->at(p)))
    {
        // if greater swap
        swap(v_weak_pointers->at(c), v_weak_pointers->at(p));

        c = p;
        p = findParent(c);
    }
}

// called by reheapifyUp() using the heap_sort function pointer array
template<typename T>
void Heap<T>::reheapifyUp_MIN(unsigned int &p, unsigned int &c)
{
    while(v_raw_data->at(v_weak_pointers->at(c)) < v_raw_data->at(v_weak_pointers->at(p)))
    {
        // if greater swap
        swap(v_weak_pointers->at(c), v_weak_pointers->at(p));

        c = p;
        p = findParent(c);
    }
}

// called by reheapifyDown() using the heap_sort function pointer array
template<typename T>
void Heap<T>::reheapifyDown_MAX(unsigned int &p, unsigned int &c)
{
    bool checkLeft, checkRight;
    checkChildrenExist(checkLeft, checkRight, p);

    chooseChild_MAX(checkLeft, checkRight, p, c);

    while(v_raw_data->at(v_weak_pointers->at(c)) > v_raw_data->at(v_weak_pointers->at(p)))
    {
        // if greater swap
        swap(v_weak_pointers->at(c), v_weak_pointers->at(p));

        p = c;

        checkChildrenExist(checkLeft, checkRight, p);

        chooseChild_MAX(checkLeft, checkRight, p, c);
    }
}

// called by reheapifyDown() using the heap_sort function pointer array
template<typename T>
void Heap<T>::reheapifyDown_MIN(unsigned int &p, unsigned int &c)
{
    bool checkLeft, checkRight;
    checkChildrenExist(checkLeft, checkRight, p);

    chooseChild_MIN(checkLeft, checkRight, p, c);

    while(v_raw_data->at(v_weak_pointers->at(c)) < v_raw_data->at(v_weak_pointers->at(p)))
    {
        // if greater swap
        swap(v_weak_pointers->at(c), v_weak_pointers->at(p));

        p = c;

        checkChildrenExist(checkLeft, checkRight, p);

        chooseChild_MIN(checkLeft, checkRight, p, c);
    }
}

// called by reheapifyDown()
template<typename T>
void Heap<T>::checkChildrenExist(bool &left, bool &right, const unsigned int &parent)
{
    left = 2*parent + 1 < v_weak_pointers->size() ? true : false;
    right = 2*parent + 2 < v_weak_pointers->size() ? true : false;
}

// called by reheapifyDown() using the heap_sort function pointer array
template<typename T>
void Heap<T>::chooseChild_MAX(const bool &left, const bool &right, const unsigned int &parent, unsigned int &child)
{
    // if right exists, then left automatically exists
    if (right)
    {
        if (v_raw_data->at(v_weak_pointers->at(2*parent + 2)) > v_raw_data->at(v_weak_pointers->at(2*parent + 1)))
        {
            child = 2*parent + 2;
        }
        else
        {
            child = 2*parent + 1;
        }
    }
    else if (left && !right)
    {
        child = 2*parent + 1;
    }
    else
    {
        child = parent;
    }
}

// called by reheapifyDown() using the heap_sort function pointer array
template<typename T>
void Heap<T>::chooseChild_MIN(const bool &left, const bool &right, const unsigned int &parent, unsigned int &child)
{
    // if right exists, then left automatically exists
    if (right)
    {
        if (v_raw_data->at(v_weak_pointers->at(2*parent + 2)) < v_raw_data->at(v_weak_pointers->at(2*parent + 1)))
        {
            child = 2*parent + 2;
        }
        else
        {
            child = 2*parent + 1;
        }
    }
    else if (left && !right)
    {
        child = 2*parent + 1;
    }
    else
    {
        child = parent;
    }
}

template<typename U>
ostream& operator<<(ostream& out, Heap<U> &h)
{
    unsigned int count = 0;
    while (!h.v_weak_pointers->empty())
    {
        if (count % 5 == 0)
            out << endl;

        out << setw(3) << h.v_raw_data->at(h.v_weak_pointers->front()) << " ";

        h.reheapifyDown();
        ++count;
    }

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
