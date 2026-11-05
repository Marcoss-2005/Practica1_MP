#include "ContratoTP.h"

int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;


//static se pone en el .h (no se pone en el .cpp)
ContratoTP::ContratoTP(char dni[], Fecha f, int m) : Contrato(dni, f) {
    this->minutosHablados = m;
}
ContratoTP::ContratoTP(const ContratoTP& c):Contrato(c){
    this->minutosHablados=c.minutosHablados;
}
void ContratoTP::ver() const {
  Contrato::ver(); //IMPORTANTE: llamamos al ver que heredo de mi padre PARA QUE MUESTRE LO DEL PADRE
                   //... y a continuacion solo "me preocupo" de mostrar lo que es exclusivo del hijo
  cout << " " << this->minutosHablados << "m, " << this->minutosTP<<"("<<this->ContratoTP::precioTP<<")";
}


void ContratoTP::setTarifaPlana(int m, float p) {
    ContratoTP::minutosTP = m;
    ContratoTP::precioTP = p;
}

//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...
//int ContratoTP::NuevoidContrato(){

//}
float ContratoTP::factura() const {
    float total = 0;
    if (this->minutosHablados > ContratoTP::minutosTP) {
        // Cuota fija de la tarifa plana actual + el exceso de los minutos sobrantes (a 0.15€)
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
    // IMPORTANTE: Usa getLimiteMinutos() y getPrecio() para que reflejen el cambio a 350 y 12
    s << " " << c.getMinutosHablados() << "m, " << ContratoTP::getLimiteMinutos() << "(" << ContratoTP::getPrecio() << ") - ";
    s << c.factura() << "€";
    return s;
}

