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
        //Declaramos los metodos y el constructor
        Cliente(char dni[10], char* nombre, string apellido, Fecha fecha);
        void setNombre(char* nombre);
        void setDni(char dni[10]);
        void setApellidos(string apellido);
        void setFecha(Fecha fecha);
        string getDni() const;
        char* getNombre() const;
        string getApellidos() const;
        Fecha getFecha() const;
        virtual ~Cliente();
        bool operator==(const Cliente& otro) const;
        Cliente& operator=(const Cliente& otro);
    protected:

    private:
        //Yo los voy a meter en privado aunque en la ayuda no salga asi, ya que si no no usamos el encapsulamiento que buscamos
        char dni[10];
        char* nombre;
        string apellido;
        Fecha fecha;
};

ostream& operator<<(ostream& os, const Cliente& cli);

#endif // CLIENTE_H
