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

int ***rotarCerradura(int*** &cerradura, int* tamanos, int estructuraIndex, int direccion) {
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

    return cerradura;
}

void configurarCerradura(int*** cerradura, int* tamanos, int cantidadEstructuras) {

    // Mostrar las estructuras de la cerradura al usuario
    cout << "Estructuras de la cerradura configuradas:" << endl;
    for (int i = 0; i < cantidadEstructuras; ++i) {
        cout << "Estructura " << i + 1 << " (" << tamanos[i] << "x" << tamanos[i] << "):" << endl;
        mostrarCerradura(cerradura, tamanos, cantidadEstructuras);
    }

    // Permitir al usuario elegir qué matriz cambiar de tamaño
    int indiceMatriz;
    do {
        cout << "Ingrese el número de la estructura que desea modificar (1-" << cantidadEstructuras << "): ";
        cin >> indiceMatriz;
    } while (indiceMatriz < 1 || indiceMatriz > cantidadEstructuras);

    int nuevaDimension;
    cout << "Ingrese la nueva dimensión para la estructura " << indiceMatriz << ": ";
    cin >> nuevaDimension;

    // Cambiar el tamaño de la matriz seleccionada
    cambiarTamanioEstructura(cerradura[indiceMatriz - 1], tamanos[indiceMatriz - 1], nuevaDimension);
    tamanos[indiceMatriz - 1] = nuevaDimension;

    // Mostrar la estructura modificada al usuario
    cout << "Estructura " << indiceMatriz << " modificada (" << nuevaDimension << "x" << nuevaDimension << "):" << endl;
    mostrarCerradura(cerradura, tamanos, cantidadEstructuras);
}

// Función para cambiar el tamaño de una estructura en la cerradura
void cambiarTamanioEstructura(int**& estructura, int dimensionAnterior, int nuevaDimension) {
    // Crear una nueva estructura con la nueva dimensión
    int** nuevaEstructura = new int*[nuevaDimension];
    for (int i = 0; i < nuevaDimension; ++i) {
        nuevaEstructura[i] = new int[nuevaDimension];
    }

    // Copiar los elementos de la estructura original a la nueva estructura
    for (int i = 0; i < min(dimensionAnterior, nuevaDimension); ++i) {
        for (int j = 0; j < min(dimensionAnterior, nuevaDimension); ++j) {
            nuevaEstructura[i][j] = estructura[i][j];
        }
    }

    // Liberar la memoria de la estructura original
    for (int i = 0; i < dimensionAnterior; ++i) {
        delete[] estructura[i];
    }
    delete[] estructura;

    // Asignar la nueva estructura a la matriz original
    estructura = nuevaEstructura;
}

bool validarCodigoCerradura(int*** cerradura, int* tamanos, int cantidadEstructuras) {
    int columna, fila;
    cout << "Ingrese las coordenadas (columna y fila) para validar el código de cerradura: ";
    cin >> columna >> fila;
    columna--;
    fila--;

    // Verificar si las coordenadas son válidas
    if (columna < 0 || columna >= tamanos[0] || fila < 0 || fila >= tamanos[0]) {
        cout << "Coordenadas fuera de rango." << endl;
        return false;
    }

    // Verificar la secuencia de valores
    for (int i = 0; i < cantidadEstructuras - 1; ++i) {
        int valor;
        cout << "Ingrese el valor para la estructura " << i + 1 << " (-1 para menor, 1 para mayor): ";
        cin >> valor;

        // Verificar si el valor es -1 o 1
        if (valor != -1 && valor != 1) {
            cout << "Valor inválido." << endl;
            return false;
        }

        // Obtener el valor actual y el siguiente en la secuencia
        int actual = cerradura[i][fila][columna];
        int siguiente = cerradura[i + 1][fila][columna];

        // Verificar si la secuencia sigue el patrón esperado
        if (valor == -1 && siguiente >= actual) {
            cout << "Error en la secuencia de valores." << endl;
            return false;
        } else if (valor == 1 && siguiente <= actual) {
            cout << "Error en la secuencia de valores." << endl;
            return false;
        }
    }

    // Si la secuencia es correcta para todas las estructuras, retornar verdadero
    cout << "Código de cerradura válido." << endl;
    return true;
}
