#include <iostream>
#include <cstdlib>
#include <iomanip> // std::setprecision
#include "Fecha.h"
#include "Cliente.h"
#include "Contrato.h"
#include "ContratoTP.h"
#include "ContratoMovil.h"
#include "Empresa.h"

using namespace std;

int main(int argc, char *argv[]) {
    bool ok;
    Empresa Yoigo;

    cout << setprecision(2) << fixed; // A partir de aquí los float se muestran con 2 decimales
    cout << endl << "APLICACION DE GESTION TELEFONICA\n" << endl;

    Yoigo.cargarDatos(); // Carga los clientes y contratos iniciales de prueba
    Yoigo.ver();         // Muestra el estado inicial de la empresa
    cout << "Yoigo tiene " << Yoigo.nContratosTP() << " Contratos de Tarifa Plana\n\n";

    Yoigo.crearContrato(); // Prueba a crear un contrato (pedirá datos por pantalla)
    Yoigo.crearContrato(); // Otro contrato más

    ok = Yoigo.cancelarContrato(28); // Este contrato no debería existir
    if (ok)
        cout << "Contrato 28 cancelado\n";
    else
        cout << "El Contrato 28 no existe\n";

    ok = Yoigo.cancelarContrato(4); // Contrato existente
    if (ok)
        cout << "El Contrato 4 ha sido cancelado\n";
    else
        cout << "El Contrato 4 no existe\n";

    ok = Yoigo.bajaCliente("75547001M"); // Baja de cliente y sus contratos asociados
    if (ok)
        cout << "El cliente 75547001M y sus Contratos han sido cancelados\n";
    else
        cout << "El cliente 75547001M no existe\n";

    Yoigo.ver(); // Muestra el estado tras las bajas y creaciones

    Yoigo.descuento(20); // Aplica un 20% de descuento a los Contratos Móviles
    cout << "\nTras rebajar un 20% la tarifa de los ContratosMovil...";
    Yoigo.ver();
    cout << "Yoigo tiene " << Yoigo.nContratosTP() << " Contratos de Tarifa Plana\n";

    system("PAUSE");
    return 0;
}
