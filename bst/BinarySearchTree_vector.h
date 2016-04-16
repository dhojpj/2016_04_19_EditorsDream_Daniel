#ifndef BINARYSEARCHTREE_VECTOR_H
#define BINARYSEARCHTREE_VECTOR_H

// since we're using nodes, calling the data of the node returns the value in template T
// rebalances itself automatically -- AVL algorithm

/*
void preOrder(size_t rootIndexValue)
{
if (rootIndexValue == -1)
return;

cout << data;

preOrder(left)
preOrder(right)
}


void inOrder(size_t rootIndexValue)
{
if (rootIndexValue == -1)
return;

preOrder(thisleft)
cout << data;

preOrder(thisright)
}

void postOrder(size_t rootIndexValue)
{
if (rootIndexValue == -1)
return;

postOrder(thisleft)
postOrder(thisright)
cout << data;

}




leftChild
(2*n) + 1


rightChild
(2*n) + 2

 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>
#include <vector>
#include <typeinfo>
using namespace std;

enum BST_TRAVERSAL_TYPE {IN_ORDER, PRE_ORDER, POST_ORDER};
enum BST_ERROR_TYPE {EMPTY};

template<typename T>
struct node
{
    T data;
    int count = 0;
};

template<typename T>
class BinarySearchTree
{
public:
    typedef void (BinarySearchTree<T>::*fptr)() const;

    typedef void (BinarySearchTree<T>::*fptr)() const;


    BinarySearchTree(BST_TRAVERSAL_TYPE t = IN_ORDER);
//    BinarySearchTree(const T &d);
//    BinarySearchTree(const BinarySearchTree<T> &other);
    ~BinarySearchTree();
//    BinarySearchTree<T>& operator=(const BinarySearchTree<T> &other);

    void insert(const T &d);

    bool empty() const;
    bool balanced();

    size_t find(const T &d);
    void clear();
    bool remove(const T &d, size_t c = 1);
    bool removeAll(const T &d);
    size_t totalData();
    size_t totalNodes();
    size_t depth();
    const T& leftMost() const;
    const T& rightMost() const;

    void rebalance();
    void setTraversal(BST_TRAVERSAL_TYPE t);
    BST_TRAVERSAL_TYPE currentTraversal();

    BinarySearchTree<T>& operator<<(const T &d);
    BinarySearchTree<T>& operator>>(T &d);

    template<typename U>
    friend ostream& operator<<(ostream& out, const BinarySearchTree<U> &other);

    template<typename U>
    friend istream& operator>>(istream& in, BinarySearchTree<U> &other);

private:
    vector<T> *v_raw_data;
    vector<size_t> *v_weak_pointers;

    string typeOfTemplate;
    bool regularSort;

    void setVectorType();

    BST_TRAVERSAL_TYPE traversalType;
    fptr whatToDo[3];


    size_t findParent(size_t child);

    size_t child(size_t parent);

    size_t depth(size_t n);
    size_t leftRotate(size_t n); // needs to reshuffle the children
    size_t rightRotate(size_t n);


//    static WHICH_CHILD direction[2];

//    void copy(node<T> *r);
//    void nukem(node<T>* &r);
//    void inOrder(node<T>* r, ostream &out) const;
//    void preOrder(node<T>* r, ostream &out) const;
//    void postOrder(node<T>* r, ostream &out) const;

//    bool balanced(node<T> *r);
//    void rebalance(node<T> *r);
//    node<T>* theMost(node<T>*r, WHICH_CHILD child) const;

//    void initialize(node<T> *n, BST_TRAVERSAL_TYPE  t );
//    size_t totalNodes(node<T> *r);
//    size_t totalDataItems(node<T> *r);

//    node<T>* createRightVine(node<T>* r);
//    node<T>* balanceVine(node<T>* r, size_t nodeCount);
//    ostream& print(ostream &out = cout) const;

    void insert_regular(const T &d);
    void insert_irregular(const T &d);

};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BST_TRAVERSAL_TYPE t)
{
    traversalType = t;
    v = new vector<T>;
}

//template<typename T>
//BinarySearchTree::BinarySearchTree(const T &d)
//{
//    BinarySearchTree(IN_ORDER);

//}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    v->clear();
}

template<typename T>
void BinarySearchTree<T>::setVectorType()
{
    if (typeOfTemplate[0] == 'P' || typeOfTemplate == typeid(bool).name()
        || typeOfTemplate == typeid(short).name() || typeOfTemplate == typeid(unsigned short).name()
        || typeOfTemplate == typeid(int).name() || typeOfTemplate == typeid(unsigned int).name()
        || typeOfTemplate == typeid(long).name() || typeOfTemplate == typeid(unsigned long).name()
        || typeOfTemplate == typeid(double).name() || typeOfTemplate == typeid(float).name()
        || typeOfTemplate == typeid(char).name()
        )
    {
        regularSort = true;
    }
    else
    {
        regularSort = false;
    }
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator<<(const T &d)
{
    // insert into tree, then rebalance it
}

// not sure how to implement this
template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator>>(T &d)
{
    d = v->front();

    // rebalance tree
}

template<typename T>
void BinarySearchTree<T>::insert(const T &d)
{

    // if node exists; increment ++count


    // if not, create new and insert

    node n(data = d);

    ++n.count;


}

//template<typename T>
//BinarySearchTree<T>::
//{

//}



#endif // BINARYSEARCHTREE_VECTOR_H
