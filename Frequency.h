#ifndef FREQUENCY_H
#define FREQUENCY_H


/*
 * node is word and its position
heap 1 is heap pointers to heap objects
each letter is a regular heap with words

if !heap(letter) create new
then insert letters
or just initialize them all


if !heap(letter).empty() then call the count

For Heap
a.     Each entry is a new node (this, if you have five "the"s then there are five nodes with "the" in it) . An entry is the word and its position in the document.
b.     As with the Binary Tree, the Heap must be implemented as an "orchard" of "vector-based" structures.(there really is not an "orchard" of heaps, but this actually
means a heap for each letter of the alphabet)

In order to assist editors, you and your teammate will write a program (first using heaps, the second time using binary trees) to do a frequency count of all of the words
contained in a document. At the end of processing a document, your program should provide the editor with the following information:
1.     A summary page that gives the word count, paragraph count, reading level, the 10 most frequently used words, the number of words which begin with each letter
of the alphabet, and the total time to process the document. Numeric constants, punctuation, and so forth should be ignored.
2.     The above is to be followed by each word, in alphabetical order, with the first letter capitalized, with its frequency of occurrence, the lines and paragraphs in which
it occurred, all in an “easy to understand” fashion.
3.     Lastly, the editor should be afforded the opportunity to save any of the above information into a file.
*/


#include <iostream>
// parser
// regex
#include <cstdlib>
#include <ctime>
#include <iomanip>
//#include <vector>
//#include <algorithm>
//#include <cmath>
#include "heap_vector.h"
using namespace std;

//template<typename T>
class Frequency
{
public:
    Frequency();
    ~Frequency();

    void print();

private:
    Heap<size_t> h;

    void initialize();
    void clear();
};



//template<typename T>
void Frequency::initialize()
{
//    h = new Heap<int>(false);

    h.setType(false);

    srand(time(NULL));

    for (size_t i = 0; i < 100; ++i)
    {

        h << rand() % 10;

    }

}

//template<typename T>
void Frequency::clear()
{
    h.clear();
}

//template<typename T>
Frequency::Frequency()
{
    initialize();
}

//template<typename T>
Frequency::~Frequency()
{
    clear();
}

// will change this to typename T
//template<typename T>
void Frequency::print()
{
    size_t previous, next, count = 0, totalCount = 0, lineCount = 0;



    if (!h.empty())
    {
        // grab the first word
        h >> previous;
        ++count;

        while (!h.empty())
        {
            h >> next;

            if (previous != next)
            {
                if (lineCount % 5 == 0)
                    cout << endl;

                cout << setw(3) << previous << "  " << setw(3) <<count << "\t";

                totalCount += count;
                ++lineCount;
                count = 0;
            }
            ++count;
            previous = next;
        }

        cout << setw(3) << next << "  " << setw(3) << count << "\n";
    }

    totalCount += count;

    cout << "\ntotal " << totalCount << endl;
}



/*
//template<typename T>
void Frequency::print()
{
    size_t previous, next, count = 0, totalCount = 0, lineCount = 0;



    if (!h.empty())
    {
        // grab the first word
        h >> previous;
        ++count;

        while (!h.empty())
        {
            h >> next;

            if (previous != next)
            {
                if (lineCount % 5 == 0)
                    cout << endl;

                cout << setw(3) << previous << "  " << setw(3) <<count << "\t";

                totalCount += count;
                ++lineCount;
                count = 0;
            }
            ++count;
            previous = next;
        }

        cout << setw(3) << next << "  " << setw(3) << count << "\n";
    }

    totalCount += count;

    cout << "\ntotal " << totalCount << endl;
}
*/

//template<typename T>
//Frequency::
//{

//}

//template<typename T>
//Frequency::
//{

//}

//template<typename T>
//Frequency::
//{

//}






#endif // FREQUENCY_H
