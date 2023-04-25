#ifndef UNTILS_H
#define UNTILS_H

#include <cmath>

class CVector2D {
    public:
        CVector2D(double vecx = 0, double vecy = 0): x (vecx), y(vecy) {}

        double abs() const { return sqrt(x*x + y*y); }
        CVector2D norm() const { return CVector2D(x/abs(), y/abs()); }

        CVector2D operator * (double scalar) const {
            return CVector2D(x*scalar, y*scalar);
        }
        
        CVector2D operator + (const CVector2D& rhs) const {
            return CVector2D(x+rhs.x, y+rhs.y);
        }

        CVector2D operator - () const {
            return CVector2D(-x, -y);
        }

        CVector2D operator - (const CVector2D& rhs) const {
            return *this + (- rhs);
        }

        CVector2D& operator -= (const CVector2D & rhs) {
            CVector2D res = *this - rhs;
            return *this = res;
        }

        CVector2D& operator += (const CVector2D & rhs) {
            CVector2D res = *this - rhs;
            return *this = res;
        }

    public:
        double x, y;
};

class CCoord {
    public:
        CCoord(double coordx = 0, double coordy = 0): x(coordx), y(coordy) {}

        void addVector(const CVector2D & vec) {
            x += vec.x;
            y += vec.y; 
        }

    public:
        double x, y;
};

template <class T>
T lerp(T from, T to, double fraction) {
    return from * (1 - fraction) + to * fraction;
}

#endif // UNTILS_H