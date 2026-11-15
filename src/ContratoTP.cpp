#include "ContratoTP.h"

int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;


//Constructor de la clase
ContratoTP::ContratoTP(char dni[], Fecha f, int m) : Contrato(dni, f) {
    this->minutosHablados = m;
}
//Construcyot copia
ContratoTP::ContratoTP(const ContratoTP& c):Contrato(c){
    this->minutosHablados=c.minutosHablados;
}
//para ver
void ContratoTP::ver() const {
  Contrato::ver();
  cout << " " << this->minutosHablados << "m, " << this->minutosTP<<"("<<this->ContratoTP::precioTP<<")";
}

//metodo para meter el dinero y los minutos a la variable declarada arrivba
void ContratoTP::setTarifaPlana(int m, float p) {
    ContratoTP::minutosTP = m;
    ContratoTP::precioTP = p;
}

float ContratoTP::factura() const {
    float total = 0;
    if (this->minutosHablados > ContratoTP::minutosTP) {
        // Cuota de la tarifa plana actual + el exceso de los minutos
        int minSobran = this->minutosHablados - ContratoTP::minutosTP;
        total = ContratoTP::precioTP + (minSobran * 0.15);
    } else {
        // Si no supera el límite, paga únicamente la cuota fija entera de la tarifa plana actual
        total = ContratoTP::precioTP;
    }
    return total;
}
void ContratoTP::setMinutosHablados(int minNuevos){
    this->minutosHablados=minNuevos;
}
ostream& operator<<(ostream &s, const ContratoTP &c) {
    s << static_cast<const Contrato&>(c); // Muestra los datos de la clase base
    s << " " << c.getMinutosHablados() << "m, " << ContratoTP::getLimiteMinutos() << "(" << ContratoTP::getPrecio() << ") - ";
    s << c.factura() << "€";
    return s;
}

