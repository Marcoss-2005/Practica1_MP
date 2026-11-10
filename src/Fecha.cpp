#include "Fecha.h"

//Constructor de la clase
Fecha::Fecha(int dia, int mes, int anio){
    setFecha(dia, mes, anio);
}

//Destructor
Fecha::~Fecha(){}

//Aqui vienen los getters
int Fecha::getDia() const {
    return this->dia;
}

int Fecha::getMes() const {
    return this->mes;
}

int Fecha::getAnio() const {
    return this->anio;
}

//Metodo para saber si un año es bisiesto
bool Fecha::bisiesto() const {
    //Formula para saber si un ao es bisiesto(cogida de internet)
    return (this->anio % 4 == 0 && this->anio % 100 != 0) || (this->anio % 400 == 0);
}

//metodo para saber los dias de los meses,corto y eficiente
int Fecha::diasEnMes(int m, int a) const {
    //tenemos 12 casos , 7 en los que pasa lo mismo y el mes tiene trenta y un dias y otros en los que tiene 30 y febrero tambien
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: {
            bool esBisiesto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
            if(esBisiesto){
                return 29;
            }else{
                return 28;
            }
        }
    }
}
//Metodo que le pasamos al constuctor, para crear una fecha
void Fecha::setFecha(int dia, int mes, int anio){
    this->anio = anio;

    if (mes >= 1 && mes <= 12) {
        this->mes = mes;
    } else {
        if(mes<1){
            this->mes=1;
        }else{
            this->mes=12;
        }
    }

    //llamamos a nuestra funcion auxiliar
    int maxDias = diasEnMes(this->mes, this->anio);
    if (dia >= 1 && dia <= maxDias) {
        this->dia = dia;
    } else {
        if(dia<1){
            this->dia=1;
        }else{
            this->dia=maxDias;
        }
    }
}
//esto para ver la fecha
void Fecha::ver() const {
    if (this->dia < 10) cout << "0";
    cout << this->dia << "/";
    if (this->mes < 10) cout << "0";
    cout << this->mes << "/" << this->anio;
}

//  incremento  (++f4)
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

//f4++
Fecha Fecha::operator++(int){
    //Primero guardamos el estado actual de nuestra fecha
    Fecha temp = *this;
    //Despues incrementamos el objeto usando el prefijo, llamamos a la funcion de arriba
    ++(*this);
    //Devolvemos la copia antigua
    return temp;
}

Fecha Fecha::operator+(int dias) const {
    //Lo mismo, guardamos en resultado el que teniamos
    Fecha resultado = *this;

    //hacemos un bucle para llamar al operador las veces que haga falta, mejor que hacer la cuenta de la vieja
    for(int i = 0; i < dias; ++i) {
        ++resultado;
    }
    return resultado;
}
//f1 =2+f2+3; operacion que actua como puente por si tiene que hacer operaciones como esa, para que no se raye
Fecha operator+(int dias, const Fecha& f) {
    return f + dias;
}
//Para mostrar por pantalla
ostream& operator<<(ostream& os, const Fecha& f){
    //Si es menor que 10 le metemos el 0 delante
    if (f.getDia() < 10) os << "0";
    os << f.getDia() << "/";
    if (f.getMes() < 10) os << "0";
    os << f.getMes() << "/" << f.getAnio();
    return os;
}
