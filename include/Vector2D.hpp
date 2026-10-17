

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "params.hpp"
#include <cmath>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>

class Vector2D{
private:
    double x, y;
public:
    Vector2D(double = 0, double = 0);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void setXY(double x, double y);
    Vector2D sumar(const Vector2D &v) const;
    Vector2D escalar(double num) const;
    double modulo() const;
    void normalizar();
    double distancia(const Vector2D &v) const;
    std::string toString() const;
    Vector2D operator+(const Vector2D &v) const;
    Vector2D operator*(double n) const;
    bool operator==(const Vector2D &v) const;
    bool operator!=(const Vector2D &v) const;
    Vector2D operator-(const Vector2D &v) const;//funcion colision de particula
};

Vector2D operator*(double num, const Vector2D &v);
std::ostream & operator<<(std::ostream & flujo, const Vector2D & v);
std::istream & operator>>(std::istream & flujo, Vector2D &p);

#endif