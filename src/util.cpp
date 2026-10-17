

#include "util.hpp"

double aleatorio(double min, double max){
    double r = rand() / static_cast<float> (RAND_MAX);
    double rango = max - min;
    return (r * rango + min);
}