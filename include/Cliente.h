#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
#include <cstring>
#include "Fecha.h"

using namespace std;

class Cliente
{
    public:
        Cliente(char dni[10], char* nombre, string apellido, Fecha fecha);
        void setNombre(char* nombre);
        void setDni(char dni[10]);
        void setApellido(string apellido);
        void setFecha(Fecha fecha);
        string getDni() const;
        char* getNombre() const;
        string getApellido() const;
        Fecha getFecha() const;
        virtual ~Cliente();
        bool operator==(const Cliente& otro) const;
    protected:

    private:
        char dni[10];
        char* nombre;
        string apellido;
        Fecha fecha;
};

ostream& operator<<(ostream& os, const Cliente& cli);

#endif // CLIENTE_H
