#include <cstdlib>
#include <iostream>
#include <iomanip> // std::setprecision
#include "Fecha.h" // definición de la clase Fecha
#include "Contrato.h" // definición de la clase Contrato
#include "ContratoTP.h" // definición de la clase ContratoTP
#include "ContratoMovil.h" // definición de la clase ContratoMovil

using namespace std;

int main(int argc, char *argv[]) {
    Fecha f1(29, 2, 2001), f2(f1), f3(29, 2, 2004);

    cout << "Fechas: ";
    f1.ver(); cout << ", "; f2.ver(); cout << ", "; f3.ver(); cout << endl;

    Contrato *p = new ContratoTP("75547111J", f1, 160); // O adaptado a tu constructor de contrato polimórfico
    ContratoTP ct1("17333256F", f1, 250); // habla 250 minutos
    ContratoTP ct2("12555100L", f3, 320); // habla 320 minutos
    ContratoMovil cm1("17333256F", f1, 0.12, 100, "ESPAÑOL"); // habla 100 minutos

    // --- CÓDIGO DE PRUEBA DEL PASO 1 AÑADIDO ---
    Contrato *t[4];
    t[0] = p;
    t[1] = &ct1; // (Asegúrate de apuntar a tus objetos creados)
    t[2] = &ct2;
    t[3] = &cm1;

    cout << "\n-- Datos de los contratos: -- \n";
    t[3]->setDniContrato("75547111J");

    for(int i = 0; i < 4; i++) {
        t[i]->setFechaContrato(t[i]->getFechaContrato() + 2);
        t[i]->ver();
        cout << endl;
    }
    // ---------------------------------------------

    system("PAUSE");
    return 0;
}
