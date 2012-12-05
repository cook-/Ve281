#include <iostream>
#include "two-three-tree.h"
#include "two-three-tree.C"
using namespace std;

int main(int argc, char *argv[])
{
    const int size = 7;
    int key[size] = { 20, 30, 35, 15, 40, 50, 45 };
//    int key[size] = { 100, 200, 50, 150, 225, 180, 170, 300, 170, 300 };
//    char key[size] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H','H', 'G' };
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

    tree.remove(35);
    cout << "Tree after removing 35" << endl;
    tree.inOrderPrint(cout);

    tree.remove(45);
    cout << "Tree after removing 45" << endl;
    tree.inOrderPrint(cout);

    tree.remove(30);
    cout << "Tree after removing 30" << endl;
    tree.inOrderPrint(cout);


    return 0;
}
