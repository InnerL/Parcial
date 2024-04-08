#include <iostream>
#include "menu.h"
#include "FuncionesD1.h"

using namespace std;
int* tamanos = nullptr;
int*** cerradura = nullptr;
int cantidadEstructuras = 0;

void menuPrin(int& seleccion){
    switch (seleccion) {
    case 1:
        case1(cantidadEstructuras, tamanos, cerradura);
        return;
    case 2:
        case2(cantidadEstructuras, cerradura, tamanos);
        return;
    case 3:
        case3(cantidadEstructuras, cerradura, tamanos);
        return;
    case 4:
        case4(cerradura, tamanos, cantidadEstructuras);
        return;

    case 5:
        case5(tamanos , cerradura, cantidadEstructuras);
        return;
    case 6:
        mostrarCerradura(cerradura, tamanos, cantidadEstructuras);
        return;
    default:
        return;
    }
}

void case1(int& cantidadEstructuras, int*& tamanos, int***& cerradura){
    cout << "Ingrese la cantidad de estructuras de la cerradura: ";
    cin >> cantidadEstructuras;

    tamanos = new int[cantidadEstructuras];
    cout << "Ingrese los tamanos de las estructuras separados por espacios: ";
    for (int i = 0; i < cantidadEstructuras; ++i) {
        cin >> tamanos[i];
    }
    cerradura = crearCerradura(tamanos, cantidadEstructuras);
}

void case2(int& cantidadEstructuras, int***& cerradura, int*& tamanos){
    int estructuraIndex;
    int direccion;

    cout << "Ingrese el indice de la estructura que desea rotar (de 1 a " << cantidadEstructuras << "): ";
    cin >> estructuraIndex;
    estructuraIndex--;

    if (estructuraIndex < 0 || estructuraIndex >= cantidadEstructuras) {
        cout << "Indice de estructura invalido." << endl;
        return;
    }
    cout << "Ingrese la direccion de rotacion (0: 90 grados a la derecha, 1: 180 grados a la derecha, 2: 270 grados a la derecha): ";
    cin >> direccion;

    if (direccion < 0 || direccion > 2) {
        cout << "Direccion de rotacion invalido." << endl;
        return;
    }
    cerradura = rotarCerradura (cerradura, tamanos, estructuraIndex, direccion);
}

void case3(int& cantidadEstructuras, int***& cerradura, int*& tamanos){
    int opcion;
    cout << "Que desea hacer?" << endl;
    cout << "1. Cambiar tamano de una estructura en la cerradura" << endl;
    cout << "2. Agregar una nueva estructura" << endl;
    cout << "3. Eliminar una estructura" << endl;
    cout << "Ingrese su opcion: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
        changeStructC3(cantidadEstructuras, cerradura, tamanos);
        break;
    case 2:
        aggStructC3(cantidadEstructuras, cerradura, tamanos);
        break;
    case 3:
        deletStructC3(cantidadEstructuras, cerradura, tamanos);

        break;
    default:
        cout << "Opcion invalida.\n";
        break;
    }
}

bool case4(int*** cerradura, int* tamanos, int cantidadEstructuras) {
    int columna, fila;
    cout << "Ingrese las coordenadas (columna y fila) para validar el codigo de cerradura: ";
    cin >> columna >> fila;
    columna--;
    fila--;

    if (columna < 0 || columna >= tamanos[0] || fila < 0 || fila >= tamanos[0]) {
        cout << "Coordenadas fuera de rango." << endl;
        return false;
    }

    for (int i = 0; i < cantidadEstructuras - 1; ++i) {
        int valor;
        cout << "Ingrese el valor para la estructura " << i + 1 << " (-1 para menor, 1 para mayor): ";
        cin >> valor;

        if (valor != -1 && valor != 1) {
            cout << "Valor invalido." << endl;
            return false;
        }

        int actual = cerradura[i][fila][columna];
        int siguiente = cerradura[i + 1][fila][columna];

        if (valor == -1 && siguiente >= actual) {
            cout << "Error en la secuencia de valores." << endl;
            return false;
        } else if (valor == 1 && siguiente <= actual) {
            cout << "Error en la secuencia de valores." << endl;
            return false;
        }
    }

    cout << "Codigo de cerradura valido." << endl;
    return true;
}

void case5(int*& tamanos ,int***& cerradura, int& cantidadEstructuras){
    {
        cout << "Creacion de cerradura a partir de la regla K" << endl;

        cout << "Ingrese la cantidad de matrices en la cerradura: ";
        cin >> cantidadEstructuras;

        int tamañoInicial = 3;

        tamanos = new int[cantidadEstructuras];
        for (int i = 0; i < cantidadEstructuras; ++i) {
            tamanos[i] = tamañoInicial;
        }
        cerradura = crearCerradura(tamanos, cantidadEstructuras);

        int columna, fila;
        cout << "Ingrese las coordenadas (columna y fila) para la primera matriz separadas por un espacio: ";
        cin >> columna >> fila;
        columna--;
        fila--;

        for (int i = 0; i < cantidadEstructuras; ++i) {
            while (columna >= tamanos[i] || fila >= tamanos[i]) {
                tamanos[i] += 2;
                cerradura = crearCerradura(tamanos, cantidadEstructuras);
            }
        }

        compareStruct(tamanos, cerradura, cantidadEstructuras, columna, fila);
    }
}
