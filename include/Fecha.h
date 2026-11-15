#ifndef FECHA_H
#define FECHA_H

#include <iostream> //cin, cout

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    // Método auxiliar que hemos metido para lo de el mes que es
    int diasEnMes(int m, int a) const;

public:
    // Constructores y Destructor
    Fecha(const int &dia, const int &m, const int &anio);
    // virtual ~Fecha(); //No hace falta
    //Getters
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }

    void setFecha(const int &dia, const int &mes, const int &a);
    void ver() const;
    bool bisiesto() const;

    // Sobrecarga de operadores
    Fecha& operator++();                  // ++f
    Fecha operator++(int i);              // f++
    Fecha operator+(const int &i) const;  // f + 5

    // Función amiga
    friend Fecha operator+(const int &i, const Fecha &f);
};

// Funciones externas globales
Fecha operator+(const int &i, const Fecha &f);
ostream& operator<<(ostream& os, const Fecha& f);

#endif // FECHA_H
