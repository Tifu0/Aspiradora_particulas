

#include "ConjuntoParticulas.hpp"


//MÉTODOS AUXILIARES PRIVADOS

void ConjuntoParticulas::reservar(const int capacidad){
    assert(capacidad>=0);
    this->capacidad = capacidad;
    conjunto = new Particula[capacidad];
}

void ConjuntoParticulas::copiar(const ConjuntoParticulas &c){
    this->capacidad = c.capacidad;
    this->num_particulas = c.num_particulas;
    for(int i = 0; i < num_particulas; i++){
        conjunto[i] = c.conjunto[i];
    }
}

void ConjuntoParticulas::liberar(){
    if(conjunto != 0){
        delete [] conjunto;
    }
    conjunto = 0;
    num_particulas = 0;
    capacidad = 0;
}

void ConjuntoParticulas::redimension(bool aumentar){
    if(aumentar){
        int newcapacidad = capacidad + TAM_BLOQUE;
        int oldnum = num_particulas;
        Particula *aux = new Particula[newcapacidad];
        for(int i = 0; i < capacidad; i++){
            aux[i] = conjunto[i];
        }
        liberar();
        conjunto = aux;
        num_particulas = oldnum;
        capacidad = newcapacidad;
    } else{
        int newcapacidad = num_particulas;
        int oldnum = num_particulas;
        Particula* aux = new Particula[newcapacidad];
        for (int i = 0; i < num_particulas; i++) {
            aux[i] = conjunto[i];
        }
        liberar();
        conjunto = aux;
        num_particulas = oldnum;
        capacidad = newcapacidad;
    }
}

bool ConjuntoParticulas::contiene(const Particula &p) const{
    bool contenido = false;
    for(int i = 0;i < num_particulas;i++){
        if(conjunto[i] == p) contenido = true;
    }
    return contenido;
}

//MÉTODOS PÚBLICOS

//Constructor

ConjuntoParticulas::ConjuntoParticulas(int n){
    if(n > 0){
        reservar(n);
        for(int i = 0; i < n; i++){
            conjunto[i] = Particula();
        }
        num_particulas = n;
        capacidad = n;
    } else{
        conjunto = nullptr;
        num_particulas = 0;
        capacidad = 0;
    }
}

//Constructor de copia

ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas &c){
    reservar(c.capacidad);
    copiar(c);
}

//sobrecarga de asignacion

ConjuntoParticulas & ConjuntoParticulas::operator=(const ConjuntoParticulas &c){
    if(&c != this){
        liberar();
        reservar(c.capacidad);
        copiar(c);
    }
    return *this;
}

//destructor

ConjuntoParticulas::~ConjuntoParticulas(){
    liberar();
}

//getters y setters

int ConjuntoParticulas::size() const{ 
    return num_particulas; 
}

const Particula& ConjuntoParticulas::obtener(int n) const {
    assert(n >= 0 && n < num_particulas);
    return (*this)[n];
}

Particula& ConjuntoParticulas::obtener(int n){ 
    assert(n >= 0 && n < num_particulas);
    return (*this)[n]; 
}

//demas funcionalidades

void ConjuntoParticulas::agregar(const Particula &p){
    if(!(*this).contiene(p)){
        if(num_particulas + 1 > capacidad){
            redimension();
        }
        conjunto[num_particulas] = p;
        num_particulas++;
    }
}

void ConjuntoParticulas::borrar(int n){
    if(n >= 0 && n < num_particulas){
        conjunto[n] = conjunto[num_particulas-1];
        num_particulas--;
        if(capacidad - num_particulas > TAM_BLOQUE){
            redimension(false);
        } 
    }
}

void ConjuntoParticulas::reemplazar(int n,const Particula &p){
    assert(n >= 0 && n < num_particulas);
    conjunto[n] = p;
}

void ConjuntoParticulas::mover(int tipo_mov){
    if(tipo_mov == 0){
        for(int i = 0; i < num_particulas; i++){
            conjunto[i].mover();
        }
    } else if(tipo_mov == 1){
        for(int i = 0; i < num_particulas; i++){
            conjunto[i].mover();
            conjunto[i].rebotar();
        }
    } else if(tipo_mov == 2){
        for(int i = 0; i < num_particulas; i++){
            conjunto[i].mover();
            conjunto[i].wrap();
        }
    }
}


void ConjuntoParticulas::gestionarColisiones(){
    for(int i = 0;i < num_particulas; i++){
        for(int j = i+1; j < num_particulas;j++){
            if(conjunto[i].colision(conjunto[j])){
                conjunto[i].choque(conjunto[j]);
            }
        }
    }
}

std::string ConjuntoParticulas::toString() const {
    std::ostringstream flujo;
    flujo << capacidad << "," << num_particulas << "\n";
    for (int i = 0; i < num_particulas; i++) {
        flujo << conjunto[i].toString() << "\n";
    }
    return flujo.str();
}

//sobrecarga de operadores

ConjuntoParticulas ConjuntoParticulas::operator+(const ConjuntoParticulas &c) const{
    ConjuntoParticulas res(*this);

    for(int i = 0; i < c.size(); i++){
        Particula p = c.obtener(i);
        if(!res.contiene(p)) res.agregar(p);
    }
    
    return res;
}

ConjuntoParticulas & ConjuntoParticulas::operator+=(const ConjuntoParticulas &c){
    *this = (*this) + c;
    return *this;
}

ConjuntoParticulas & ConjuntoParticulas::operator+=(const Particula &p){
    (*this).agregar(p);
    return *this;
}

//Asumo que el usuario que usase esta clase podria intentar sumar
//una particula con un conjunto de ellas y esperar que un conjunto se retornase
ConjuntoParticulas & operator+=(const Particula &p, ConjuntoParticulas &c){
    c.agregar(p);
    return c;
}


ConjuntoParticulas & ConjuntoParticulas::operator-=(const int ind){
    (*this).borrar(ind);
    return *this;
}
//Aqui en cambio no tiene sentido quitarle a una int indice
//un conjunto y esperar que se retorne un conjunto
//por tanto en este caso no hare otro metodo externo indice -= conjunto

Particula & ConjuntoParticulas::operator[](const int ind){
    assert(ind>=0 && ind < num_particulas);
    return conjunto[ind];
}

const Particula & ConjuntoParticulas::operator[](const int ind) const{
    assert(ind>=0 && ind < num_particulas);
    return conjunto[ind];
}

std::ostream & operator<<(std::ostream & flujo, const ConjuntoParticulas & c){
    flujo << "Particulas: " << std::to_string(c.size()) << std::endl;
    for(int i = 0; i < c.size(); i++){
        flujo << "P" << i << " => " << c.obtener(i) << std::endl;
    }
    return flujo;
}

std::istream & operator>>(std::istream & flujo, ConjuntoParticulas & c){
    std::string s;
    Particula p;
    int num;
    flujo >> s >> num;
    ConjuntoParticulas c2(num);
    c = c2;
    for(int i = 0; i < num; i++){
        flujo >> p;
        c.reemplazar(i,p);
    }
    return flujo;
}