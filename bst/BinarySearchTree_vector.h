#ifndef BINARYSEARCHTREE_VECTOR_H
#define BINARYSEARCHTREE_VECTOR_H

// since we're using nodes, calling the data of the node returns the value in template T

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
#include <algorithm>
using namespace std;

enum BST_TRAVERSAL_TYPE {PRE_ORDER, IN_ORDER, POST_ORDER};
enum BST_ERROR_TYPE {EMPTY};


template<typename T>
class BinarySearchTree
{
struct node
{
    T data;
    int count;
};

public:
    typedef void (BinarySearchTree<T>::*fptr)(size_t n, ostream &out) ;

//    typedef void (BinarySearchTree<T>::*fptr)() const;


int depth(size_t farthestNode, size_t root);
size_t highestNode(size_t n);


    BinarySearchTree(BST_TRAVERSAL_TYPE t = IN_ORDER);
//    BinarySearchTree(const T &d);
//    BinarySearchTree(const BinarySearchTree<T> &other);
    ~BinarySearchTree();
//    BinarySearchTree<T>& operator=(const BinarySearchTree<T> &other);

    void insert(const T &d, size_t root);

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

    ostream& print(ostream &out);

    void setTraversal(BST_TRAVERSAL_TYPE t);
    BST_TRAVERSAL_TYPE currentTraversal();

    BinarySearchTree<T>& operator<<(const T &d);
    BinarySearchTree<T>& operator>>(T &d);

    template<typename U>
    friend ostream& operator<<(ostream& out, const BinarySearchTree<U> &other);

    template<typename U>
    friend istream& operator>>(istream& in, BinarySearchTree<U> &other);

private:
    vector<node> *v_raw_data;
    vector<size_t> *v_weak_pointers;

    int balance(size_t p);

    string typeOfTemplate;
    bool regularSort;

    void setVectorType();

    BST_TRAVERSAL_TYPE traversalType;
    fptr traverse[3];

    void rebalance(size_t n);
    size_t findParent(size_t child);

    size_t child(size_t parent);

    void leftRotate(size_t n); // needs to reshuffle the children
    void rightLeftRotate(size_t n);

    void rightRotate(size_t n);
    void leftRightRotate(size_t n);

    void checkChildrenExist(size_t n, bool &l, bool &r);
    void checkVoidChildren(size_t p, bool &l, bool &r);

//    static WHICH_CHILD direction[2];

//    void copy(node<T> *r);
//    void nukem(node<T>* &r);


//    bool balanced(node<T> *r);
//    node<T>* theMost(node<T>*r, WHICH_CHILD child) const;

//    void initialize(node<T> *n, BST_TRAVERSAL_TYPE  t );
//    size_t totalNodes(node<T> *r);
//    size_t totalDataItems(node<T> *r);

//    node<T>* createRightVine(node<T>* r);
//    node<T>* balanceVine(node<T>* r, size_t nodeCount);
//    ostream& print(ostream &out = cout) const;

    void preOrder(size_t n, ostream &out) ;
    void inOrder(size_t n, ostream &out) ;
    void postOrder(size_t n, ostream &out) ;

    void insert_regular(const T &d);
    void insert_irregular(const T &d);
        int count;

};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BST_TRAVERSAL_TYPE t)
{
    count = 0;
    traversalType = t;
    v_raw_data = new vector<node>;
    v_weak_pointers = new vector<size_t>;

    traverse[PRE_ORDER] = &BinarySearchTree<T>::preOrder;
    traverse[IN_ORDER] = &BinarySearchTree<T>::inOrder;
    traverse[POST_ORDER] = &BinarySearchTree<T>::postOrder;

}

//template<typename T>
//BinarySearchTree::BinarySearchTree(const T &d)
//{
//    BinarySearchTree(IN_ORDER);

//}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    v_weak_pointers->clear();
    v_raw_data->clear();
}

//template<typename T>
//void BinarySearchTree<T>::setVectorType()
//{
//    if (typeOfTemplate[0] == 'P' || typeOfTemplate == typeid(bool).name()
//        || typeOfTemplate == typeid(short).name() || typeOfTemplate == typeid(unsigned short).name()
//        || typeOfTemplate == typeid(int).name() || typeOfTemplate == typeid(unsigned int).name()
//        || typeOfTemplate == typeid(long).name() || typeOfTemplate == typeid(unsigned long).name()
//        || typeOfTemplate == typeid(double).name() || typeOfTemplate == typeid(float).name()
//        || typeOfTemplate == typeid(char).name()
//        )
//    {
//        regularSort = true;
//    }
//    else
//    {
//        regularSort = false;
//    }
//}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator<<(const T &d)
{
//    cout << "operator<<\n";
    insert(d, 0);

    rebalance(0);

//    return
    // need to return something to chain it
    return *this;
}

// not sure how to implement this
template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator>>(T &d)
{
//    d = v->front();


}

template<typename T>
void BinarySearchTree<T>::insert(const T &d, size_t root)
{
    if (v_raw_data->size() == 0)
    {
        node n;
        n.data = d;
        n.count = 1;

        v_raw_data->push_back(n);
        v_weak_pointers->push_back(v_raw_data->size() - 1);

        return;
    }
    while (root > v_weak_pointers->size() - 1)
    {
        node placeHolder;
        placeHolder.count = -1;

        v_raw_data->push_back(placeHolder);
        v_weak_pointers->push_back(v_raw_data->size() - 1);
    }

    if ((v_raw_data->at(v_weak_pointers->at(root))).count == -1)
    {
        v_raw_data->at(v_weak_pointers->at(root)).data = d;
        v_raw_data->at(v_weak_pointers->at(root)).count = 1;
        return;
    }

    if (v_raw_data->at(v_weak_pointers->at(root)).data == d)
    {
        // if node exists; increment ++count
        ++(v_raw_data->at(v_weak_pointers->at(root)).count);
        return;
    }
    else if (v_raw_data->at(v_weak_pointers->at(root)).data > d) // go left
    {
        root = 2*root + 1;
    }
    else if (v_raw_data->at(v_weak_pointers->at(root)).data < d)
    {
        root = 2*root + 2;
    }

    insert(d, root);
}




template<typename T>
void BinarySearchTree<T>::preOrder(size_t n, ostream &out)
{
    if(v_raw_data->at(v_weak_pointers->at(n)).count == -1)
    {
        return;
    }
    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    inOrder(left, out);
    out << v_raw_data->at(v_weak_pointers->at(n)).data
           << "|"
              << v_raw_data->at(v_weak_pointers->at(n)).count << endl ;
    inOrder(right,out);
}


template<typename T>
void BinarySearchTree<T>::inOrder(size_t n, ostream &out)
{



//    cout << "now printing\n";

    if(v_raw_data->at(v_weak_pointers->at(n)).count == -1)
    {
//        cout << "now returning\n";
        return;
    }

//    cout << "searching for " << n << " children\n";
    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    if (!(left > v_weak_pointers->size() - 1))
    {
        inOrder(left, out);
//        cout << left << " is " << n << " left child\n";
    }

    out << v_raw_data->at(v_weak_pointers->at(n)).data
           << "|"
              << v_raw_data->at(v_weak_pointers->at(n)).count << endl;

    count += v_raw_data->at(v_weak_pointers->at(n)).count;

    if (!(right > v_weak_pointers->size() - 1))
    {
//        cout << right << " is " << n << " right child\n";
        inOrder(right,out);
    }


}

template<typename T>
void BinarySearchTree<T>::postOrder(size_t n, ostream &out)
{
    if(v_raw_data->at(v_weak_pointers->at(n)).count == -1)
    {
        return;
    }
    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    inOrder(left, out);
    out << v_raw_data->at(v_weak_pointers->at(n)).data
           << "|"
              << v_raw_data->at(v_weak_pointers->at(n)).count << " " ;
    inOrder(right,out);
}

template<typename T>
void BinarySearchTree<T>::leftRotate(size_t n)
{
    //    "root" goes left, right goes to root
    //    previous root becomes current root's left child
    //    and right's left child gets inserted into root at right

    cout << "rotating left\t" << n << endl;
    size_t left, right, farthestRight;

    left = 2*n + 1;
    right = 2*n + 2;
    farthestRight = 2*right + 2;

    swap(v_weak_pointers->at(farthestRight), v_weak_pointers->at(left));
    swap(v_weak_pointers->at(n), v_weak_pointers->at(left));
    swap(v_weak_pointers->at(n), v_weak_pointers->at(right));
}

template<typename T>
void BinarySearchTree<T>::rightLeftRotate(size_t n)
{
//    else if (treeBalance == -2)
//    {
//        if (rightBalance == -2)
//        {
//            rebalance(right);
//            return;
//        }
//        else if (rightBalance == 1)
//        {
//            cout << "rotate right,left\n";
//            rightLeftRotate(n);
//        }

    cout << "rotating right and left\t" << n << endl;
    size_t right, farthestLeft, farthestRight;

    right = 2*n + 2;
    farthestLeft = 2*right + 1;
    farthestRight = 2*right + 2;

    while (farthestRight > v_weak_pointers->size() - 1)
    {
        cout << "placeholder " << v_weak_pointers->size() -1 << endl;
        node placeHolder;
        placeHolder.count = -1;

        v_raw_data->push_back(placeHolder);
        v_weak_pointers->push_back(v_raw_data->size() - 1);
    }

    swap(v_weak_pointers->at(right), v_weak_pointers->at(farthestRight));
    swap(v_weak_pointers->at(right), v_weak_pointers->at(farthestLeft));

    leftRotate(n);
}



template<typename T>
void BinarySearchTree<T>::rightRotate(size_t n)
{
    // left imbalance
//        else if (leftBalance == 1)
//        {
//            cout << "rotate right\n";
//            //    +2,+1 = right
//            rightRotate(n);

    cout << "rotating right\t" << n << endl;
    size_t left, right, farthestLeft;

    left = 2*n + 1;
    farthestLeft = 2*left + 1;
    right = 2*n + 2;

    swap(v_weak_pointers->at(right), v_weak_pointers->at(farthestLeft));
    swap(v_weak_pointers->at(left), v_weak_pointers->at(right));
    swap(v_weak_pointers->at(n), v_weak_pointers->at(right));
}

template<typename T>
void BinarySearchTree<T>::leftRightRotate(size_t n)
{
    // left imbalance
//        else if (leftBalance == 1)
//        {
//            cout << "rotate right\n";
//            //    +2,+1 = right
//            rightRotate(n);
//        }
//        else if (leftBalance == -1)
//        {
//            cout << "rotate left, right\n";
//            //    +2,-1 = left -> then auto right
//            leftRightRotate(n);


    cout << "rotating left and right\t" << n << endl;
    size_t left, farthestLeft, farthestRight;

    left = 2*n + 1;
    farthestLeft = 2*left + 1;
    farthestRight = 2*left + 2;

//    while (farthestRight > v_weak_pointers->size() - 1)
//    {
////        cout << "placeholder " << v_weak_pointers->size() -1 << endl;
//        node placeHolder;
//        placeHolder.count = -1;

//        v_raw_data->push_back(placeHolder);
//        v_weak_pointers->push_back(v_raw_data->size() - 1);
//    }

    swap(v_weak_pointers->at(left), v_weak_pointers->at(farthestRight));
    swap(v_weak_pointers->at(farthestLeft), v_weak_pointers->at(farthestRight));

    rightRotate(n);
}





//template<typename T>
//BinarySearchTree<T>::
//{

//}


//template<typename T>
//BinarySearchTree<T>::
//{

//}


//template<typename T>
//BinarySearchTree<T>::
//{

//}


template<typename T>
void BinarySearchTree<T>::rebalance(size_t n)
{
//    bool checkLeft, checkRight;
    size_t left = 2*n + 1, right = 2*n + 2;
    int treeBalance, leftBalance = balance(left), rightBalance = balance(right);

//    checkChildrenExist(n, checkLeft, checkRight);

    treeBalance = balance(n);

    if (treeBalance == 2)
    {
        cout << "left imbalance\t" << leftBalance << endl;
        if (leftBalance == 2)
        {
            cout << "double left imbalance 2,2\n";
            rebalance(left);
            return;
        }
        else if (leftBalance == 1)
        {
                                cout << "left imbalance 2,1\n";
            cout << "rotate right\n";
            //    +2,+1 = right
            rightRotate(n);
        }
        else if (leftBalance == -1)
        {
                                cout << "left imbalance 2,-1\n";
            cout << "rotate left, right\n";
            //    +2,-1 = left -> then auto right
            leftRightRotate(n);
        }

    }
    else if (treeBalance == -2)
    {
        cout << "right imbalance \t" << rightBalance << endl;
        if (rightBalance == -2)
        {
            cout << "double right imbalance -2,-2\n";
            rebalance(right);
            return;
        }
        else if (rightBalance == 1)
        {
            cout << "right imbalance -2,1\n";
            cout << "rotate right,left\n";
            rightLeftRotate(n);
        }
        else if (rightBalance == -1)
        {
            cout << "right imbalance -2,-1\n";
            cout << "rotate left\n";
//            cout << "right -1\n";
            leftRotate(n);
        }

    }
//    else
//        cout << "no need to balance\n";

}




template<typename T>
ostream& BinarySearchTree<T>::print(ostream &out)
{
    (this->*traverse[traversalType])(0, out);

    cout << "\ntotal count = " << count << endl;

    return out;
}




//template<typename T>
//BinarySearchTree<T>::
//{

//}




//template<typename T>
//void BinarySearchTree<T>::checkVoidChildren(size_t p, bool &l, bool &r)
//{
////    cout << "exist? " << n << endl;
//    size_t left = 2*p + 1, right = 2*p + 2;

//    if (left < v_raw_data->size() - 1)
//    {
//        l = true;
//    }
//    else
//    {
//        l = false;
//    }

//    if (right < v_raw_data->size() - 1)
//    {
//        r = true;
//    }
//    else
//    {
//        r = false;
//    }
//}

template<typename T>
void BinarySearchTree<T>::checkChildrenExist(size_t n, bool &l, bool &r)
{
    size_t left = 2*n + 1, right = 2*n + 2;

    if ((left <= v_raw_data->size() - 1) && (v_raw_data->at(v_weak_pointers->at(left))).count != -1)
    {
        l = true;
    }
    else
    {
        l = false;
    }

    if ((right <= v_raw_data->size() - 1) && (v_raw_data->at(v_weak_pointers->at(right))).count != -1)
    {
        r = true;
    }
    else
    {
        r = false;
    }
}

// finds out how far the branch grows from a specific node
template<typename T>
size_t BinarySearchTree<T>::highestNode(size_t n)
{
    bool checkLeft, checkRight;
    size_t left = 2*n + 1, right = 2*n + 2;
    size_t greatestLeft = 0, greatestRight = 0, greatest = n;

    checkChildrenExist(n, checkLeft, checkRight);

    if (checkLeft)
    {
        greatestLeft = highestNode(left);
    }

    if (checkRight)
    {
        greatestRight = highestNode(right);
    }

    if ((greatestLeft > greatestRight) && greatestLeft > greatest)
    {
        greatest = greatestLeft;
    }
    else if ((greatestLeft < greatestRight) && greatestRight > greatest)
    {
        greatest = greatestRight;
    }

//    cout << "highest node " << greatest << endl;

    return greatest;
}

// counting the branches from the farthest node
template<typename T>
int BinarySearchTree<T>::depth(size_t farthestNode, size_t root)
{
//    cout << "depth\t";
//    cout << "farth  " << farthestNode << endl;
//    cout << "root = " << root << endl;
    // the count
    int c = 0;

    // if the parent/root is not blank, do incrementations
    if (v_raw_data->at(v_weak_pointers->at(root)).count != -1)
    {
        // counts back from the farthest node to the highest
        for(size_t i = farthestNode; i > root; i = (i-1)/2)
        {
            ++c;
        }
    }

//    cout << "max node = " << farthestNode << "\tto" << root << "\t" << c << endl;
    return c;
}


template<typename T>
int BinarySearchTree<T>::balance(size_t p)
{
    bool checkLeft, checkRight;
    int right = 0, left = 0;

    checkChildrenExist(p, checkLeft, checkRight);

    if (checkLeft)
    {
        left = depth(highestNode(2*p + 1), 2*p + 1);
//        cout << "left " << left << endl;
    }
//    else
//        cout << "no left\n";

    if (checkRight)
    {

        right = depth(highestNode(2*p + 2), 2*p + 2);
//        cout << "rightt " << right << endl;
    }
    /*
    else
        cout << "no right\n";*/


    return left - right;
}



//template<typename T>
//BinarySearchTree<T>::
//{

//}











#endif // BINARYSEARCHTREE_VECTOR_H
