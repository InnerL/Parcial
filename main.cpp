#include <iostream>
#include "FuncionesD1.h"

using namespace std;

int main()
{
    int seleccion = 0;
    int* tamanos = nullptr;
    int*** cerradura = nullptr;
    int cantidadEstructuras = 0;

    while (seleccion != 7){
        cout << "| Bienvenido al sistema de lockers virtuales de la empresa informa2 |"<< endl;
        cout << " 1. Crear cerradura\n 2. Rotar partes cerradura\n 3. Cambiar configuracion cerradura\n 4. Validar codigo de cerradura\n 5. Crear cerradura a partir de codigo \n 6. Mostrar cerradura\n 7. Salir \n| Que desea hacer?: ";
        cin >> seleccion;

        switch (seleccion) {
        case 1:

            cout << "Ingrese la cantidad de estructuras de la cerradura: ";
            cin >> cantidadEstructuras;

            tamanos = new int[cantidadEstructuras];
            cout << "Ingrese los tamanos de las estructuras separados por espacios: ";
            for (int i = 0; i < cantidadEstructuras; ++i) {
                cin >> tamanos[i];
            }

            cerradura = crearCerradura(tamanos, cantidadEstructuras);
            break;

        case 2:
            int estructuraIndex;
            cout << "Ingrese el indice de la estructura que desea rotar (de 1 a " << cantidadEstructuras << "): ";
            cin >> estructuraIndex;
            estructuraIndex--;

            if (estructuraIndex < 0 || estructuraIndex >= cantidadEstructuras) {
                cout << "Indice de estructura inválido." << endl;
                break;
            }

            int direccion;
            cout << "Ingrese la direccion de rotacion (0: 90 grados a la derecha, 1: 180 grados a la derecha, 2: 270 grados a la derecha): ";
            cin >> direccion;

            if (direccion < 0 || direccion > 2) {
                cout << "Direccion de rotacion inválida." << endl;
                break;
            }

            cerradura = rotarCerradura (cerradura, tamanos, estructuraIndex, direccion);
            break;

        case 3:
            int opcion;
            cout << "Que desea hacer?" << endl;
            cout << "1. Cambiar tamano de una estructura en la cerradura" << endl;
            cout << "2. Agregar una nueva estructura" << endl;
            cout << "3. Eliminar una estructura" << endl;
            cout << "Ingrese su opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                int indice;
                cout << "Ingrese el indice de la estructura que desea cambiar: ";
                cin >> indice;
                if (indice < 1 || indice > cantidadEstructuras) {
                    cout << "Indice invalido.\n";
                    break;
                }
                int nuevoTam;
                cout << "Ingrese el nuevo tamano para la estructura " << indice << ": ";
                cin >> nuevoTam;
                if (nuevoTam <= 0) {
                    cout << "Tamano invalido.\n";
                    break;
                }

                cerradura[indice - 1] = cambiarTamanioEstructura(cerradura[indice - 1], tamanos[indice - 1], nuevoTam);
                tamanos[indice - 1] = nuevoTam;

                cout << "Tamanio de la estructura " << indice << " actualizado.\n";
                break;
            case 2:

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
                break;
            case 3:
                if (cantidadEstructuras == 1) {
                    cout << "No se puede eliminar la ultima estructura.\n";
                    break;
                }
                int indiceEliminar;
                cout << "Ingrese el indice de la estructura que desea eliminar: ";
                cin >> indiceEliminar;
                if (indiceEliminar < 1 || indiceEliminar > cantidadEstructuras) {
                    cout << "Indice invalido.\n";
                    break;
                }
                for (int i = indiceEliminar - 1; i < cantidadEstructuras - 1; ++i) {
                    tamanos[i] = tamanos[i + 1];
                }
                cantidadEstructuras--;
                cerradura = crearCerradura(tamanos, cantidadEstructuras);
                cout << "Estructura eliminada.\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                break;
            }
            break;

        case 4:
            validarCodigoCerradura(cerradura, tamanos, cantidadEstructuras);
            break;

        case 5:
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
                while (columna >= tamanos[i] || fila >= tamanos[i] || cerradura[i][j][k] == 0) {
                    tamanos[i] += 2;
                    cerradura = crearCerradura(tamanos, cantidadEstructuras);
                }
            }

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
                int rotationCount = 0;




                switch (valor) {
                case -1:
                {
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
                    break;
                }

                case 0:
                {
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
                    break;
                }
                case 1:
                {
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
        break;



        case 6:

            mostrarCerradura(cerradura, tamanos, cantidadEstructuras);

            break;
        default:

            break;
        }

    }
    return 0;
}
