#include "Cliente.h"

Cliente::Cliente(char dni[10], char* nombre, string apellido, Fecha fecha)
    : fecha(fecha) // esto daba fallo
{
    strcpy(this->dni, dni);
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
    this->apellido = apellido;
}

Cliente::~Cliente() {
    delete[] this->nombre;
}

void Cliente::setNombre(char* nombre){
    this->nombre = nombre;
}

void Cliente::setDni(char dni[10]){
    strcpy(this->dni, dni);
}

Fecha Cliente::getFecha() const{
    return this->fecha;
}

char* Cliente::getNombre() const{
    return this->nombre;
}

string Cliente::getApellido() const{
    return this->apellido;
}

string Cliente::getDni() const{
    return this->dni;
}

bool Cliente::operator==(const Cliente& otro) const {
    return (this->getDni() == otro.getDni());
}

void Cliente::setApellido(string apellido){
    this->apellido = apellido;
}

void Cliente::setFecha(Fecha fecha){
    this->fecha = fecha;
}

ostream& operator<<(ostream& os, const Cliente& cli) {
    os << cli.getNombre() << " " << cli.getApellido() << " (" << cli.getDni() << "  " << cli.getFecha() << ")";
    return os;
}
