#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
//#include <vector>
//#include "heap_vector.h"
#include "Frequency.h"
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
    Frequency f;

    f.print();

    cout << endl << endl;

//    Heap <string> h;
//    bool order;
//    cin >> order;
//    h.setType(order); // false is MIN type heap (ascending order)
//    srand(time(NULL));
//    string str = "";

//    for (size_t i = 0; i < 500; ++i)
//    {
//        for (size_t j = 0; j < 10; ++j)
//        {
//            str+=genRandom();
//        }

//        h << str;
//        str = "";
//    }




    return 0;
}
