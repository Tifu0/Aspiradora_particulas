

#ifndef PARTICULA_H
#define PARTICULA_H

#include "Vector2D.hpp"
#include "params.hpp"
#include "util.hpp"
#include <sstream>
#include <iostream>

class Particula{
private:
    Vector2D posicion;
    Vector2D velocidad;
    Vector2D aceleracion;
    double radio;
    int tipo;
public:
    Particula(int tipo = 0);
    Particula(Vector2D ,Vector2D , Vector2D , double , int ) ;
    Vector2D getPosicion() const;
    Vector2D getVelocidad() const;
    Vector2D getAceleracion() const;
    double getRadio() const;
    int getTipo() const;
    void setPosicion(Vector2D posicion);
    void setVelocidad(Vector2D velocidad);
    void setAceleracion(Vector2D aceleracion);
    void setRadio(double radio);
    void mover();
    void rebotar();
    bool colision(const Particula &otro) const;
    void choque(Particula &p);
    std::string toString() const;
    void wrap();
    bool operator==(const Particula &p) const;//operador suma de conjuntoparticulas
    bool operator!=(const Particula &p) const;
};

std::ostream& operator<<(std::ostream & flujo, const Particula & p);
std::istream& operator>>(std::istream & flujo, Particula & p);

#endif