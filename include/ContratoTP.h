#ifndef CONTRATOTP_H
#define CONTRATOTP_H

#include <iostream> //cin, cout
#include "Fecha.h"
#include "Contrato.h"

using namespace std;

class ContratoTP: public Contrato {
  static int minutosTP;
  static float precioTP;
  int minutosHablados;
  static const float precioExcesoMinutos;

public:
  ContratoTP(char dni[], Fecha f, int m);
  //virtual ~ContratoTP(); //¿es necesario? pensar y reflexionad
  //ContratoTP(const ContratoTP& c);  //¿es necesario? pensar y reflexionad, claro que si, sin eso no puedes usar la copia
  //ContratoTP& operator=(const ContratoTP& c); //¿es necesario? pensar y reflexionad
  ContratoTP(const ContratoTP& c);
  static int getLimiteMinutos() { return ContratoTP::minutosTP; }
  static float getPrecio() { return ContratoTP::precioTP; }
  static void setTarifaPlana(int m, float p); //en el .cpp se pone la cabecera sin la palabra static
  int getMinutosHablados()const{return this->minutosHablados;}
  float factura()const;
  //para que sirva el polimorfismo, metemos el metodo ver como virtual
  virtual void ver()const;
  void setMinutosHablados(int minNuevos);

  // 1. Declarar el operador << como función amiga
  friend ostream& operator<<(ostream &s, const ContratoTP &c);
};

// 2. Implementar correctamente el operador <<
ostream& operator<<(ostream &s, const ContratoTP &c);

#endif // CONTRATOTP_H
