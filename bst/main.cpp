#include <iostream>
#include <ctime>
#include <cstdlib>
#include "BinarySearchTree_vector.h"
using namespace std;

int main()
{
    BinarySearchTree<int> bst;

//    bst << 120;

    int num;
    srand(time(NULL));

    for (size_t i = 0; i < 15; ++i)
    {
        num = rand() % 100;
        cout << i << "\t" << num << endl;

        bst << num;
    }

    bst.print(cout);

    cout << endl << endl;

    return 0;
}

