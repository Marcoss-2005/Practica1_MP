#include <iostream>
#include <cstdlib>
#include <cstring> //strlen, strcpy
#include <iomanip> //std::setprecision
#include "Contrato.h"
#include "ContratoMovil.h"

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
                                                                     //solucion: implementar constructor copia en CONTRATO y usar esta cabecera...
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

