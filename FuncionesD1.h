#ifndef FUNCIONESD1_H
#define FUNCIONESD1_H

int*** crearCerradura(int* tamanos, int cantidadEstructuras);
int*** rotarCerradura(int*** &cerradura, int* tamanos, int estructuraIndex, int direccion);
void mostrarCerradura(int*** &cerradura, int* tamanos, int cantidadEstructuras);
void cambiarTamanioEstructura(int**& estructura, int dimensionAnterior, int nuevaDimension);
bool validarCodigoCerradura(int*** cerradura, int* tamanos, int cantidadEstructuras);

#endif // FUNCIONESD1_H
