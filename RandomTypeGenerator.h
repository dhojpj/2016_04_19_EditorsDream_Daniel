#ifndef RANDOMTYPEGENERATOR_H
#define RANDOMTYPEGENERATOR_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Frequency.h"

using namespace std;

//enum TYPE_OF_DATA {I, S, U};

class RandomTypeGenerator
{
public:
    RandomTypeGenerator(bool m = true);
//    RandomTypeGenerator(TYPE_OF_DATA t);
    ~RandomTypeGenerator();

//    typedef void (RandomTypeGenerator::*fptr)();

    Heap<int>& generateIntegers();
    Heap<string>& generateStrings();

//    void setType(TYPE_OF_DATA t);
//    void generateData();
private:
    bool MAX_or_MIN;
//    TYPE_OF_DATA type;
//    fptr genPtrs[sizeOfGenPtrs];
//    size_t sizeOfGenPtrs = 2;
};


RandomTypeGenerator::RandomTypeGenerator(bool m)
{
    srand(time(NULL));
    MAX_or_MIN = m;

}

RandomTypeGenerator::~RandomTypeGenerator()
{

}

Heap<int>& RandomTypeGenerator::generateIntegers()
{
    Heap<int>* h = new Heap<int>(MAX_or_MIN);

    for (size_t i = 0; i < 600000; ++i)
    {
        *h << rand() % 100;
    }

    return *h;
}

Heap<string>& RandomTypeGenerator::generateStrings()
{
    Heap<string>* h = new Heap<string>(MAX_or_MIN);

    char alphanum[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

    int stringLength = sizeof(alphanum) - 1;

    string str = "";

    for (size_t i = 0; i < 5000; ++i)
    {
        for (size_t j = 0; j < 10; ++j)
        {
            str+= alphanum[rand() % stringLength];
        }

        *h << str;
        str = "";
    }

    return *h;

}

//RandomTypeGenerator::
//{

//}


#endif // RANDOMTYPEGENERATOR_H
