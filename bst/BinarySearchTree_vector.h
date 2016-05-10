#ifndef BINARYSEARCHTREE_VECTOR_H
#define BINARYSEARCHTREE_VECTOR_H
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

    int depth(size_t farthestNode, size_t root);
    size_t highestNode(size_t n);


    BinarySearchTree(BST_TRAVERSAL_TYPE t = IN_ORDER);
    ~BinarySearchTree();

    size_t insert(const T &d, size_t root);

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
//    vector<size_t> *v_weak_pointers;


    bool uh_oh;
    int balance(size_t p);

    node current;

    void createBranches(size_t max);

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
    uh_oh = false;
    count = 0;
    current.data = 0;
    traversalType = t;
    v_raw_data = new vector<node>;

    traverse[PRE_ORDER] = &BinarySearchTree<T>::preOrder;
    traverse[IN_ORDER] = &BinarySearchTree<T>::inOrder;
    traverse[POST_ORDER] = &BinarySearchTree<T>::postOrder;
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    v_raw_data->clear();
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator<<(const T &d)
{
    int index = insert(d, 0);

    cout << "inserted " << d << " at index " << index << "\n";


    int p, gp, ggp;

    p = (index - 1) / 2;
    gp = (p - 1) / 2;
    ggp = (gp - 1) / 2;

    cout << "p = " << p << "\tgp = " << gp << "\tggp = " << ggp << endl;

    if (p < 0 || gp < 0 || ggp < 0)
    {
        exit (20);
    }

    rebalance(p);
    rebalance(gp);
    rebalance(ggp);
    return *this;
}

// not sure how to implement this
template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator>>(T &d)
{


}

// insert and return index
template<typename T>
size_t BinarySearchTree<T>::insert(const T &d, size_t root)
{
    cout << "d = " << d << " at node = " << root << endl;
    if (v_raw_data->size() == 0)
    {
        cout << "first\t";
        cout << "d = " << d << " at node = " << root << endl;
        node n;
        n.data = d;
        n.count = 1;

        v_raw_data->push_back(n);

        return v_raw_data->size() - 1;
    }
    while (root > v_raw_data->size() - 1)
    {
        node placeHolder;
        placeHolder.count = -1;
        v_raw_data->push_back(placeHolder);
    }

    if (v_raw_data->at(root).count == -1)
    {
        v_raw_data->at(root).data = d;
        v_raw_data->at(root).count = 1;
        return root;
    }
    else if (v_raw_data->at(root).data == d)
    {
        ++(v_raw_data->at(root).count);
        return root;
    }
    else if (v_raw_data->at(root).data > d) // go left
    {
        root = 2*root + 1;
        insert(d, root);
    }
    else if (v_raw_data->at(root).data < d)
    {
        root = 2*root + 2;
        insert(d, root);
    }

}




template<typename T>
void BinarySearchTree<T>::preOrder(size_t n, ostream &out)
{
    if(v_raw_data->at(n).count == -1)
    {
        return;
    }
    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    inOrder(left, out);
    out << v_raw_data->at(n).data
           << "|"
              << v_raw_data->at(n).count << endl ;
    inOrder(right,out);
}


template<typename T>
void BinarySearchTree<T>::inOrder(size_t n, ostream &out)
{
    if(v_raw_data->at(n).count == -1)
    {
        return;
    }

    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    if (left < v_raw_data->size())
    {
        inOrder(left, out);
    }


    out << n << "|" << v_raw_data->at(n).data << "|" << v_raw_data->at(n).count << "   ";

    if (v_raw_data->at(n).data < current.data)
    {
        uh_oh = true;
        cout <<  v_raw_data->at(n).data
                 << " is not bigger than " << current.data << "\t";
        exit(1);
    }
    else
    {
        current.data = v_raw_data->at(n).data;
    }

    count += v_raw_data->at(n).count;

    if (right < v_raw_data->size())
    {
        inOrder(right,out);
    }

}

template<typename T>
void BinarySearchTree<T>::postOrder(size_t n, ostream &out)
{
    if(v_raw_data->at(n).count == -1)
    {
        return;
    }
    size_t left, right;
    left = 2*n + 1;
    right = 2*n + 2;

    inOrder(left, out);
    out << v_raw_data->at(n).data
           << "|"
              << v_raw_data->at(n).count << " " ;
    inOrder(right,out);
}








template<typename T>
void BinarySearchTree<T>::rightRotate(size_t n)
{
    // left imbalance
    // +2,+1 = right

    cout << "before rotate right print\n";
    this->print(cout);
    cout << endl << endl;

    size_t l, r, ll, lr, rl, rr, lll, llr;

    l = 2*n + 1;
    r = 2*n + 2;
    ll = 2*l + 1;
    lr = 2*l + 2;
    rl = 2*r + 1;
    rr = 2*r + 2;
    lll = 2*ll + 1;
    llr = 2*ll + 2;

    createBranches(llr);


    if (v_raw_data->at(rl).count != -1 || v_raw_data->at(rr).count != -1)
    {
        cout << "before rotation\nv_raw_data->at(rl).count != -1 || v_raw_data->at(rr).count != -1" << endl;
        exit(5);
    }




    // 0 1 2 3 4 5 6 7
    // 1 3 0 7 8 4 2 x

    node temp = v_raw_data->at(n);
//    cout << "temp = " << temp.data << endl;

    v_raw_data->at(n) = v_raw_data->at(l);
    v_raw_data->at(rr) = v_raw_data->at(r);
    v_raw_data->at(r) = temp;
    v_raw_data->at(rl) = v_raw_data->at(lr);
    v_raw_data->at(lr) = v_raw_data->at(llr);
    v_raw_data->at(l) = v_raw_data->at(ll);
    v_raw_data->at(ll) = v_raw_data->at(lll);


    node temp2;
    temp2.count = -1;

    v_raw_data->at(lll) = temp2;
    v_raw_data->at(llr) = temp2;

//    v_raw_data->erase(v_raw_data->begin() + 111 - 1, v_raw_data->begin() + llr - 1);
//    if (v_raw_data->at(lll).count != -1 || v_raw_data->at(llr).count != -1)
//    {
//        cout << "after rotation\nv_raw_data->at(lll).count == -1 || v_raw_data->at(llr).count == -1" << endl;
//        exit(5);
//    }


//    cout << "rotate right print\n";
//    this->print(cout);

    cout << "printing after right rotation" << endl;
    print(cout);
    cout << endl;
//    exit(1);
}

template<typename T>
void BinarySearchTree<T>::leftRotate(size_t n)
{

    cout << "########\nrotating left from node " << n << endl;

    cout << "printing before left rotation" << endl;
    print(cout);
    cout << endl;


    size_t l, r, ll, lr, rl, rr;

    l = 2*n + 1;
    r = 2*n + 2;
    ll = 2*l + 1;
    lr = 2*l + 2;
    rl = 2*r + 1;
    rr = 2*r + 2;

    createBranches(rr);

    swap(v_raw_data->at(n), v_raw_data->at(l));
    swap(v_raw_data->at(n), v_raw_data->at(r));
    swap(v_raw_data->at(r), v_raw_data->at(rr));
    swap(v_raw_data->at(lr), v_raw_data->at(ll));

    cout << "**********\nprinting after left rotation" << endl;
    print(cout);
    cout << endl;
}


//rightBalance == -2, +1
template<typename T>
void BinarySearchTree<T>::rightLeftRotate(size_t n)
{

//    size_t root = 2*n + 1;
//    left = 2*root + 1;

    rightRotate(2*n+1);

//    cout << "rotating right and left\t" << n << endl;
//    size_t right, farthestLeft, farthestRight;

//    right = 2*n + 2;
//    farthestLeft = 2*right + 1;
//    farthestRight = 2*right + 2;

//    createBranches(farthestRight);

//    swap(v_raw_data->at(right), v_raw_data->at(farthestRight));
//    swap(v_raw_data->at(right), v_raw_data->at(farthestLeft));

//    leftRotate((n-1)/2);
    leftRotate(n);
}


// left imbalance
template<typename T>
void BinarySearchTree<T>::leftRightRotate(size_t n)
{
    //    +2,-1 = left -> then auto right

//    cout << "left imbalance\trotating left and right\t" << n << endl;
//    size_t left, farthestLeft, farthestRight;

//    left = 2*n + 1;
//    farthestLeft = 2*left + 1;
//    farthestRight = 2*left + 2;


//    createBranches(farthestRight);

//    swap(v_raw_data->at(left), v_raw_data->at(farthestRight));
//    swap(v_raw_data->at(farthestLeft), v_raw_data->at(farthestRight));

//    size_t left = 2*n + 2;//, leftRight = 2*left + 2;

    leftRotate(2*n+2);

//    rightRotate((n-1)/2);
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
    size_t left = 2*n + 1, right = 2*n + 2;
    int treeBalance, leftBalance, rightBalance, parent;

    treeBalance = balance(n);

    cout << "balance = " << treeBalance << endl;


    if (treeBalance == 1 || treeBalance == 0 || treeBalance == -1)
    {
        if (n == 0)
        {
            return;
        }
        else
        {
            parent = (int)(n-1)/2;
            rebalance(parent);
        }
    }



    if (treeBalance == 2)
    {
//        error = true;
        leftBalance = balance(left);
        cout << "left imbalance\t" << leftBalance << endl;
/*        if (leftBalance > 1) //|| leftBalance < -1)
        {
            cout << "leftBalance > 1" << endl;


            print(cout);
            cout << endl;
//            rightRotate(2*left + 1);
//            rebalance(2*left + 1);
            rebalance(left);
//                        cout << endl;
//                        print(cout);
//                        cout << endl;
//            rightLeftRotate(2*left + 1);
            return;

        }
        else if (leftBalance < -1)
        {
            cout << "leftBalance < -1" << endl;



                                        cout << endl;
                                        print(cout);
                                        cout << endl;
//            rebalance(2*left + 2);
//            rightRotate(2*left + 1);
            rebalance(left);
//            leftRightRotate(left);

//            leftRotate(2*n + 2);
            return;
        }
        else */
        if (leftBalance == 1)
        {
            cout << "left imbalance 2,1\trotate right\n";

//                                    cout << endl;
//                                    print(cout);
//                                    cout << endl;
            //    +2,+1 = right
            // right rotate starts at left
            rightRotate(n);
        }
        else if (leftBalance == -1)
        {
            cout << "left imbalance 2,-1\trotate left, right\n";
            //    +2,-1 = left -> then auto right

//                                    cout << endl;
//                                    print(cout);
//                                    cout << endl;
//                                    exit(1);
            leftRightRotate(left);                      //xxxxxxxxxxxxxxxxxxx
//            leftRotate(2*n + 2);
//            rightRotate(n);
        }

    }
    else if (treeBalance == -2)
    {
//        error = true;
        rightBalance = balance(right);
        cout << "right imbalance \t" << rightBalance << endl;
//        cout << "double right imbalance -2,+-2\n";

/*        if (rightBalance > 1) //|| rightBalance < -1)
        {
            cout << "rightBalance > 1\n";


            cout << endl << endl;
            print(cout);
            cout << endl;
//            rightLeftRotate(2*right+1);
            rebalance(right);
//            rebalance(2*right + 1);

//                            cout << endl;
//                            print(cout);
//                            cout << endl;
            return;
        }
        else if (rightBalance < -1)
        {
            cout << "rightBalance < -1\n";
            cout << endl;
            print(cout);
            cout << endl;
//            leftRotate(2*right + 2);
            rebalance(right);
//            rebalance(right);

//                                cout << endl;
//                                print(cout);
//                                cout << endl;
            return;
        }
        else */
        if (rightBalance == 1)
        {
            cout << "RIGHT imbalance -2,1\trotate right,left\n";
//            rightLeftRotate(n);
//                                    cout << endl;
//                                    print(cout);
//                                    cout << endl;
            rightLeftRotate(right);
//            leftRotate(n);
        }
        else if (rightBalance == -1)
        {
            cout << "RIGHT imbalance -2,-1\trotate left\n";
//            cout << "right -1\n";
//            cout << endl;
//            print(cout);
//            cout << endl;
            leftRotate(n);                                      // +++++++++
        }

    }

//    if (error)

//    {
//        cout << "imbalance error\n";
//        return;
//    }
//    else
//        cout << "no need to balance\n";

}




template<typename T>
ostream& BinarySearchTree<T>::print(ostream &out)
{
//    size_t count = 0;

    out << endl;
    (this->*traverse[traversalType])(0, out);

    out << "\ntotal count = " << count << endl;

    if (uh_oh)
    {
        out << "ERROR UH OH" << endl << endl;

    }

    count = 0;
    current.data = 0;
    uh_oh = false;

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

    if ((left <= v_raw_data->size() - 1) && (v_raw_data->at(left)).count != -1)
    {
        l = true;
    }
    else
    {
        l = false;
    }

    if ((right <= v_raw_data->size() - 1) && (v_raw_data->at(right)).count != -1)
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
//        cout << "left greatest = " << greatestLeft << endl;
    }

    if (checkRight)
    {
        greatestRight = highestNode(right);
//        cout << "right greatest = " << greatestRight << endl;
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
    // the count
    int c = 0;

    // if the parent/root is not blank, do incrementations
    if (v_raw_data->at(root).count != -1)
    {
        // counts back from the farthest node to the highest
        for(size_t i = farthestNode; i > root; i = (i-1)/2)
        {
            ++c;
        }
    }

//    cout << "  max node = " << farthestNode << "\tto" << root << "\tcount = " << c << endl;
    return c;
}


// returns the difference between nodes
template<typename T>
int BinarySearchTree<T>::balance(size_t p)
{
    bool checkLeft, checkRight;
    int right = 0, left = 0;

    checkChildrenExist(p, checkLeft, checkRight);

    if (checkLeft)
    {
        left = depth(highestNode(2*p + 1)
                     , p);
//        cout << "\tleft depth = " << left << endl;
    }

    if (checkRight)
    {
        right = depth(highestNode(2*p + 2), p);
//        cout << "\tright depth = " << right << endl;
    }

    return left - right;
}


template<typename T>
void BinarySearchTree<T>::createBranches(size_t max)
{
//    cout << "creating placeholding nodes\n";
    while (max > v_raw_data->size() - 1)
    {
        node placeHolder;
        placeHolder.count = -1;

        v_raw_data->push_back(placeHolder);
    }

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

//template<typename T>
//BinarySearchTree<T>::
//{

//}










#endif // BINARYSEARCHTREE_VECTOR_H
