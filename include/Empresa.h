#ifndef EMPRESA_H
#define EMPRESA_H

#include "Fecha.h"
#include "Cliente.h"
#include "Contrato.h"
#include "ContratoTP.h"
#include "ContratoMovil.h"

using namespace std;

class Empresa{
    Cliente *clientes[100];
    int ncli;
    const int nmaxcli;

    Contrato **contratos;
    int ncon;
    int nmaxcon;
protected:
    int buscarCliente(const char dni[]) const;
    int altaCliente(Cliente *c);
public:
    Empresa();
    virtual ~Empresa();
    void crearContrato();
    bool cancelarContrato(int idContrato);
    bool bajaCliente(const char dni[]);
    int descuento(float porcentaje)const;
    int nContratosTP()const;
    void cargarDatos();
    void ver()const;
    int contarContratosTPSuperioresA(int minutosMinimos) const;
    void actualizarPrecioMinutoMoviles(float nuevoPrecio);
    int eliminarContratosDeCliente(const char dniBuscado[]);

};
#endif
