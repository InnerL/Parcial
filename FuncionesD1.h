#ifndef FUNCIONESD1_H
#define FUNCIONESD1_H

int*** crearCerradura(int* tamanos, int cantidadEstructuras);
int*** rotarCerradura(int*** &cerradura, int* tamanos, int estructuraIndex, int direccion);
void mostrarCerradura(int*** &cerradura, int* tamanos, int cantidadEstructuras);
int** cambiarTamanioEstructura(int**& estructura, int dimensionAnterior, int nuevaDimension);
int validarNumero();
int validarNumeroImpar();
void changeStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos);
void aggStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos);
void deletStructC3(int& cantidadEstructuras, int***& cerradura, int*& tamanos);
void compareStruct(int*& tamanos ,int***& cerradura, int& cantidadEstructuras, int columna, int fila);
void negative(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int j, int fila, int columna, bool esPosible, short int valor);
void equal(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int i, int fila, int columna, short int valor);
void positive(int*& tamanos, int***& cerradura, int& numero1, int& numero2, int i, int fila, int columna,bool& esPosible, short int valor);

#endif // FUNCIONESD1_H
