#include "two-three-tree.h"
#include "two-three-tree.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

struct Record {
    int *pPopulation;
    int *pEconomy;
    string *pName;
    friend ostream& operator<<(ostream&, Record);
};

ostream& operator<<(ostream& os, Record record) {
    os << *(record.pPopulation) << " "
       << *(record.pEconomy) << " "
       << *(record.pName);
    return os;
}

int main()
{
    Tree<int, Record> pTree;
    Tree<int, Record> eTree;
    Tree<string, Record> nTree;

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

            if (pTree.search(population) == NULL &&
              eTree.search(economy) == NULL &&
              nTree.search(name) == NULL) {
                
                int *pPopulation = new int(population);
                int *pEconomy = new int(economy);
                string *pName = new string(name);
                Record *pRecord = new Record;
                pRecord->pPopulation = pPopulation;
                pRecord->pEconomy = pEconomy;
                pRecord->pName = pName;

                pTree.insert(pPopulation, pRecord);
                eTree.insert(pEconomy, pRecord);
                nTree.insert(pName, pRecord);
                cout << "Insertion successful" << endl;
            }
            else
                cout << "Insertion failed" << endl;
        }

        if (op == "search") {
            int field;
            cin >> field;
            Record *pRecord = NULL;

            if (field == 1) {
                int population;
                cin >> population;
                cout << "search " << field << " " << population << endl;
                pRecord = pTree.search(population);
            }
            if (field == 2) {
                int economy;
                cin >> economy;
                cout << "search " << field << " " <<economy << endl;
                pRecord = eTree.search(economy);
            }
            if (field == 3) {
                string name;
                cin >> name;
                cout << "search " << field << " " << name << endl;
                pRecord = nTree.search(name);
            }

            if (pRecord != NULL)
                cout << "Record found: "
                     << *(pRecord->pPopulation) << " "
                     << *(pRecord->pEconomy) << " "
                     << *(pRecord->pName) << endl;
            else
                cout << "No record found" << endl;

        }

        if (op == "remove") {
            int field;
            cin >> field;
            Record *pRecord = NULL;
            if (field == 1) {
                int population;
                cin >> population;
                cout << "remove " << field << " " << population << endl;
                pRecord = pTree.search(population);
            }
            if (field == 2) {
                int economy;
                cin >> economy;
                cout << "remove " << field << " " << economy << endl;
                pRecord = eTree.search(economy);
            }
            if (field == 3) {
                string name;
                cin >> name;
                cout << "remove " << field << " " << name << endl;
                pRecord = nTree.search(name);
            }

            if (pRecord != NULL) {
                pTree.remove(*(pRecord->pPopulation));
                eTree.remove(*(pRecord->pEconomy));
                nTree.remove(*(pRecord->pName));
                // delete pRecord;
                cout << "Remove record: "
                     << *(pRecord->pPopulation) << " "
                     << *(pRecord->pEconomy) << " "
                     << *(pRecord->pName) << endl;
            }
            else
                cout << "Removal failed" << endl;
        }

        if (op == "list") {
            int field;
            cin >> field;
            cout << "list " << field << endl;
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
