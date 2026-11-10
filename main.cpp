#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <typeinfo>
#include "Fecha.h"
#include "Cliente.h"
#include "Contrato.h"
#include "ContratoTP.h"
#include "ContratoMovil.h"
#include "Empresa.h"

using namespace std;

int main() {
    cout << setprecision(2) << fixed;
    cout << "==================================================\n";
    cout << "   TEST DE COMPROBACION DE TODOS LOS METODOS\n";
    cout << "==================================================\n\n";

    // ==========================================
    // 1. PRUEBAS DE LA CLASE FECHA
    // ==========================================
    cout << "--- 1. Probando clase Fecha ---" << endl;
    Fecha f1(29, 2, 2004); // Año bisiesto válido
    Fecha f2(31, 9, 2007); // Fecha inválida (mes con 30 días -> se ajusta a 30/09/2007)

    cout << "Fecha f1 (bisiesto): "; f1.ver(); cout << endl;
    cout << "Fecha f2 (ajustada): "; f2.ver(); cout << endl;
    cout << "Getters de f1 -> Dia: " << f1.getDia() << ", Mes: " << f1.getMes() << ", Anio: " << f1.getAnio() << endl;
    cout << "Es f1 bisiesto?: " << (f1.bisiesto() ? "SI" : "NO") << endl;
    cout << "Es f2 bisiesto?: " << (f2.bisiesto() ? "SI" : "NO") << endl;

    // Operadores de incremento y suma de fechas
    ++f1; // Avanza un dia
    cout << "f1 tras pre-incremento (++f1): "; f1.ver(); cout << endl;

    f1++; // Post-incremento
    cout << "f1 tras post-incremento (f1++): "; f1.ver(); cout << endl;

    Fecha f3 = f2 + 10; // Sumar 10 días
    cout << "f2 + 10 dias (f3): "; f3.ver(); cout << endl;

    Fecha f4 = 5 + f1; // Sumar entero por la izquierda (amiga)
    cout << "5 + f1 (f4): "; f4.ver(); cout << endl;
    cout << "Impresion con operator<< para Fecha: " << f1 << "\n\n";

    // ==========================================
    // 2. PRUEBAS DE LA CLASE CLIENTE
    // ==========================================
    cout << "--- 2. Probando clase Cliente ---" << endl;
    Cliente cli1("75547001Y", "Ana Maria", "Diaz", f1);
    cout << "Cliente 1 creado: " << cli1 << endl;

    // Probando Modificadores (Setters) y Consultores (Getters)
    cli1.setNombre("Ana Belen");
    cli1.setApellido("Perez Gomez");
    cli1.setDni("75547111X");
    cli1.setFecha(Fecha(15, 5, 2020));

    cout << "Cliente 1 modificado -> DNI: " << cli1.getDni()
         << ", Nombre: " << cli1.getNombre()
         << ", Apellido: " << cli1.getApellido()
         << ", Fecha: " << cli1.getFecha() << endl;

    Cliente cli2("75547999Z", "Juan", "Sin Miedo", Fecha(29, 2, 2000));
    cout << "Cliente 2: " << cli2 << endl;

    // Comprobación de operador de comparación (==) y asignación (=)
    if (cli1 == cli2)
        cout << "cli1 y cli2 son iguales.\n";
    else
        cout << "cli1 y cli2 NO son iguales.\n";

    cli2 = cli1; // Probando operador de asignación con memoria dinámica
    cout << "Tras la asignacion (cli2 = cli1), cli2 es: " << cli2 << "\n\n";

    // ==========================================
    // 3. PRUEBAS DE CONTRATOS (TP y Movil)
    // ==========================================
    cout << "--- 3. Probando Contratos (Tarifa Plana y Movil) ---" << endl;

    // Tarifa Plana por defecto
    cout << "Tarifa Plana general -> Limite: " << ContratoTP::getLimiteMinutos()
         << "m, Precio: " << ContratoTP::getPrecio() << " EUR" << endl;

    ContratoTP ctp1("17333256F", f1, 350); // Habla 350 min (supera el límite de 300)
    ContratoMovil cm1("17000000S", f2, 0.12, 180, "ESPAÑOL"); // 180 min a 0.12 EUR/min

    cout << "Contrato Tarifa Plana: " << ctp1 << endl;
    cout << "Factura Tarifa Plana (con exceso): " << ctp1.factura() << " EUR" << endl;

    cout << "Contrato Movil: " << cm1 << endl;
    cout << "Factura Contrato Movil: " << cm1.factura() << " EUR" << endl;

    // Modificación de atributos de contratos
    ctp1.setMinutosHablados(200);
    cm1.setPrecioMinuto(0.10);
    cm1.setNacionalidad("FRANCES");

    cout << "Tras modificar contratos:" << endl;
    cout << "  - TP modificada: " << ctp1 << endl;
    cout << "  - Movil modificado: " << cm1 << "\n\n";

    // Actualización de tarifa plana global para toda la compañía
    ContratoTP::setTarifaPlana(400, 15);
    cout << "Nueva Tarifa Plana global -> Limite: " << ContratoTP::getLimiteMinutos()
         << "m, Precio: " << ContratoTP::getPrecio() << " EUR\n\n";

    // ==========================================
    // 4. PRUEBAS DE LA CLASE EMPRESA
    // ==========================================
    cout << "--- 4. Probando clase Empresa (Polimorfismo, dynamic_cast y typeid) ---" << endl;
    Empresa Yoigo;

    // Cargar datos iniciales preconfigurados
    Yoigo.cargarDatos();
    Yoigo.ver();

    // Contar contratos de Tarifa Plana usando typeid
    cout << "Yoigo tiene " << Yoigo.nContratosTP() << " Contratos de Tarifa Plana.\n\n";

    // Cancelar un contrato existente
    bool cancelado = Yoigo.cancelarContrato(3);
    if (cancelado)
        cout << "El Contrato 3 ha sido cancelado exitosamente.\n";
    else
        cout << "El Contrato 3 no existe.\n";

    // Aplicar descuento porcentual a todos los contratos móviles usando dynamic_cast
    int modif = Yoigo.descuento(15.0f); // 15% de descuento
    cout << "Se ha aplicado descuento a " << modif << " Contratos Moviles.\n";

    // Dar de baja a un cliente y comprobar la eliminación en cascada de sus contratos
    bool baja = Yoigo.bajaCliente("75547001M");
    if (baja)
        cout << "El cliente 75547001M y sus contratos asociados han sido dados de baja.\n";
    else
        cout << "El cliente 75547001M no existe.\n";

    // Ver estado final de la empresa
    Yoigo.ver();

    cout << "==================================================\n";
    cout << "      TODAS LAS PRUEBAS FINALIZARON CON EXITO\n";
    cout << "==================================================\n";

    system("PAUSE");
    return 0;
}
