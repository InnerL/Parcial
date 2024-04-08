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
                    cout << "  ";
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

bool validarCodigoCerradura(int*** cerradura, int* tamanos, int cantidadEstructuras) {
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

    cout << "Codigo de cerradura válido." << endl;
    return true;
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
