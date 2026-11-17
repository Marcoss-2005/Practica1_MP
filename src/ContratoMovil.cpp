#include <iostream>
#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include "Contrato.h"
#include "ContratoMovil.h"

//Constructor
ContratoMovil::ContratoMovil(char dni[], Fecha f, float p, int m, const char *nac): Contrato(dni, f) {
  this->precioMinuto=p;
  this->minutosHablados=m;
  //el strlen es para calcular la longuitud de la cadena nac que nos pasan por parametros, hay que sumarle uno para que funcione
  this->nacionalidad=new char [strlen(nac)+1];
  strcpy(this->nacionalidad, nac);
}

ContratoMovil::~ContratoMovil() {
//metodo para borrar la memoria sin ningun problema, ya que la nacionaldad es constante
    if (this->nacionalidad != nullptr) {
        delete[] this->nacionalidad;
        this->nacionalidad = nullptr;
    }
}

//ContratoMovil::ContratoMovil(const ContratoMovil& c):Contrato(c) { //IMPORTANTE: SI PONGO ESTA CABECERA y no implemento un constructor de copia en CONTRATO
                                                                     //NO DA ERROR AL COMPILAR PORQUE EL COMPILADOR GENERA UN CONSTRUCTOR COPIA POR SU CUENTA...
                                                                     //...EL PROBLEMA ES QUE EL QUE GENERA EL COMPILADOR NO INCREMENTA contador
                                                                     //Y ASIGNARIA EL MISMO CODIGO A AMBOS CONTRATOS
//Constructor de copia                                                                     //solucion: implementar constructor copia en CONTRATO y usar esta cabecera...
ContratoMovil::ContratoMovil(const ContratoMovil& c) : Contrato(c) { // Usando Contrato(c) aprovechas el constructor de copia de la clase base
  this->precioMinuto = c.precioMinuto;
  this->minutosHablados = c.minutosHablados;

  // Reserva memoria y copia profunda de la nacionalidad
  this->nacionalidad = new char[strlen(c.nacionalidad) + 1];
  strcpy(this->nacionalidad, c.nacionalidad);
}

//El const para garantizar que vamos solo a leer el objeto
void ContratoMovil::ver() const {
  Contrato::ver(); //IMPORTANTE: llamamos al ver que heredo de mi padre PARA QUE MUESTRE LO DEL PADRE
                   //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  cout << " " << this->minutosHablados << "m, " << this->nacionalidad << " " << this->precioMinuto;
}
//el precio total
float ContratoMovil::factura() const {
  return this->getMinutosHablados()*this->getPrecioMinuto();
}
//para modificar una constante, primero tenemos que liberarla
void ContratoMovil::setNacionalidad(const char* nac) {
    if (this->nacionalidad != nullptr) {
        delete[] this->nacionalidad;
    }

    this->nacionalidad = new char[strlen(nac) + 1];

    strcpy(this->nacionalidad, nac);
}



//usamos el operador para
ostream& operator<<(ostream &s, const ContratoMovil &c) {
  s << (Contrato &)c; //IMPORTANTE: convierto el objeto c (ContratoMovil &) a objeto Contrato &
                      // de esta forma se cree que es un objeto Contrato y muestra lo que indica el operator<< de Contrato
                      //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  s << " " << c.getMinutosHablados() << "m, " << c.getNacionalidad() << " " << c.getPrecioMinuto() << " - ";
  s << c.factura() << "€";
  return s;
}
/*
Aclaracion de virtual, const y static y amiga:

virtual: sirve para el polimorfismo(que tiene muchas formas, imagina que tienes la clase animal y dentro de ella puede ser gato perro...)
es para llamar al metodo correcto de la clase hija, si no lo ponemos puede llamar a la clase hija incorrecta
//AÑADIDO si no pones virtual, no es que llame a una clase hija incorrecta, sino que llama siempre al método de la clase padre

static: hace que una variable pertenezca a una clase y no a un objeto

const: significa que es constante

friend: es una funcion externa que permite acceder a los atributos privados de una clase, saltandose el emncapsulamiento por ejemplo la usamos en la fecha para poder acceder a dia mes y año sin tener que usar los metodos get

*/

/*
Conceptos de herencia, polimorfismo y encapsulamiento y abstraccion

Herencia: permite que una clase hija reciba y utilize metodos de la clase padre, como en la parte de contratos, esta contrato como padre y contratoTP y contratoMovil como hijas

Polimorfismo: como la funcion factura, Permite tratar a objetos de distintas clases hijas a través de un puntero o referencia de la clase padre
Ejemplo en tu práctica: Llamar a factura() desde un array de contratos generales y que C++ calcule automáticamente la factura de Tarifa Plana o de Móvil según corresponda.

Encapsulamiento: Consiste en proteger los datos internos de un objeto ocultándolos con private por ejemplo

Abstraccion:Es el proceso de aislar y representar solo las características esenciales de un objeto, ignorando los detalles complejos que no importan
La clase Contrato como clase abstracta. Define el concepto general de contrato
*/
/*
#include "ContratoMovilInternet.h"
#include <iostream>

using namespace std;

// Constructor: Llama primero al constructor del padre (ContratoMovil)
ContratoMovilInternet::ContratoMovilInternet(const char dni[], Fecha f, float precioMinuto, int minutosHablados, const char nacionalidad[], float megas, float precioMega)
    : ContratoMovil(dni, f, precioMinuto, minutosHablados, nacionalidad)
{
    this->megasContratados = megas;
    this->precioPorMega = precioMega;
}

ContratoMovilInternet::~ContratoMovilInternet() {
    // Destructor por defecto
}

// Método ver() polimórfico
void ContratoMovilInternet::ver() const {
    // Reutilizamos el ver del padre y añadimos la info de internet
    ContratoMovil::ver();
    cout << " | Datos: " << megasContratados << "MB, Precio/MB: " << precioPorMega << endl;
}

// Método factura() polimórfico que calcula llamadas + datos
float ContratoMovilInternet::factura() const {
    float facturaBase = ContratoMovil::factura(); // Calcula (minutos * precioMinuto)
    float facturaDatos = megasContratados * precioPorMega;

    return facturaBase + facturaDatos;
}
Ejemplo de destructor chetado
~Empresa() {
        // 1. Primero borramos cada contrato individualmente de la memoria
        for (int i = 0; i < ncon; i++) {
            delete contratos[i]; // Llama al destructor de cada Contrato (y de sus hijas gracias al 'virtual')
        }

        // 2. Después borramos el array de punteros principal
        delete[] contratos;

        // (Opcional por seguridad)
        contratos = nullptr;
        ncon = 0;
        nmaxcon = 0;
    }


    #ifndef CONTRATOMOVILINTERNET_H
#define CONTRATOMOVILINTERNET_H

#include "ContratoMovil.h"

class ContratoMovilInternet : public ContratoMovil {
private:
    float megasContratados; // en MB o GB
    float precioPorMega;    // coste adicional por datos

public:
    // Constructor parametrizado
    ContratoMovilInternet(const char dni[], Fecha f, float precioMinuto, int minutosHablados, const char nacionalidad[], float megas, float precioMega);

    // Destructor
    virtual ~ContratoMovilInternet();

    // Getters y Setters específicos
    float getMegasContratados() const { return megasContratados; }
    float getPrecioPorMega() const { return precioPorMega; }
    void setMegasContratados(float m) { megasContratados = m; }
    void setPrecioPorMega(float p) { precioPorMega = p; }

    // Redefinición de métodos virtuales (Polimorfismo)
    virtual void ver() const override;
    virtual float factura() const override;
};

#endif
*/
