#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "RandomTypeGenerator.h"
#include "Frequency.h"
using namespace std;

int main()
{
    RandomTypeGenerator r; // need this object for the next call
    Heap<int> h = r.generateIntegers(); //

    Frequency<int> f(h);

    f.print();

    cout << endl << endl;

    return 0;
}
