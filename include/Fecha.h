#ifndef FECHA_H
#define FECHA_H

#include <iostream>

using namespace std;

class Fecha
{
    //En public declaramos los metodos que vamos a usar
    public:
        Fecha(int dia, int mes, int anio);
        virtual ~Fecha();
        bool bisiesto() const;
        int getDia() const;
        int getMes() const;
        int getAnio() const;
        void setFecha(int dia, int mes, int anio);
        void ver() const;

        //estos metodos son para operaciones como la que hacemos de 3+f2+2
        Fecha& operator++();
        Fecha operator++(int);
        Fecha operator+(int dias) const;

    protected:

    private:
        int dia;
        int mes;
        int anio;

        //metodo auziliar para poder saber el mes que nos dan y los dias que tiene para saber si esta permitido o no,
        //tambien lo podemos hacer a la cuenta de la vieja con if pero creo que es mas contundente como lo he hecho yo
        int diasEnMes(int m, int a) const;
};

Fecha operator+(int dias, const Fecha& f);

ostream& operator<<(ostream& os, const Fecha& f);

#endif // FECHA_H
