#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "BinarySearchTree_vector.h"
using namespace std;

int main()
{
    BinarySearchTree<int> bst;

    int num;
    srand(time(NULL));


//    cout << bst.depth(50,0) << endl;

//    size_t count = 0, digits = 0, size = 23;

//    for (size_t i = size; i > 0; i /= 10)
//    {
//        ++digits;
//    }

//    for (size_t i = 0; i <= size; ++i)
//    {
//        if (count % 5 == 0)
//            cout << endl;
//        cout << setw(digits) << i << "|" <<
//                setw(digits) << (2*i + 1) << "|"<<
//                setw(digits) << (2*i + 2) << " ";
//        ++count;
//    }

//    cout << endl << endl;


////cout << "inserted " << 50 << endl;
//    bst << 50;
//    cout << "\tinserted\n";


////cout << "inserted " << 25 << endl;
////bst << 25;
//    bst << 100;
//    cout << "\tinserted\n";

//    bst << 200;
//    cout << "\tinserted\n";


////    exit(1);
//////cout << "inserted " << 0 << endl;
//bst << 0;
//cout << "inserting " << 1 << endl;
//bst << 1;
//cout << "inserting " << 2 << endl;
//bst << 2;

    for (size_t i = 0; i < 500; ++i)
    {
        num = rand() % 100;
        cout << i << "\t" << num << endl;

        bst << num;
    }

    cout << "\n\n\nprinting\n";
    bst.print(cout);

    cout << endl << endl;

    return 0;
}

