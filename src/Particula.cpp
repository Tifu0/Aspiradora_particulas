

#include "Particula.hpp"

//MÉTODOS PÚBLICOS

//constructores

Particula::Particula(int tipo){
    this->tipo = tipo;
    if(tipo != 0){
        radio = RADIO;
        posicion = Vector2D(0.0,0.0);
        velocidad = Vector2D(0.0,0.0);
        aceleracion = Vector2D(0.0,0.0);
    } else{
        radio = aleatorio(MIN_R, MAX_R);
        posicion = Vector2D(aleatorio(MIN_X,MAX_X),aleatorio(MIN_Y,MAX_Y));
        velocidad = Vector2D(aleatorio(-MAX_VEL,MAX_VEL),aleatorio(-MAX_VEL,MAX_VEL));
        aceleracion = Vector2D(aleatorio(-MAX_ACC,MAX_ACC),aleatorio(-MAX_ACC,MAX_ACC));
    }
}

Particula::Particula(Vector2D pos,Vector2D vel, Vector2D ac, double r, int t) : posicion(pos),velocidad(vel),aceleracion(ac),radio(r),tipo(t) {}

//getters y setters

Vector2D Particula::getPosicion() const { return posicion; }
Vector2D Particula::getVelocidad() const { return velocidad; }
Vector2D Particula::getAceleracion() const { return aceleracion; }
double Particula::getRadio() const { return radio; }
int Particula::getTipo() const { return tipo; }
void Particula::setPosicion(Vector2D posicion){ this->posicion = posicion; }
void Particula::setVelocidad(Vector2D velocidad){ this->velocidad = velocidad; }
void Particula::setAceleracion(Vector2D aceleracion){ this->aceleracion = aceleracion; }
void Particula::setRadio(double radio){ this->radio = radio; }

//Otras funcionalidades

void Particula::mover(){
    Vector2D res(velocidad + aceleracion);

    if(res.getX() >= MAX_VEL - EPSILON) res.setX(MAX_VEL);
    else if(res.getX() <= -MAX_VEL + EPSILON)  res.setX(-MAX_VEL);
    if(res.getY() >= MAX_VEL - EPSILON) res.setY(MAX_VEL);
    else if(res.getY() <= -MAX_VEL + EPSILON) res.setY(-MAX_VEL);

    setVelocidad(res);
    
    Vector2D res2(posicion + velocidad);

    if(res2.getX()+radio >= MAX_X - EPSILON) res2.setX( MAX_X - radio);
    else if(res2.getX() <= MIN_X+radio+EPSILON) res2.setX(MIN_X + radio);
    if(res2.getY()+radio >= MAX_Y- EPSILON) res2.setY(MAX_Y - radio);
    else if(res2.getY() <= MIN_Y+radio+ EPSILON) res2.setY(MIN_Y + radio);

    setPosicion(res2);
}

void Particula::rebotar(){
    if(posicion.getX() + radio >= MAX_X- EPSILON || posicion.getX() - radio<= MIN_X  +EPSILON){
        setVelocidad(Vector2D(velocidad.getX()*-1,velocidad.getY()));
        setAceleracion(Vector2D(aceleracion.getX()*-1, aceleracion.getY()));
    }
    if(posicion.getY() + radio>= MAX_Y- EPSILON || posicion.getY() - radio <= MIN_Y+ EPSILON){
        setVelocidad(Vector2D( velocidad.getX(),velocidad.getY()*-1));
        setAceleracion(Vector2D(aceleracion.getX(), aceleracion.getY()*-1));
    }
}

bool Particula::colision(const Particula &p) const{
    Vector2D resta(posicion - p.getPosicion());

    double dist = resta.getX()*resta.getX() + resta.getY()*resta.getY();
    double radios = radio + p.getRadio();
    
    return dist <= (radios * radios) + EPSILON;
}

void Particula::choque(Particula &p) {
    double vx = velocidad.getX();
    double vy = velocidad.getY();
    double v2x = p.velocidad.getX();
    double v2y = p.velocidad.getY();

    setVelocidad(Vector2D(v2x,v2y));
    p.setVelocidad(Vector2D(vx,vy));

    double ax = aceleracion.getX();
    double ay = aceleracion.getY();
    double a2x = p.getAceleracion().getX();
    double a2y = p.getAceleracion().getY();

    setAceleracion(Vector2D(a2x,a2y));
    p.setAceleracion(Vector2D(ax,ay));
}

std::string Particula::toString() const {
    std::ostringstream flujo;
    flujo << "{" << posicion << "," << velocidad << "," << aceleracion << "," << std::to_string(radio) << "," << std::to_string(tipo) << "}";
    return flujo.str();
    /*
    return 
    "{(" + std::to_string(posicion.getX()) + "," + std::to_string(posicion.getY()) + "),(" 
    + std::to_string(velocidad.getX()) + "," + std::to_string(velocidad.getY()) + "),(" 
    + std::to_string(getAceleracion().getX()) + "," + std::to_string(getAceleracion().getY()) + "),"
    + std::to_string(radio) + "," + std::to_string(getTipo()) + "}";
    */
}

void Particula::wrap() {
    Vector2D pos = getPosicion();
    double x = pos.getX();
    double y = pos.getY();

    if (x + radio > MAX_X - EPSILON) {
        double sobre = (x + radio) - MAX_X;
        x = MIN_X + sobre + radio;
    } else if (x - radio < MIN_X + EPSILON) { 
        double debajo = MIN_X - (x - radio);
        x = MAX_X - debajo - radio;
    }

    if (y + radio > MAX_Y- EPSILON) { 
        double sobre = (y + radio) - MAX_Y;
        y = MIN_Y + sobre + radio;
    } 
    else if (y - radio < MIN_Y+ EPSILON) { 
        double debajo = MIN_Y - (y - radio);
        y = MAX_Y - debajo - radio;
    }

    setPosicion(Vector2D(x, y));
}

//Sobrecarga de operadores

bool Particula::operator==(const Particula &p) const{
    return (*this).colision(p);
}

bool Particula::operator!=(const Particula &p) const{
    return !((*this) == p);
}

std::ostream& operator<<(std::ostream & flujo, const Particula & p){
    flujo << p.toString();
    return flujo;
}

std::istream& operator>>(std::istream & flujo, Particula & p){
    std::string s;
    double r;
    Vector2D v1, v2, v3;
    int t;
    flujo >> s >> v1 >> v2 >> v3 >> r >> t;
    Particula p2(t);
    p = p2;
    p.setPosicion(Vector2D(v1));
    p.setVelocidad(Vector2D(v2));
    p.setAceleracion(Vector2D(v3));
    p.setRadio(r);

    return flujo;
}