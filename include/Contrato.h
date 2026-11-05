#ifndef CONTRATO_H
#define CONTRATO_H

#include <iostream> //cin, cout
#include <cstring> //strlen, strcpy
#include "Fecha.h"

using namespace std;

class Contrato {
  static int contador;
  const int idContrato;
  char dniContrato[10];
  Fecha fechaContrato;
public:
  Contrato(const char dni[], Fecha f);
  virtual ~Contrato();
  Contrato(const Contrato& c); //¿es necesario? pensar y reflexionad claro que es necesario porque sin eso el constructor que haces abajo no lo estas declarando

//Contrato& operator=(const Contrato& c); //no es necesario y ademas no puede ser usado porque Contrato tiene un
                                          //atributo constante idContrato que no puede modificarse
                                          //no se puede usar el = en el main con objetos Contrato

  int getIdContrato() const { return this->idContrato; }
  const char* getDniContrato() const { return this->dniContrato; }
  Fecha getFechaContrato() const { return this->fechaContrato; }
  void setFechaContrato(Fecha f) { this->fechaContrato=f; }
  void setDniContrato(const char dni[]) { strcpy(this->dniContrato,dni); }
  void ver() const;
};

ostream& operator<<(ostream &s, const Contrato &c);

#endif // CONTRATO_H
