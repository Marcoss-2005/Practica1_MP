#include "Empresa.h"
#include <typeinfo>

Empresa::Empresa() : nmaxcli(100) {
    ncli = 0;
    ncon = 0;
    nmaxcon = 10;
    contratos = new Contrato*[nmaxcon];
}
Empresa::~Empresa(){
}

void Empresa::crearContrato() {
    char dni[10];
    bool falso=true;
    cout<<"digame su dni";
    cin>>dni;
    int pos=buscarCliente(dni);

    if(pos==-1){
        int d;
        int m;
        int a;
        char nombre[30];
        char apellidos[40];
        cout<<"Digame su nombre";
        cin>>nombre;
        cout<<"Digame sus apellidos";
        cin>>apellidos;
        cout<<"Digame su fecha";
        cout<<"Dia";
        cin>>d;
        cout<<"Mes";
        cin>>m;
        cout<<"Anio";
        cin>>a;
        Fecha fcl(d,m,a);
        Cliente *nuevoClinte=new Cliente(dni, nombre,apellidos,fcl);
        if(altaCliente(nuevoClinte)==-1){
            cout<<"No se pueden registrar mas clientes"<<endl;
            delete nuevoClinte;
            falso=false;
        }

    }
    if(falso){
        int tipo;
        cout << "Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
        cin >> tipo;

        int d, m, a;
        cout << "Fecha del contrato\n";
        cout << "dia: "; cin >> d;
        cout << "mes: "; cin >> m;
        cout << "anio: "; cin >> a;
        Fecha fContrato(d, m, a);

        Contrato *nuevoContrato = nullptr;

        if (tipo == 1) {
            int minutos;
            cout << "minutos hablados: ";
            cin >> minutos;
            nuevoContrato = new ContratoTP(dni, fContrato, minutos);
        }else if (tipo == 2) {
            int minutos;
            float precioMinuto;
            char nacionalidad[20];

            cout << "minutos hablados: ";
            cin >> minutos;
            cout << "Precio minuto: ";
            cin >> precioMinuto;
            cout << "Nacionalidad: ";
            cin >> nacionalidad;

            nuevoContrato = new ContratoMovil(dni, fContrato, precioMinuto, minutos, nacionalidad);
        } else {
            cout << "Tipo de contrato no válido.\n";
            falso=false;
        }
        if(falso){
            // 5. Control de redimensionamiento dinámico del array de contratos
            // Si el array actual se ha llenado (ncon == nmaxcon), duplicamos su capacidad (10, 20, 40, 80...)
            if (ncon == nmaxcon) {
                int nuevoMaxcon = nmaxcon * 2;
                Contrato **aux = new Contrato*[nuevoMaxcon];

                for (int i = 0; i < ncon; i++) {
                aux[i] = contratos[i]; // Copiamos los punteros antiguos
                }

                delete[] contratos; // Liberamos la memoria antigua
                contratos = aux;    // Actualizamos el puntero principal
                nmaxcon = nuevoMaxcon;
            }

    // 6. Añadimos el nuevo contrato al array y aumentamos el contador
            contratos[ncon] = nuevoContrato;
            ncon++;
        }
    }
}
bool Empresa::cancelarContrato(int idContrato){
    bool encontrado=false;
    int n=-1;
    for(int i=0; i<ncon;i++){
        if(!encontrado){
            if(contratos[i]->getIdContrato()==idContrato){
                n=i;
                encontrado=true;
            }
        }
    }
    if(n==-1){
        cout<<"No existe ese contrato amigo"<<endl;
    }else{
        delete contratos[n];
        // 4. Desplazamos los punteros restantes hacia la izquierda para rellenar el hueco
        for (int i = n; i < ncon - 1; i++) {
            contratos[i] = contratos[i + 1];
        }

        // 5. Decrementamos el número total de contratos
        ncon--;
    }
    return encontrado;
}
// Devuelve la posición del cliente en el array estático, o -1 si no existe
int Empresa::buscarCliente(const char dni[]) const {
    bool encontrado = false;
    int pos = -1;

    for (int i = 0; i < ncli; i++) {
        if (!encontrado) {
            // Añadimos .c_str() para convertir el string de getDni() a const char* de forma segura
            const char* d = clientes[i]->getDni().c_str();

            if (strcmp(dni, d) == 0) {
                encontrado = true;
                pos = i;
            }
        }
    }

    return pos; // Un único return al final, fuera del bucle
}
// Añade un cliente al array estático si hay hueco
int Empresa::altaCliente(Cliente *c) {
    if (ncli >= nmaxcli) {
        return -1; // Empresa llena (límite de 100 clientes)
    }
    clientes[ncli] = c;
    ncli++;
    return ncli - 1; // Devuelve la posición donde se ha insertado
}
bool Empresa::bajaCliente(const char dni[]) {
    // 1. Buscamos si el cliente existe
    int posCliente = buscarCliente(dni);
    if (posCliente == -1) {
        return false; // El cliente no existe
    }

    // 2. Eliminamos TODOS los contratos asociados a este DNI
    // Recorremos el array de contratos de atrás hacia adelante para evitar problemas al desplazar índices
    for (int i = ncon - 1; i >= 0; i--) {
        if (strcmp(contratos[i]->getDniContrato(), dni) == 0) {
            // Liberamos la memoria del contrato individual
            delete contratos[i];

            // Desplazamos los contratos restantes hacia la izquierda
            for (int j = i; j < ncon - 1; j++) {
                contratos[j] = contratos[j + 1];
            }
            ncon--; // Reducimos el contador de contratos
        }
    }

    // 3. Liberamos la memoria del cliente
    delete clientes[posCliente];

    // 4. Desplazamos los clientes restantes en el array estático hacia la izquierda
    for (int i = posCliente; i < ncli - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    ncli--; // Reducimos el contador de clientes

    return true;
}
int Empresa::nContratosTP() const {
    int contador = 0;
    for (int i = 0; i < ncon; i++) {
        // Comparamos el tipo real del objeto al que apunta el puntero con la clase ContratoTP
        if (typeid(*contratos[i]) == typeid(ContratoTP)) {
            contador++;
        }
    }
    return contador;
}
int Empresa::descuento(float porcentaje) const {
    int acumuladorModificados = 0;

    for (int i = 0; i < ncon; i++) {
        // Intentamos convertir el puntero de Contrato* a ContratoMovil*
        ContratoMovil *cm = dynamic_cast<ContratoMovil*>(contratos[i]);

        // Si el cast es exitoso (significa que el contrato es realmente un ContratoMovil)
        if (cm != nullptr) {
            float precioActual = cm->getPrecioMinuto();
            // Aplicamos el descuento al precio por minuto
            float nuevoPrecio = precioActual - (precioActual * (porcentaje / 100.0));
            cm->setPrecioMinuto(nuevoPrecio);

            acumuladorModificados++;
        }
    }
    return acumuladorModificados; // Devuelve a cuántos contratos se les ha aplicado
}
void Empresa::cargarDatos() {
    // 1. Creamos y damos de alta a 3 clientes iniciales
    Cliente *c1 = new Cliente("75547001M", "Juan Luis", "Sevilla", Fecha(29, 2, 2000));
    Cliente *c2 = new Cliente("75547555J", "Pepe", "Hernandez", Fecha(1, 3, 2008));
    Cliente *c3 = new Cliente("75547111J", "Maria", "Perez", Fecha(5, 5, 1995));

    altaCliente(c1);
    altaCliente(c2);
    altaCliente(c3);

    // 2. Creamos contratos y los añadimos al array dinámico de contratos
    // (Asegúrate de ir incrementando ncon y controlando si hace falta ampliar el array con la duplicación si superas los 10 iniciales)
    contratos[ncon++] = new ContratoTP("75547001M", Fecha(1, 1, 2015), 150);
    contratos[ncon++] = new ContratoMovil("75547001M", Fecha(2, 1, 2015), 0.15, 100, "ESPAÑOL");
    contratos[ncon++] = new ContratoTP("75547555J", Fecha(10, 2, 2015), 300);
    contratos[ncon++] = new ContratoMovil("75547555J", Fecha(12, 2, 2015), 0.12, 200, "EXTRANJERO");
    contratos[ncon++] = new ContratoTP("75547111J", Fecha(20, 3, 2015), 100);
    contratos[ncon++] = new ContratoMovil("75547111J", Fecha(22, 3, 2015), 0.18, 50, "ESPAÑOL");
    contratos[ncon++] = new ContratoTP("75547001M", Fecha(5, 4, 2015), 250);
}
void Empresa::ver() const {
    cout << "\n========================================" << endl;
    cout << "           ESTADO DE LA EMPRESA         " << endl;
    cout << "========================================" << endl;

    cout << "\n--- LISTA DE CLIENTES (" << ncli << ") ---" << endl;
    for (int i = 0; i < ncli; i++) {
        // Imprimimos los datos del cliente usando sus getters
        // (Ajusta los nombres de los métodos si en tu clase Cliente se llaman un poco diferente)
        cout << "DNI: " << clientes[i]->getDni()
             << " | Nombre: " << clientes[i]->getNombre()
             << " " << clientes[i]->getApellido() << endl;
    }

    cout << "\n--- LISTA DE CONTRATOS (" << ncon << ") ---" << endl;
    for (int i = 0; i < ncon; i++) {
        contratos[i]->ver(); // Polimorfismo: llama al ver() de ContratoTP o ContratoMovil
        cout << endl;
    }
    cout << "========================================\n" << endl;
}
