#include "Fecha.h"
#include <iostream>

using namespace std;

// Constructor de la clase
Fecha::Fecha(const int &dia, const int &m, const int &anio){
    setFecha(dia, m, anio);
}

// Destructor (opcional)
//Fecha::~Fecha(){}

// Método para saber si un año es bisiesto,con formula usada
bool Fecha::bisiesto() const {
    return (this->anio % 4 == 0 && this->anio % 100 != 0) || (this->anio % 400 == 0);
}

//Metodo corto para los casos de los meses
int Fecha::diasEnMes(int m, int a) const {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: {
            //metemos este metodo en febrero por si es año bisiesto
            bool esBisiesto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
            return esBisiesto ? 29 : 28;
        }
        default: return 31;
    }
}

//Metodo para meter la fecha
void Fecha::setFecha(const int &dia, const int &mes, const int &a){
    this->anio = a;

    if (mes >= 1 && mes <= 12) {
        this->mes = mes;
    } else {
        if(mes < 1){
            this->mes = 1;
        } else {
            this->mes = 12;
        }
    }

    int maxDias = diasEnMes(this->mes, this->anio);
    if (dia >= 1 && dia <= maxDias) {
        this->dia = dia;
    } else {
        if(dia < 1){
            this->dia = 1;
        } else {
            this->dia = maxDias;
        }
    }
}

// Método para ver la fecha por pantalla
void Fecha::ver() const {
    if (this->dia < 10) cout << "0";
    cout << this->dia << "/";
    if (this->mes < 10) cout << "0";
    cout << this->mes << "/" << this->anio;
}

// Operador incremento
Fecha& Fecha::operator++(){
    this->dia++;
    int maxDias = diasEnMes(this->mes, this->anio);
    if (this->dia > maxDias) {
        this->dia = 1;
        this->mes++;
        if (this->mes > 12) {
            this->mes = 1;
            this->anio++;
        }
    }
    return *this;
}

// Operador incremento postfijo
Fecha Fecha::operator++(int i){
    Fecha temp = *this;
    ++(*this);
    return temp;
}

// Operador suma de días (f + 5)
Fecha Fecha::operator+(const int &i) const {
    Fecha resultado = *this;
    for(int count = 0; count < i; ++count) {
        ++resultado;
    }
    return resultado;
}

// Función amiga global para permitir (int + Fecha)
Fecha operator+(const int &i, const Fecha &f) {
    return f + i;
}

// Operador de flujo << para imprimir objetos Fecha directamente con cout
ostream& operator<<(ostream& os, const Fecha& f){
    if (f.getDia() < 10) os << "0";
    os << f.getDia() << "/";
    if (f.getMes() < 10) os << "0";
    os << f.getMes() << "/" << f.getAnio();
    return os;
}
