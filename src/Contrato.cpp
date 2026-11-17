#include "Contrato.h"

//Contador estatico e inicio de los id
int Contrato::contador=1;

//Constructor de la clase
Contrato::Contrato(const char dni[], Fecha f): idContrato(++contador), fechaContrato(f) {//El idcontrato lo que hace es añadir uno porque el enunciado nos exige que cada id sea diferente, lo declaramos a 0 antes, y el fechaContato lo metemos ahi porque estamos llamando al constructor de otra clase
    strcpy(this->dniContrato,dni);
    Contrato::contador++;
    //this->fechaContrato=f; //ERROR es tipo no primitivo y debe ir en zona inicializadores
    //idContrato=contador; //ERROR es constante y debe ir en zona inicializadores

}
// Constructor de copia
Contrato::Contrato(const Contrato& c) : idContrato(++contador), fechaContrato(c.fechaContrato) {
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
float Contrato::factura() const {
    return 0; // Valor por defecto para la clase base genérica
}
/*
bool mismoDiaAlta(const Contrato &c,int diaBuscado){
    bool hecho=false;
    if(c.fechaContrato.getDia()==diaBuscado){
            hecho=true;
    }
    return hecho;
}
*/
