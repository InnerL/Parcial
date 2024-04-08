#include <iostream>
#include "menu.h"

using namespace std;

int main()
{
    int seleccion = 0; 

    while (seleccion != 7){
        cout <<endl<< "| Bienvenido al sistema de lockers virtuales de la empresa informa2 |"<< endl;
        cout << " 1. Crear cerradura\n 2. Rotar partes cerradura\n 3. Cambiar configuracion cerradura\n 4. Validar codigo de cerradura\n 5. Crear cerradura a partir de codigo \n 6. Mostrar cerradura\n 7. Salir \n| Que desea hacer?: ";
        cin >> seleccion;
        menuPrin(seleccion);
    }
    return 0;
}
