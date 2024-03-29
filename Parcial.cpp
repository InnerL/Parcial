#include <iostream>

using namespace std;

void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == size / 2 && j == size / 2) {
                cout << "  "; // Deja un espacio vacío en el centro
            } else {
                cout << matrix[i][j] << " ";
            }
        }
            cout <<   endl;
    }
}

void rotateMatrix(int** matrix, int size) {
    // Creamos una matriz temporal para almacenar la matriz original
    int** temp = new int*[size];
    for (int i = 0; i < size; ++i) {
        temp[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            temp[i][j] = matrix[i][j];
        }
    }

    // Giramos los elementos de la matriz original usando la matriz temporal
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[j][size - 1 - i] = temp[i][j];
        }
    }

    // Liberamos la memoria de la matriz temporal
    for (int i = 0; i < size; ++i) {
        delete[] temp[i];
    }
    delete[] temp;
}
