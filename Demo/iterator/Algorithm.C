#include <iostream>
using namespace std;

template<class Iter>
void genPrint(Iter itBegin, Iter itEnd)
{
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }
}
