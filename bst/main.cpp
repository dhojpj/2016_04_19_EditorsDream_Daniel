#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "BinarySearchTree_vector.h"
using namespace std;

int main()
{
    BinarySearchTree<int> bst;

    bst << 100 << 200 << 300 << 400 << 500 << 600;



//        int num;
//        srand(time(NULL));



//        size_t digits = 0, size = 10, max = 100;

//        for (size_t i = size; i > 0; i /= 10)
//        {
//            ++digits;
//        }
//        for (size_t i = 0; i < size; ++i)
//        {
//            num = rand() % max;
////            cout << i << "\t" << num << endl;
//            bst << num;
//        }
//        cout << "done inserting\n";

    cout << "\n\n\nprinting\n";
    bst.print(cout);

//    for(int i = 0; i < 60; ++i)
//    {
//        cout << i << "|" << 2*i + 1 << "|" << 2*i + 2<< endl;
//    }

    cout << endl << endl;

    return 0;
}

