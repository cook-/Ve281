#include <iostream>
#include "two-three-tree.h"
#include "two-three-tree.C"
using namespace std;

int main(int argc, char *argv[])
{
    const int size = 11;
    int key[size] = {10, 30, 40, 20, 65, 80, 60, 50, 90, 100, 70};

    int val[size];
    int i;
    for(i = 0; i < size; i++)
        // We make values the same as the keys.
        val[i] = key[i];

    Tree<int, int> tree;
    for(i = 0; i < size; i++)
    {
        tree.insert(key+i, val+i);
    }
    cout << "Tree after multiple insertions" << endl;
    tree.inOrderPrint(cout);

    tree.remove(65);
    cout << "Tree after removing 65" << endl;
    tree.inOrderPrint(cout);

    tree.remove(70);
    cout << "Tree after removing 70" << endl;
    tree.inOrderPrint(cout);

    tree.remove(90);
    cout << "Tree after removing 90" << endl;
    tree.inOrderPrint(cout);

    tree.remove(100);
    cout << "Tree after removing 100" << endl;
    tree.inOrderPrint(cout);

    return 0;
}
