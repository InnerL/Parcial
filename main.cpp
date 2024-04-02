#include <iostream>
#include "FuncionesD1.h"

using namespace std;

int main()
{
    int seleccion = 0;
    int *tamanos = nullptr;
    int*** cerradura = nullptr; // Agrega una variable para almacenar la cerradura
    int cantidadEstructuras = 0; // Inicializa la cantidad de estructuras

    while (seleccion != 6){
        cout << "| Bienvenido al sistema de lockers virtuales de la empresa informa2 |"<< endl;
        cout << " 1. Crear cerradura\n 2. Rotar partes cerradura\n 3. Cambiar configuracion cerradura\n 4. Validar codigo de cerradura\n 5. Crear cerradura a partir de codigo \n 6. Salir \n| Que desea hacer?: ";
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

            crearCerradura(cerradura, tamanos, cantidadEstructuras);
            break;

        case 2:
            // Rotar partes de la cerradura
            int estructuraIndex;
            cout << "Ingrese el indice de la estructura que desea rotar (de 0 a " << cantidadEstructuras - 1 << "): ";
            cin >> estructuraIndex;

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

            rotarCerradura(cerradura, tamanos, estructuraIndex, direccion);
            break;

        case 3:
            // Cambiar configuración de cerradura
            int opcion;
            cout << "¿Qué desea hacer?\n";
            cout << "1. Cambiar tamaño de una estructura en la cerradura\n";
            cout << "2. Añadir una nueva estructura\n";
            cout << "3. Eliminar una estructura\n";
            cout << "Ingrese su opción: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                int indice;
                cout << "Ingrese el índice de la estructura que desea cambiar: ";
                cin >> indice;
                if (indice < 1 || indice > cantidadEstructuras) {
                    cout << "Índice inválido.\n";
                    break;
                }
                int nuevoTam;
                cout << "Ingrese el nuevo tamaño para la estructura " << indice << ": ";
                cin >> nuevoTam;
                if (nuevoTam <= 0) {
                    cout << "Tamaño inválido.\n";
                    break;
                }
                tamanos[indice - 1] = nuevoTam;
                cout << "Tamaño de la estructura " << indice << " actualizado.\n";
                break;
            case 2:

                int *nuevosTamanos;
                // Agregar nueva estructura
                cantidadEstructuras++;
                nuevosTamanos = new int[cantidadEstructuras];
                for (int i = 0; i < cantidadEstructuras - 1; ++i) {
                    nuevosTamanos[i] = tamanos[i];
                }
                cout << "Ingrese el tamaño de la nueva estructura: ";
                cin >> nuevosTamanos[cantidadEstructuras - 1];
                delete[] tamanos;
                tamanos = nuevosTamanos;
                crearCerradura(cerradura, tamanos, cantidadEstructuras);
                cout << "Nueva estructura agregada.\n";
                break;
            case 3:
                // Eliminar estructura
                if (cantidadEstructuras == 1) {
                    cout << "No se puede eliminar la última estructura.\n";
                    break;
                }
                int indiceEliminar;
                cout << "Ingrese el índice de la estructura que desea eliminar: ";
                cin >> indiceEliminar;
                if (indiceEliminar < 1 || indiceEliminar > cantidadEstructuras) {
                    cout << "Índice inválido.\n";
                    break;
                }
                for (int i = indiceEliminar - 1; i < cantidadEstructuras - 1; ++i) {
                    tamanos[i] = tamanos[i + 1];
                }
                cantidadEstructuras--;
                crearCerradura(cerradura, tamanos, cantidadEstructuras);
                cout << "Estructura eliminada.\n";
                break;
            default:
                cout << "Opción inválida.\n";
                break;
            }
            break;

        case 4:

            break;

        case 5:

            break;

        default:
            break;
        }

    }

    // Liberar la memoria asignada
    delete[] tamanos;
    for (int i = 0; i < cantidadEstructuras; ++i) {
        for (int j = 0; j < tamanos[i]; ++j) {
            delete[] cerradura[i][j];
        }
        delete[] cerradura[i];
    }
    delete[] cerradura;

    return 0;
}
