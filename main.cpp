#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
//#include <vector>
#include "heap_vector.h"
using namespace std;


static const char alphanum[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{

    return alphanum[rand() % stringLength];
}

// randomly generate numbers, and sort them as a heap

int main()
{

    Heap <string> h;
    srand(time(NULL));
    string str = "";

    for (size_t i = 0; i < 60; ++i)
    {
//        str = "";
        for (size_t j = 0; j < 10; ++j)
        {
            str+=genRandom();
        }

        h << str;
        str = "";
    }



    cout << h << endl;
    cout << endl << endl;


//    int n;
//    cout << "Enter value: ";
//    cin >> n;

//    while (n >= 0)
//    {
//        cout << n << " has children " <<  2*n + 1 << " and " << 2*n + 2 << endl;
//        cout << n << " parent is " << (n-1)/2 << endl << endl;
//        cout << "Enter value: ";
//        cin >> n;
//    }

//    cout << endl;
//    vector<int>v;

//    srand(time(NULL));
//    for (size_t i = 0; i < 25; ++i)
//    {
//        v.push_back(rand() % 100);
//    }

//    for (vector<int>::iterator it = v.begin() ; it != v.end(); ++it)
//      cout << *it << " ";

//    cout << endl << endl;

////    v.clear();

//    vector<int>v2;


//    v2.push_back(500);

//    v = v2;

//    v2.clear();

//    for (vector<int>::iterator it = v.begin() ; it != v.end(); ++it)
//      cout << *it << " ";
//cout << endl << endl;
    return 0;
}

