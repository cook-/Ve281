#include "two-three-tree.h"
#include "two-three-tree.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

int main()
{
    Tree<int, int> pTree;
    Tree<int, int> eTree;
    Tree<string, string> nTree;

    while (cin) {
        string op;
        cin >> op;

        if (op == "insert") {
            int population;
            int economy;
            string name;
            cin >> population >> economy >> name;
            cout << "insert " << population << " "
                 << economy << " " << name << endl;


            bool success = (pTree.search(population) == NULL) &&
                           (eTree.search(economy) == NULL) &&
                           (nTree.search(name) == NULL);
            if (success) {
                string* newName = new string(name);
                int* newPopulation = new int(population);
                int* newEconomy = new int(economy);
                pTree.insert(newPopulation, newPopulation);
                eTree.insert(newEconomy, newEconomy);
                nTree.insert(newName, newName);
                cout << "Insertion successful" << endl;
            }
            else
                cout << "Insertion failed" << endl;
        }

        if (op == "search") {
            int field;
            cin >> field;
            if (field == 1) {
                int population;
                cin >> population;
            }
            if (field == 2) {

            }
            if (field == 3) {

            }
        }

        if (op == "remove") {
            int field;
            cin >> field;
            if (field == 1) {

            }
            if (field == 2) {

            }
            if (field == 3) {

            }
        }

        if (op == "list") {
            int field;
            cin >> field;
            if (field == 1)
                pTree.inOrderPrint(cout);
            if (field == 2)
                eTree.inOrderPrint(cout);
            if (field == 3)
                nTree.inOrderPrint(cout);
        }
    }
    return 0;
}
