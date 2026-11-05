#include "Contrato.h"

int Contrato::contador=1;

Contrato::Contrato(const char dni[], Fecha f): idContrato(++contador), fechaContrato(f) {
    strcpy(this->dniContrato,dni);
  //this->fechaContrato=f; //ERROR es tipo no primitivo y debe ir en zona inicializadores
}
// Constructor de copia
Contrato::Contrato(const Contrato& c) : idContrato(c.idContrato), fechaContrato(c.fechaContrato) {
    strcpy(this->dniContrato, c.dniContrato);
}

Contrato::~Contrato() {
    //dtor
}

void Contrato::ver() const {
  cout << this->dniContrato << " (" << this->idContrato << " - ";
  this->fechaContrato.ver(); //llamo al ver del objeto fecha
  cout << ")";
}

ostream& operator<<(ostream &s, const Contrato &c) {
  s << c.getDniContrato() << " (" << c.getIdContrato() << " - " << c.getFechaContrato() << " )";
  return s;
}

//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...
