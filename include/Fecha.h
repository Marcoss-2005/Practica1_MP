#ifndef FECHA_H
#define FECHA_H

#include <iostream> //cin, cout

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    // Método auxiliar que hemos metido para lo de el mes que es
    int diasEnMes(int m, int a) const;

public:
    // Constructores y Destructor
    Fecha(const int &dia, const int &m, const int &anio);
    // virtual ~Fecha(); //No hace falta
    //Getters
    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }

    void setFecha(const int &dia, const int &mes, const int &a);
    void ver() const;
    bool bisiesto() const;

    // Sobrecarga de operadores
    Fecha& operator++();                  // ++f
    Fecha operator++(int i);              // f++
    Fecha operator+(const int &i) const;  // f + 5

    // Función amiga
    friend Fecha operator+(const int &i, const Fecha &f);
};

// Funciones externas globales
Fecha operator+(const int &i, const Fecha &f);
ostream& operator<<(ostream& os, const Fecha& f);

#endif // FECHA_H




/*
1. mejorClienteContratoTP() constObjetivo: Encontrar al cliente que posee la mayor cantidad de contratos de tipo Tarifa Plana (ContratoTP) en la empresa.   Qué hace: Recorre los clientes y sus contratos utilizando dynamic_cast para filtrar los de tarifa plana, cuenta cuántos tiene cada usuario y muestra por pantalla su DNI junto con el número total de dichos contratos.
 2. mejorClienteDeLaEmpresaMejorTotalDeFacturas() constObjetivo: Identificar al cliente que genera mayor volumen de facturación global para la compañía.   Qué hace: Suma el importe de las facturas de todos los contratos asociados a cada cliente (ya sean ContratoTP o ContratoMovil, aprovechando el polimorfismo con el método virtual factura()), y muestra por pantalla el DNI del mejor cliente junto con la suma total de sus facturas.
 3. Constructor de Copia de Empresa (Empresa(const Empresa &e))Objetivo: Permitir la duplicación completa y segura (deep copy) de una empresa existente para poder instanciar otra nueva de forma limpia, por ejemplo: Empresa Vodafone(Yoigo);.   Qué hace: Reserva nueva memoria dinámica (new) y clona uno a uno tanto los punteros del array de clientes como el array polimórfico de contratos de la empresa origen, evitando que ambas empresas compartan las mismas direcciones de memoria y previniendo fallos de doble borrado en el destructor.
void Empresa::mejorClienteContratoTP() const
{
    if (ncli == 0 || ncon == 0) {
        std::cout << "No hay clientes o contratos registrados." << std::endl;
        return;
    }

    const char* dniMejor = nullptr;
    int maxContratosTP = -1;

    // Recorremos cada cliente de la empresa
    for (int i = 0; i < ncli; i++)
    {
        int contadorTP = 0;
        const char* dniActual = clientes[i]->getDni(); // Asumiendo getDni() o getDniCliente()

        // Contamos cuántos contratos TP tiene este cliente concreto
        for (int j = 0; j < ncon; j++)
        {
            // Comprobamos si el contrato es de tipo ContratoTP usando dynamic_cast
            ContratoTP *tp = dynamic_cast<ContratoTP*>(contratos[j]);
            if (tp != nullptr)
            {
                // Comparamos el DNI del contrato con el DNI del cliente actual
                if (strcmp(contratos[j]->getDniContrato(), dniActual) == 0)
                {
                    contadorTP++;
                }
            }
        }

        // Actualizamos si este cliente tiene el récord hasta el momento
        if (contadorTP > maxContratosTP)
        {
            maxContratosTP = contadorTP;
            dniMejor = dniActual;
        }
    }

    if (dniMejor != nullptr && maxContratosTP > 0)
    {
        // Buscamos los datos del cliente para imprimirlos ordenadamente si se desea,
        // o directamente el DNI y los contratos según la salida esperada.
        std::cout << dniMejor << " tiene " << maxContratosTP << " contratostP" << std::endl;
    }
}
void Empresa::mejorClienteDeLaEmpresaMejorTotalDeFacturas() const
{
    if (ncli == 0 || ncon == 0) {
        return;
    }

    const char* dniMejor = nullptr;
    float maxSumaFacturas = -1.0f;

    // Recorremos cada cliente
    for (int i = 0; i < ncli; i++)
    {
        float sumaCliente = 0.0f;
        const char* dniActual = clientes[i]->getDni();

        // Sumamos las facturas de todos los contratos asociados a este cliente
        for (int j = 0; j < ncon; j++)
        {
            if (strcmp(contratos[j]->getDniContrato(), dniActual) == 0)
            {
                // Gracias al polimorfismo y el método virtual factura(),
                // se calcula automáticamente sea TP o Móvil.
                sumaCliente += contratos[j]->factura();
            }
        }

        // Comparamos para encontrar el máximo sumatorio de facturas
        if (sumaCliente > maxSumaFacturas)
        {
            maxSumaFacturas = sumaCliente;
            dniMejor = dniActual;
        }
    }

    if (dniMejor != nullptr)
    {
        std::cout << dniMejor << " suma en facturas " << maxSumaFacturas << std::endl;
    }
}
Empresa::Empresa(const Empresa &e)
{
    // 1. Copiamos los contadores y capacidades de contratos
    this->ncon = e.ncon;
    this->nmaxcon = e.nmaxcon;

    // Reservamos memoria para el nuevo array dinámico de punteros a Contrato
    this->contratos = new Contrato*[this->nmaxcon];

    // Clonación profunda de cada contrato utilizando el constructor de copia (o polimorfismo)
    for (int i = 0; i < this->ncon; i++)
    {
        // O bien invocamos al typeid / dynamic_cast para clonar el subtipo exacto,
        // o si tus clases hijas tienen implementado un método clonar() / constructor de copia virtual.
        // La forma robusta típica con dynamic_cast en estas prácticas es:

        ContratoTP *tp = dynamic_cast<ContratoTP*>(e.contratos[i]);
        ContratoMovil *mov = dynamic_cast<ContratoMovil*>(e.contratos[i]);

        if (tp != nullptr) {
            this->contratos[i] = new ContratoTP(*tp); // Usa el constructor de copia de ContratoTP
        }
        else if (mov != nullptr) {
            this->contratos[i] = new ContratoMovil(*mov); // Usa el constructor de copia de ContratoMovil
        }
        else {
            // Caso genérico base por si hubiera más hijas
            this->contratos[i] = new Contrato(*e.contratos[i]);
        }
    }

    // 2. Copiamos los atributos de clientes (haciendo lo mismo de forma simétrica)
    this->ncli = e.ncli;
    this->nmaxcli = e.nmaxcli;
    this->clientes = new Cliente*[this->nmaxcli];

    for (int i = 0; i < this->ncli; i++)
    {
        this->clientes[i] = new Cliente(*e.clientes[i]); // Constructor de copia de Cliente
    }
}
*/
