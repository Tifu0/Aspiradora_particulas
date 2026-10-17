

#include "Vector2D.hpp"


//MÉTODOS PÚBLICOS

//constructor

Vector2D::Vector2D(double _x, double _y) : x(_x), y(_y) {}

//getters y setters

double Vector2D::getX() const{ return x; }
double Vector2D::getY() const{ return y; }
void Vector2D::setX(double x){ this->x = x; }
void Vector2D::setY(double y){ this->y = y; }
void Vector2D::setXY(double x, double y){
    this->x = x;
    this->y = y;
}

//Otras funcionalidades

Vector2D Vector2D::sumar(const Vector2D &v) const{
    return (*this) + v;
}

Vector2D Vector2D::escalar(double num) const{
    return (*this) * num;
}

double Vector2D::modulo() const{
    return std::sqrt(x * x + y * y);
}

void Vector2D::normalizar() {
    double mod = modulo();
    assert(mod != 0.0);
    double x = this->x / mod;
    double y = this->y / mod;
    setXY(x,y);
}

double Vector2D::distancia(const Vector2D &v) const{
    double x = this->x - v.getX();
    double y = this->y - v.getY();
    return std::sqrt(x * x + y * y);
}

std::string Vector2D::toString() const{
    std::ostringstream flujo;
    flujo << "(" << std::to_string(getX()) << "," << std::to_string(getY()) << ")";
    return flujo.str();
    //return "(" + std::to_string(getX()) + "," + std::to_string(getY()) + ")";
}

//Sobrecarga de operadores

Vector2D Vector2D::operator+(const Vector2D &v) const{
    double x = this->x + v.getX();
    double y = this->y + v.getY();
    Vector2D result(x,y);
    return result;
}

Vector2D Vector2D::operator*(double num) const{
    return Vector2D(x * num, y * num);
}

Vector2D operator*(double num, const Vector2D &v){
    return Vector2D(v.getX() * num, v.getY() * num);
}

bool Vector2D::operator==(const Vector2D &v) const{
    bool igualx = std::abs(this->x - v.getX()) < EPSILON;
    bool igualy = std::abs(this->y - v.getY()) < EPSILON;
    return igualx && igualy;
}

bool Vector2D::operator!=(const Vector2D &v) const{
    return !((*this) == v);
}

Vector2D Vector2D::operator-(const Vector2D &v) const{
    double x = this->x - v.getX();
    double y = this->y - v.getY();
    Vector2D result(x,y);
    return result;
}

std::ostream & operator<<(std::ostream & flujo, const Vector2D & v){
    flujo << v.toString();
    return flujo;
}

std::istream & operator>>(std::istream & flujo, Vector2D &p){
    double num1, num2;
    flujo >> num1 >> num2;
    p.setXY(num1,num2);
    return flujo;
}