#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

struct Viaje
{
    string fecha;
    vector<string> miembros;
    string destino;
};

class VacacionesPilasYColas
{
private:
    int opcion;
    queue<string> miembros;
    queue<string> destinos;
    queue<Viaje> viajes;

public:
    VacacionesPilasYColas(){};

    void anadirMiembro()
    {
        string miembro;
        bool existe = false;

        cout << "Ingresa el nombre del miembro: " << endl;
        cin >> miembro;
        /*Se crea una cola temporal que es la misma que la cola miembros para no afectar la cola original.*/
        queue<string> temp = miembros;
        /*Verifica si el miembro ya existe.*/
        while (!temp.empty())
        {
            if (temp.front() == miembro)
            {
                existe = true;
                break;
            }
            temp.pop();
        }
        /*Si el miembro ya existe, muestra un mensaje de error y termina la función.*/
        if (existe)
        {
            cout << "El miembro ya existe. Intentalo de nuevo." << endl;
            return;
        }
        /*Si el miembro no existe, se añade a la cola de miembros y se muestra un mensaje para indicar que el miembro se añadio con éxito.*/
        miembros.push(miembro);
        cout << "Miembro agregado exitosamente." << endl;
    }

    void anadirDestino()
    {
        string destino;
        bool existe = false;

        cout << "Ingresa el destino: " << endl;
        cin >> destino;
        /*Se crea una cola temporal que es la misma que la cola destinos para no afectar la cola original.*/
        queue<string> temp = destinos;
        /*Verifica si el destino ya existe.*/
        while (!temp.empty())
        {
            if (temp.front() == destino)
            {
                existe = true;
                break;
            }
            temp.pop();
        }
        /*Si el destino ya existe, muestra un mensaje de error y termina la función.*/
        if (existe)
        {
            cout << "El destino ya existe. Inténtalo de nuevo." << endl;
            return;
        }
        /*Si el destino no existe, se añade a la cola de destinos y se muestra un mensaje para indicar que el destino se añadio con éxito.*/
        destinos.push(destino);
        cout << "Destino agregado exitosamente." << endl;
    }

    void planificarViaje()
    {
        Viaje viaje;
        int indiceDestino;
        int indiceMiembro;
        int sizeDestinos = destinos.size();
        int sizeMiembros = miembros.size();

        if (miembros.empty())
        {
            cout << "No hay miembros disponibles.\n";
            return;
        }

        cout << "Selecciona los miembros que participaran en el viaje (ingresa -1 cuando hayas terminado): " << endl;

        while (true)
        {
            queue<string> temp = miembros;
            vector<string> miembrosVector;
            int i = 0;

            while (!temp.empty())
            {
                cout << i << ": " << temp.front() << endl;
                miembrosVector.push_back(temp.front());
                temp.pop();
                i++;
            }
            cin >> indiceMiembro;

            if (indiceMiembro == -1)
            {
                break;
            }

            if (indiceMiembro < 0 or indiceMiembro >= sizeMiembros)
            {
                cout << "Indice invalido. Intentalo de nuevo.\n";
            }

            viaje.miembros.push_back(miembrosVector[indiceMiembro]);

            for (int i = 0; i < sizeMiembros; i++)
            {
                if (i != indiceMiembro)
                {
                    temp.push(miembrosVector[i]);
                }
            }
            miembros = temp;
        }

        if (destinos.empty())
        {
            cout << "No hay destinos disponibles.\n";
            return;
        }

        cout << "Selecciona el destino para el viaje: " << endl;

        queue<string> tempDestinos = destinos;
        vector<string> destinosVector;
        int i = 0;

        while (!tempDestinos.empty())
        {
            cout << i << ": " << tempDestinos.front() << endl;
            destinosVector.push_back(tempDestinos.front());
            tempDestinos.pop();
            i++;
        }
        cin >> indiceDestino;

        if (indiceDestino < 0 or indiceDestino >= sizeDestinos)
        {
            cout << "Indice invalido. Intentalo de nuevo.\n";
        }

        viaje.destino = destinosVector[indiceDestino];

        for (int i = 0; i < sizeDestinos; i++)
        {
            if (i != indiceDestino)
            {
                tempDestinos.push(destinosVector[i]);
            }
        }

        destinos = tempDestinos;

        cout << "Ingresa la fecha del viaje (dd/mm/aa): ";
        cin >> viaje.fecha;

        viajes.push(viaje);
    }

    void consultarViajes()
    {
        /*Verifica si hay viajes planeados. Si no hay se muestra un mensaje indicandolo, en caso de que haya se muetran por pantalla.*/
        if (viajes.empty())
        {
            cout << "No hay viajes planificados." << endl;
            return;
        }

        cout << "Viajes planificados: " << endl;
        /*Se crea una cola temporal que es la misma que la cola viajes para no afectar la cola original.*/
        queue<Viaje> temp = viajes;
        /*Recorre la cola temporal para imprimir los viajes que hay.*/
        while (!temp.empty())
        {
            Viaje v = temp.front();
            temp.pop();

            cout << "Fecha: " << v.fecha << "\n";
            cout << "Miembros: ";
            for (const auto &m : v.miembros)
            {
                cout << m << " ";
            }
            cout << "\nDestino: " << v.destino << "\n\n";
        }
    }

    void menu()
    {
        cout << "Bienvenido a nuestro sistema de Pilas y Colas!!\n";
        while (opcion != 5)
        {
            cout << "1. Agregar miembro.\n";
            cout << "2. Agregar destino.\n";
            cout << "3. Planificar viaje.\n";
            cout << "4. Consultar viajes.\n";
            cout << "5. Salir.\n";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                anadirMiembro();
                break;
            case 2:
                anadirDestino();
                break;
            case 3:
                planificarViaje();
                break;
            case 4:
                consultarViajes();
                break;
            case 5:
                cout << "Gracias por usar nuestro sistema!!\n";
                break;
            }
        }
    }
};