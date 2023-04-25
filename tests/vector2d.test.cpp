#include <cassert>
#include "utils.h"

int main () {
    CVector2D vec;
    assert(vec.x == 0 && vec.y == 0);
    vec += 10;
    assert(vec.x == 10 && vec.y == 0);

    vec += CVector2D(10, 10);
    assert(vec.x == 20 && vec.y == 10);

    vec = vec * 5;
    assert(vec.x == 100 && vec.y == 50);

    vec -= CVector2D(100, 50);
    assert(vec.x == 0 && vec.y == 0);

    vec -= 10;
    assert(vec.x == -10 && vec.y == 0);

    vec = CVector2D(1, 2);
    assert(vec.x == 1 && vec.y == 2);

    vec = -vec;
    assert(vec.x == -1 && vec.y == -2);

    assert(CVector2D(0, 0) == CVector2D(0, 0));
    assert( CVector2D(100, 200) == CVector2D(100, 200));
    assert((CVector2D(100, 200) == CVector2D(200, 100)) == false);

    assert((CVector2D(100, 200) != CVector2D(100, 200)) == false);
    assert((CVector2D(100, 200) != CVector2D(200, 100)));

}