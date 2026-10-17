

#ifndef CONJUNTOPARTICULAS_H
#define CONJUNTOPARTICULAS_H

#include "Particula.hpp"
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

const int TAM_BLOQUE = 3;

class ConjuntoParticulas{
private:
    Particula *conjunto;
    int capacidad;
    int num_particulas;
public:
    ConjuntoParticulas(int = 0);
    ConjuntoParticulas(const ConjuntoParticulas &c);
    ConjuntoParticulas & operator=(const ConjuntoParticulas &c);
    ~ConjuntoParticulas();

    int size() const;
    void agregar(const Particula &p);
    void borrar(int n);
    const Particula& obtener(int n) const;
    Particula& obtener(int n);
    void reemplazar(int n, const Particula &p);
    void mover(int tipo_mov = 0);
    void gestionarColisiones();
    std::string toString() const;
    ConjuntoParticulas operator+(const ConjuntoParticulas &c) const;
    ConjuntoParticulas & operator +=(const ConjuntoParticulas &c);
    ConjuntoParticulas & operator+=(const Particula &p);
    ConjuntoParticulas & operator -=(const int ind);
    Particula & operator[](const int ind);
    const Particula & operator[](const int ind) const;
private:
    void reservar(const int capacidad);
    void copiar(const ConjuntoParticulas &c);
    void liberar();
    void redimension(bool aumentar = true);
    bool contiene(const Particula &p) const;
};

ConjuntoParticulas & operator+=(const Particula &p, ConjuntoParticulas &c);

std::ostream & operator<<(std::ostream & flujo, const ConjuntoParticulas & c);
std::istream & operator>>(std::istream & flujo, ConjuntoParticulas & c);


#endif