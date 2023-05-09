#include "utils.h"

#include <random>
#include <iostream>

CVector2D operator - (CCoord left, CCoord right) {
    return CVector2D(left.x - right.x, left.y - right.y);
}


double normalize_angle(double x) {
    return fmod(x + 180, 2.0*180) - 180;
}

double lerp_angle(double a, double b, double t) {

    if (fabs(a-b) >= 180) {
        if (a > b)
            a = normalize_angle(a) - 2.0 * 180;
        else
            b = normalize_angle(b) - 2.0 * 180;
    }
    return normalize_angle(lerp(a, b, t));
}

std::random_device rd;

int randInteger(int from, int to) {
    std::uniform_int_distribution<int> dist(from, to);

    return dist(rd);
}

std::ostream& operator << (std::ostream & os, CCoord coord) {
    return os << '(' << coord.x << ", " << coord.y << ')'; 
}

std::ostream& operator << (std::ostream & os, CVector2D coord) {
    return os << '(' << coord.x << ", " << coord.y << ')'; 
}
