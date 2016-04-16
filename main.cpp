#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "RandomTypeGenerator.h"
#include "Frequency.h"
#include <typeinfo>

using namespace std;


int main()
{
    RandomTypeGenerator r(false); // false is ascending order, true is descending

    Heap<string> h;

    h = r.generateStrings(); //
//    Heap<int> h;
//    h = r.generateIntegers();

    Frequency<string> f(h);

//    Frequency<int> f(h);

    f.print();

    cout << endl << endl;

    return 0;
}
