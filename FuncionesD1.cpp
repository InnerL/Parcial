#include <iostream>
#include "FuncionesD1.h"

using namespace std;



int*** crearCerradura(int* tamanos, int cantidadEstructuras) {
    int*** cerradura = new int**[cantidadEstructuras];
    for (int i = 0; i < cantidadEstructuras; ++i) {
        cerradura[i] = new int*[tamanos[i]];
        int contador = 1;
        for (int j = 0; j < tamanos[i]; ++j) {
            cerradura[i][j] = new int[tamanos[i]];
            for (int k = 0; k < tamanos[i]; ++k){
                if (j == tamanos[i]/2 && k == tamanos[i]/2){
                    cerradura[i][j][k] = 0;
                }
                else {
                    cerradura[i][j][k] = contador++;
                }
            }
        }
    }
    return cerradura;
}

int ***rotarCerradura(int*** &cerradura, int* tamanos, int estructuraIndex, int direccion) {
    int size = tamanos[estructuraIndex];
    int** temp = new int*[size];

    for (int i = 0; i < size; ++i) {
        temp[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            switch (direccion) {
            case 0:
                temp[i][j] = cerradura[estructuraIndex][size - 1 - j][i];
                break;
            case 1:
                temp[i][j] = cerradura[estructuraIndex][size - 1 - i][size - 1 - j];
                break;
            case 2:
                temp[i][j] = cerradura[estructuraIndex][j][size - 1 - i];
                break;
            default:
                break;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cerradura[estructuraIndex][i][j] = temp[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;

    return cerradura;
}

int** cambiarTamanioEstructura(int**& estructura, int dimensionAnterior, int nuevaDimension) {
    int** nuevaEstructura = new int*[nuevaDimension];
    for (int i = 0; i < nuevaDimension; ++i) {
        nuevaEstructura[i] = new int[nuevaDimension];
    }

    int contador = 1;
    for (int i = 0; i < nuevaDimension; ++i) {
        for (int j = 0; j < nuevaDimension; ++j) {
            if (i == nuevaDimension / 2 && j == nuevaDimension / 2) {
                cout << "   ";
            } else {
                nuevaEstructura[i][j] = contador++;
            }
        }
    }

    for (int i = 0; i < dimensionAnterior; ++i) {
        delete[] estructura[i];
    }
    delete[] estructura;

    estructura = nuevaEstructura;

    return estructura;
}

void mostrarCerradura(int*** &cerradura, int* tamanos, int cantidadEstructuras){
    cout << "Se creo la cerradura con las siguientes estructuras:" << endl;
    for (int i = 0; i < cantidadEstructuras; ++i) {
        cout << "Estructura " << i+1 << ":" << endl;
        for (int j = 0; j < tamanos[i]; ++j) {
            for (int k = 0; k < tamanos[i]; ++k) {
                if (j == tamanos[i]/2 && k == tamanos[i]/2){
                    cout << "   ";
                }
                else {
                    cout << cerradura[i][j][k] << " ";
                }
            }
            cout << endl;
        }
    }
}

void changeStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos){
    int indice;
    cout << "Ingrese el indice de la estructura que desea cambiar: ";
    cin >> indice;
    if (indice < 1 || indice > cantidadEstructuras) {
        cout << "Indice invalido.\n";
        return;
    }
    int nuevoTam;
    cout << "Ingrese el nuevo tamano para la estructura " << indice << ": ";
    cin >> nuevoTam;
    if (nuevoTam <= 0) {
        cout << "Tamano invalido.\n";
        return;
    }

    cerradura[indice - 1] = cambiarTamanioEstructura(cerradura[indice - 1], tamanos[indice - 1], nuevoTam);
    tamanos[indice - 1] = nuevoTam;

    cout << "Tamanio de la estructura " << indice << " actualizado.\n";
}

void aggStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos){
    int *nuevosTamanos;
    cantidadEstructuras++;
    nuevosTamanos = new int[cantidadEstructuras];
    for (int i = 0; i < cantidadEstructuras - 1; ++i) {
        nuevosTamanos[i] = tamanos[i];
    }
    cout << "Ingrese el tamano de la nueva estructura: ";
    cin >> nuevosTamanos[cantidadEstructuras - 1];
    delete[] tamanos;
    tamanos = nuevosTamanos;
    cerradura = crearCerradura(tamanos, cantidadEstructuras);
    cout << "Nueva estructura agregada.\n";
}

void deletStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos){
    if (cantidadEstructuras == 1) {
        cout << "No se puede eliminar la ultima estructura.\n";
        return;
    }
    int indiceEliminar;
    cout << "Ingrese el indice de la estructura que desea eliminar: ";
    cin >> indiceEliminar;
    if (indiceEliminar < 1 || indiceEliminar > cantidadEstructuras) {
        cout << "Indice invalido.\n";
        return;
    }
    for (int i = indiceEliminar - 1; i < cantidadEstructuras - 1; ++i) {
        tamanos[i] = tamanos[i + 1];
    }
    cantidadEstructuras--;
    cerradura = crearCerradura(tamanos, cantidadEstructuras);
    cout << "Estructura eliminada.\n";
}

void compareStruct(int*& tamanos ,int***& cerradura, int& cantidadEstructuras, int columna, int fila){
    int numero1, numero2;
    bool esPosible = true;
    for (int i = 0; i < cantidadEstructuras - 1; ++i) {
        short int valor;
        cout << "Ingrese el valor para la estructura " << i + 1 << " (-1 para menor, 1 para mayor, 0 para igual): ";
        cin >> valor;

        if (valor != -1 && valor != 1 && valor != 0) {
            cout << "Valor inválido." << endl;
            break;
        }
        switch (valor) {
        case -1:
        {
            negative(tamanos, cerradura, numero1, numero2, i, fila, columna, esPosible, valor);
            break;
        }

        case 0:
        {
            equal(tamanos, cerradura, numero1, numero2, i, fila, columna, valor);
            break;
        }
        case 1:
        {
            positive(tamanos, cerradura, numero1, numero2, i, fila, columna, esPosible, valor);
            break;
        }
        default:
        {
            cout << "valor invalido";
        }
        break;
        }

    }

    if (esPosible){
        mostrarCerradura(cerradura, tamanos, cantidadEstructuras);
    }
    else {
        cout << "Config invalida" << endl;
    }
}

void negative(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int i, int fila, int columna, bool esPosible, short int valor){
    int rotationCount = 0;
    while (true){
        numero1 = cerradura[i][fila][columna];
        numero2 = cerradura[i + 1][fila][columna];

        if (!esPosible) break;

        if (valor == -1 && numero1 < numero2) break;
        cerradura = rotarCerradura(cerradura, tamanos, i+1, 0);
        rotationCount++;

        if (rotationCount > 4) {
            cerradura[i+1] = cambiarTamanioEstructura(cerradura[i+1], tamanos[i+1], tamanos[i+1]+2);
            tamanos[i+1]+=2;
            rotationCount = 0;
        }
    }
}

void equal(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int i, int fila, int columna, short int valor){
    int rotationCount = 0;
    while (true){

        numero1 = cerradura[i][fila][columna];
        numero2 = cerradura[i + 1][fila][columna];

        if (valor == 0 && numero1 == numero2) break;
        cerradura = rotarCerradura(cerradura, tamanos, i+1, 0);
        rotationCount++;

        if (rotationCount > 4) {
            cerradura[i+1] = cambiarTamanioEstructura(cerradura[i+1], tamanos[i+1], tamanos[i]);
            tamanos[i+1]= tamanos[i];
            rotationCount = 0;
        }

    }
}

void positive(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int i, int fila, int columna,bool& esPosible, short int valor){
    int rotationCount = 0;;
    while (true){

        numero1 = cerradura[i][fila][columna];
        numero2 = cerradura[i + 1][fila][columna];

        if (valor == 1 && numero1 > numero2) break;
        cerradura = rotarCerradura(cerradura, tamanos, i+1, 0);
        rotationCount++;

        if (rotationCount > 4) {
            if ((tamanos[i+1]==3) || (tamanos[i+1]-2 <= columna)|| (tamanos[i+1]-2 <= fila)) {
                esPosible = false;
                break;
            }
            cerradura[i+1] = cambiarTamanioEstructura(cerradura[i+1], tamanos[i+1], tamanos[i+1]-2);
            tamanos[i+1]-=2;
            rotationCount = 0;
        }

    }
}
