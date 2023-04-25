#include <cassert>
#include "utils.h"

int main () {
    CVector2D vec(100, 50);
    
    CCoord coord(0, 0);
    assert(coord.x == 0 && coord.y == 0);

    coord.addVector(vec);
    assert(coord.x == 100 && coord.y == 50);

    coord.addVector(vec);
    assert(coord.x == 200 && coord.y == 100);
}