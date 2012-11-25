#include <iostream>
#include "IntList.h"

using namespace std;

int main() 
{
    IntList s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.print();

    ListIter it = s.begin();
    *it = 4;
    s.print();

    return 0;
}
