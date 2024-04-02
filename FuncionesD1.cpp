#include <iostream>
#include "FuncionesD1.h"

using namespace std;

void crearCerradura(int*** &cerradura, int* tamanos, int cantidadEstructuras) {
    cerradura = new int**[cantidadEstructuras];
    for (int i = 0; i < cantidadEstructuras; ++i) {
        cerradura[i] = new int*[tamanos[i]];
        int contador = 1;
        for (int j = 0; j < tamanos[i]; ++j) {
            cerradura[i][j] = new int[tamanos[i]];
            for (int k = 0; k < tamanos[i]; ++k){
                if (j == tamanos[i]/2 && k == tamanos[i]/2){
                    cout << " ";
                }
                else {
                    cerradura[i][j][k] = contador++;
                }
            }
        }
    }
    // Imprimir la configuración de la cerradura
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

void rotarCerradura(int*** &cerradura, int* tamanos, int estructuraIndex, int direccion) {
    int size = tamanos[estructuraIndex];
    int** temp = new int*[size];

    // Rotar la matriz de la estructura seleccionada
    for (int i = 0; i < size; ++i) {
        temp[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            switch (direccion) {
            case 0:  // Rotar 90 grados a la derecha
                temp[i][j] = cerradura[estructuraIndex][size - 1 - j][i];
                break;
            case 1:  // Rotar 180 grados a la derecha
                temp[i][j] = cerradura[estructuraIndex][size - 1 - i][size - 1 - j];
                break;
            case 2:  // Rotar 270 grados a la derecha
                temp[i][j] = cerradura[estructuraIndex][j][size - 1 - i];
                break;
            default:
                break;
            }
        }
    }

    // Actualizar la matriz de la estructura con la rotación
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cerradura[estructuraIndex][i][j] = temp[i][j];
        }
    }

    // Liberar memoria
    for (int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;

    // Mensaje de confirmación
    cout << "La estructura " << estructuraIndex + 1 << " ha sido rotada " << (direccion + 1) * 90 << " grados." << endl;
}
