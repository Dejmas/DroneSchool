#include <cassert>
#include "utils.h"

int main () {
    assert(lerp(100, 200, 0) == 100);
    assert(lerp(100, 200, 1) == 200);
    assert(lerp(100, 200, 0.5) == 150);
    assert(lerp(100, 200, 0.9) == 190);

    assert(lerp(CVector2D(0, 0), CVector2D(100, 100), 0) == CVector2D(0, 0));
    assert(lerp(CVector2D(0, 0), CVector2D(100, 100), 1) == CVector2D(100, 100));
    assert(lerp(CVector2D(0, 0), CVector2D(100, 100), 0.5) == CVector2D(50, 50));
}