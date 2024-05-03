#include <iostream>
#include "SamuelConjuntosYMapas.cpp"
#include "SamuelPilasYColas.cpp"

using namespace std;

int main()
{
    int opcion;

    VacacionesPilasYColas pilas;
    VacacionesConjuntosYMapas conjuntos;

    cout << "Bienvenido a nuestro sistema planificador de vacaciones. Elige que sistema deseas usar:\n1. Conjuntos y Mapas.\n2. Pilas y Colas." << endl;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        conjuntos.menu();
        break;
    case 2:
        pilas.menu();
        break;
    default:
        cout << "Opción no válida." << endl;
        break;
    }

    return 0;
}