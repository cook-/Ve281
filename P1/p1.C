#include "p1.h"
#include "queue.h"
#include "queue.C"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cassert>
//#include <ctime>
using namespace std;

int main(int argc, char* argv[])
{
//    clock_t begin, input_end, process_end, output_end;
//    begin = clock();

    /*
     * Do some error checkings.
     */
    try {
        if (argc == 1) throw argc;
    }
    catch (int) {
        cout << "Error: Missing arguments!\n"
            << "Usage: ./p1 <grid-file>" << endl;
        return 0;
    }

    string gridFile(argv[1]);
    ifstream iFile;
    try {
        iFile.open(gridFile.c_str());
        if (!iFile) throw gridFile;
    }
    catch (string &fileName) {
        cout << "Error: Cannot open file "
            << fileName << "!" << endl;
        return 0;
    }

    /*
     * Initialize the grid and find source & destination pins.
     */
    string line;
    getline(iFile, line);
    int size = atoi(line.c_str());      // size of the grid
    getline(iFile, line);
    int levelTot = atoi(line.c_str());  // total # of levels

    Pin ****Grid = new Pin***[levelTot];
    Pin *src;
    Pin *dest;
    for (int i = levelTot - 1; i != -1; --i) {
        Grid[i] = new Pin**[size];
        for (int j = 0; j != size; ++j) {
            getline(iFile, line);   // read jth row of ith level
            while (line[0] == '#')  // skip the comments
                getline(iFile, line);
            Grid[i][j] = new Pin*[size];
            for (int k = 0; k != size; ++k) {
                Grid[i][j][k] = new Pin;
                Grid[i][j][k]->value = line[k];
                Grid[i][j][k]->l = i;
                Grid[i][j][k]->r = j;
                Grid[i][j][k]->c = k;
                Grid[i][j][k]->dist = -1;
                Grid[i][j][k]->direction = ' ';
                if (line[k] == 'S') {
                    src = Grid[i][j][k];
                    src->dist = 0;
                }
            }
        }
    }
    iFile.close();  // close the file.

//    input_end = clock();
    
    /*
     * Put examine cells into Queue until reaching destination.
     */
    Queue<Pin> q;
    Pin *examineCell = NULL;
    Pin *n = NULL;  // north pin adjacent to the examine cell;
    Pin *s = NULL;  // south pin adjacent to the examine cell;
    Pin *w = NULL;  // west pin adjacent to the examine cell;
    Pin *e = NULL;  // east pin adjacent to the examine cell;
    Pin *u = NULL;  // up pin adjacent to the examine cell;
    Pin *d = NULL;  // down pin adjacent to the examine cell;
    q.enqueue(src);

    while (!q.isEmpty()) {  // queue is not empty

        examineCell = q.dequeue();

        if ((n = northPin(Grid, examineCell, size)) != NULL
          && n->value != 'X' && n->dist < 0) {   // unblocked & unreached
            n->dist = examineCell->dist + 1;
            q.enqueue(n);
            if (n->value == 'D') {
                dest = n;
                break;
            }
        }

        if ((s = southPin(Grid, examineCell, size)) != NULL
          && s->value != 'X' && s->dist < 0) {
            s->dist = examineCell->dist + 1;
            q.enqueue(s);
            if (s->value == 'D') {
                dest = s;
                break;
            }
        }

        if ((w = westPin(Grid, examineCell, size)) != NULL
          && w->value != 'X' && w->dist < 0) {
            w->dist = examineCell->dist + 1;
            q.enqueue(w);
            if (w->value == 'D') {
                dest = w;
                break;
            }
        }

        if ((e = eastPin(Grid, examineCell, size)) != NULL
          && e->value != 'X' && e->dist < 0) {
            e->dist = examineCell->dist + 1;
            q.enqueue(e);
            if (e->value == 'D') {
                dest = e;
                break;
            }
        }

        if (examineCell->value == '^') {       // connected to the upper level
            if ((u = upPin(Grid, examineCell, levelTot)) != NULL
              && u->value != 'X' && u->dist < 0) {
                u->dist = examineCell->dist + 1;
                q.enqueue(u);
                if (u->value == 'D') {
                    dest = u;
                    break;
                }
            }
        }

        if (examineCell->value == 'V') {       // connected to the lower level
            if ((d = downPin(Grid, examineCell, levelTot)) != NULL
              && d->value != 'X' && d->dist < 0) {
                d->dist = examineCell->dist + 1;
                q.enqueue(d);
                if (d->value == 'D') {
                    dest = d;
                    break;
                }
            }
        }
    }

    /*
     * Mark the minimal path.
     */
    if (q.isEmpty())
        cout << "No path found!" << endl;
    else {
        cout << "Path found!\nThe minimal distance is "
            << dest->dist << '\n'
            << levelTot << '\n' << size << endl;
        examineCell = dest;

        while (examineCell->dist > 0) {

            if ((n = northPin(Grid, examineCell, size)) != NULL
              && n->value != 'X' && n->dist == examineCell->dist - 1) {
                examineCell = n;
                n->direction = 's';
            }
            else if ((s = southPin(Grid, examineCell, size)) != NULL
              && s->value != 'X' && s->dist == examineCell->dist - 1) {
                examineCell = s;
                s->direction = 'n';
            }
            else if ((w = westPin(Grid, examineCell, size)) != NULL
              && w->value != 'X' && w->dist == examineCell->dist - 1) {
                examineCell = w;
                w->direction = 'e';
            }
            else if ((e = eastPin(Grid, examineCell, size)) != NULL
              && e->value != 'X' && e->dist == examineCell->dist - 1) {
                examineCell = e;
                e->direction = 'w';
            }
            else if ((u = upPin(Grid, examineCell, levelTot)) != NULL
              && u->value == 'V' && u->dist == examineCell->dist - 1) {
                examineCell = u;
                u->direction = 'd';
            }
            else if ((d = downPin(Grid, examineCell, levelTot)) != NULL
              && d->value == '^' && d->dist == examineCell->dist - 1) {
                examineCell = d;
                d->direction = 'u';
            }

        }

//        process_end = clock();

        /*
         * Print the minimal path.
         */
        
        for (int i = levelTot - 1; i != -1; --i) {
            printf("#level %d\n", i);
            for (int j = 0; j != size; ++j) {
                for (int k = 0; k != size; ++k) {
                    if (Grid[i][j][k]->direction != ' ')
                        printf("%c", Grid[i][j][k]->direction);
                    else
                        printf("%c", Grid[i][j][k]->value);
                }
                printf("\n");
            }
        }
       
    }

    /*
     * Clear the non-empty Queue.
     */
    while (!q.isEmpty())
        q.dequeue();

    /*
     * Release allocated memory for grid.
     */
    for (int i = 0; i != levelTot; ++i) {
        for (int j = 0; j != size; ++j) {
            for (int k = 0; k != size; ++k)
                delete Grid[i][j][k];
            delete [] Grid[i][j];
        }
        delete [] Grid[i];
    }
    delete [] Grid;

//    output_end = clock();
//    double input_time =
//          ((double)input_end - (double)begin)/CLOCKS_PER_SEC;
//    double process_time =
//          ((double)process_end - (double)input_end)/CLOCKS_PER_SEC;
//    double output_time =
//          ((double)output_end - (double)process_end)/CLOCKS_PER_SEC;
//    cout << "Input time: " << input_time << "s" << endl;
//    cout << "Process time: " << process_time << "s" << endl;
//    cout << "Output time: " << output_time << "s" << endl;

    return 0;
}

Pin *northPin(Pin ****Grid, Pin *pin, int size) {
    if (pin->r - 1 < 0)
        return NULL;
    return Grid[pin->l][pin->r - 1][pin->c];
}

Pin *southPin(Pin ****Grid, Pin *pin, int size) {
    if (pin->r + 1 > size -1)
        return NULL;
    return Grid[pin->l][pin->r + 1][pin->c];
}

Pin *westPin(Pin ****Grid, Pin *pin, int size) {
    if (pin->c - 1 < 0)
        return NULL;
    return Grid[pin->l][pin->r][pin->c - 1];
}

Pin *eastPin(Pin ****Grid, Pin *pin, int size) {
    if (pin->c + 1 > size - 1)
        return NULL;
    return Grid[pin->l][pin->r][pin->c + 1];
}

Pin *upPin(Pin ****Grid, Pin *pin, int levelTot) {
    if (pin->l + 1 > levelTot - 1)
        return NULL;
    return Grid[pin->l + 1][pin->r][pin->c];
}

Pin *downPin(Pin ****Grid, Pin *pin, int levelTot) {
    if (pin->l - 1 < 0)
        return NULL;
    return Grid[pin->l - 1][pin->r][pin->c];
}

/*
void printGrid(Pin ****Grid, int levelTot, int size) {
    for (int i = levelTot - 1; i != -1; --i) {
        printf("#level %d/n", i);
        for (int j = 0; j != size; ++j) {
            for (int k = 0; k != size; ++k) {
                if (Grid[i][j][k]->direction != ' ')
                    printf("%c", Grid[i][j][k]->direction);
                else
                    printf("%c", Grid[i][j][k]->value);
            }
            printf("/n");
        }
    }
    printf("/n");
}
*/
