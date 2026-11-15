#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include <sstream> //stringstream
#include "Cliente.h"
//Metemos el constructor
Cliente::Cliente(char dni[10], char* nombre, string apellido, Fecha fecha)
    : fecha(fecha) // esto hace que se llame a fecha del tiron para meter la fecha recibida por parametros
{
    strcpy(this->dni, dni);
    //el strlen calcula los caracteres del nombre para declarar el tamaño del char y metemos el 1 por el caracter nulo
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
    this->apellido = apellido;
}

//en el destructor destruimos el nombre ya que es un puntero y no queremos que se nos quede apuntando ahi
Cliente::~Cliente() {
    delete[] this->nombre;
}

//setters y getters
void Cliente::setNombre(char* nombre){
    //al ser un puntero tenemos que tener cuidado con lo que habia dentro
    if (this->nombre != NULL) {
        delete[] this->nombre;
    }
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);
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

string Cliente::getApellidos() const{
    return this->apellido;
}

string Cliente::getDni() const{
    return this->dni;
}

//operador de comparacio,lo hacemos por el dni, recordamos que es una constante
bool Cliente::operator==(const Cliente& otro) const {
    return (strcmp(this->dni, otro.dni) == 0);
}

void Cliente::setApellidos(string apellido){
    this->apellido = apellido;
}

void Cliente::setFecha(Fecha fecha){
    this->fecha = fecha;
}
//Esto para mostrar los datos de los clientes
ostream& operator<<(ostream& os, const Cliente& cli) {
    os << cli.getNombre() << " " << cli.getApellidos() << " (" << cli.getDni() << " – " << cli.getFecha() << ")";
    return os;
}
// Operador de asignación
Cliente& Cliente::operator=(const Cliente& otro) {
    if (this != &otro) { // Evitar que se asignen solos
        delete[] this->nombre; // Liberar memoria antigua

        strcpy(this->dni, otro.dni);
        this->apellido = otro.apellido;
        this->fecha = otro.fecha;

        this->nombre = new char[strlen(otro.nombre) + 1];
        strcpy(this->nombre, otro.nombre);
    }
    return *this;
}
