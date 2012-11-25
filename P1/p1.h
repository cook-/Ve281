#ifndef __P1__
#define __P1__

struct Pin {            // represent a pin on the grid
    char value;         // possible characters: 'X', ' ' , 'D', '^', 'V'
    int l;              // which level?
    int r;              // which row?
    int c;              // which column?
    int dist;           // distance to the source pin
    char direction;     // if pin is on the path,
                        // direction = 'n', 's', 'e', 'w', 'u', 'd'
                        // otherwise, direction = ' '
};

/*
 * return the adjacent pin of a certain direction to the examine cell.
 */
Pin *northPin(Pin ****Grid, Pin *pin, int size);
Pin *southPin(Pin ****Grid, Pin *pin, int size);
Pin *westPin(Pin ****Grid, Pin *pin, int size);
Pin *eastPin(Pin ****Grid, Pin *pin, int size);
Pin *upPin(Pin ****Grid, Pin *pin, int levelTot);
Pin *downPin(Pin ****Grid, Pin *pin, int levelTot);

//void printGrid(Pin ****Grid, int levelTot, int size);

#endif /* __P1__*/
