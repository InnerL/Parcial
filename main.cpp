#include <iostream>
#include "Parcial.h"

using namespace std;

int main() {
    int size = 3; // Tamaño inicial de la matriz

    while (size < 11) {
        int** matrix = new int*[size]; // Crear un array de punteros a int

        // Asignar memoria para cada fila de la matriz
        for (int i = 0; i < size; ++i) {
            matrix[i] = new int[size];
        }

        // Inicializar la matriz con números del 1 hasta el máximo
        int count = 1;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (i == size / 2 && j == size / 2) {
                    matrix[i][j] = 0; // Deja el centro vacío
                } else {
                    matrix[i][j] = count++;
                }
            }
        }

        // Imprimir la matriz
        cout << "Matriz de tamano " << size << "x" << size << ":" <<endl;
        printMatrix(matrix, size);

        rotateMatrix(matrix, size);

        // Imprimir la matriz rotada
        cout << "Matriz rotada:" <<endl;
        printMatrix(matrix, size);


        // Solicitar coordenadas al usuario
        int row, col;
        cout << "Ingrese la fila y columna (separadas por un espacio): ";
        cin >> row >> col;

        if (row >= 0 && row < size && col >= 0 && col < size) {
            int number = matrix[row][col];
            cout << "El numero en la coordenada (" << row << ", " << col << ") es: " << number <<  endl;
        } else {
            cout << "Coordenadas fuera de rango." <<  endl;
        }

        // Liberar memoria
        for (int i = 0; i < size; ++i) {
            delete[] matrix[i]; // Liberar memoria de cada fila
        }
        delete[] matrix; // Liberar memoria del array de punteros
        size += 2; // Aumentar el tamano de la matriz
        cout <<  endl;
    }

    return 0;
}
