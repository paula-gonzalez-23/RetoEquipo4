#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Vacaciones
{
private:
    int opcion;
    map<int, set<string>> miembros;
    map<int, set<string>> destinos;
    map<int, set<string>> fechas;
    map<string, pair<set<string>, set<string>>> viajes;
    /*
    La clave del mapa representa la fecha del viaje que el usuario ingrese.
    El pair contiene dos conjuntos; el primero son los miembros que participaran en el viaje y el segundo el destino del viaje.
    */

public:
    Vacaciones(){};

    void anadirMiembro()
    {
        string miembro;

        cout << "Ingresa el nombre del miembro: ";
        cin >> miembro;
        /*Recorre el mapa de miembros.*/
        for (const auto &m : miembros)
        {
            if (m.second.find(miembro) != m.second.end())
            {
                /*Si el miembro ya existe, muestra el mensaje por pantalla.*/
                cout << "El miembro ya existe.\n";
                return;
            }
        }
        /*Si no existe lo añade al mapa de miembros, siendo la clave el tamaño del mapa y el dato el miembro.*/
        int clave = miembros.size();
        miembros[clave].insert(miembro);
    }

    void anadirDestino()
    {
        string destino;

        cout << "Ingresa el destino: ";
        cin >> destino;
        /*Recorre el mapa de destinos.*/
        for (const auto &m : destinos)
        {
            if (m.second.find(destino) != m.second.end())
            {
                /*Si el destino ya existe, muestra el mensaje por pantalla.*/
                cout << "El destino ya existe.\n";
                return;
            }
        }
        /*Si no existe lo añade al mapa de destinos, siendo la clave el tamaño del mapa y el dato el destino.*/
        int clave = destinos.size();
        destinos[clave].insert(destino);
    }

    void planificarViaje()
    {
        string fecha;
        int destinoClave;
        int miembroClave;
        set<string> miembrosSeleccionados;

        cout << "Selecciona los miembros que participaran en el viaje (ingresa -1 cuando hayas terminado): " << endl;

        /*Recorre el mapa de miembros y muestra las opciones*/
        for (auto it = miembros.begin(); it != miembros.end(); ++it)
        {
            cout << it->first << ": ";
            for (const auto &m : it->second)
            {
                cout << m << " ";
            }
            cout << endl;
        }

        /*Recibe la entrada del usuario para las claves de los miembros hasta que se ingrese -1*/
        while (true)
        {
            cin >> miembroClave;
            if (miembroClave == -1)
                break;

            /*Verifica si el miembro seleccionado ya tiene un viaje planeado en la misma fecha*/
            for (const auto &v : viajes)
            {
                /*
                Este condicional comprueba si la fecha del viaje actual (v.first) es igual a la fecha ingresada por el usuario
                y si el miembro seleccionado (miembros[miembroClave]) ya está en el conjunto de miembros del viaje actual (v.second.first),
                si es asi muestra un mensaje por pantalla y retorna.
                */
                if (v.first == fecha and v.second.first.find(*miembros[miembroClave].begin()) != v.second.first.end())
                {
                    cout << "El miembro ya tiene un viaje planeado en esta fecha.\n";
                    return;
                }
            }

            /*Agrega el miembro seleccionado al conjunto de miembros seleccionados.*/
            miembrosSeleccionados.insert(miembros[miembroClave].begin(), miembros[miembroClave].end());
        }

        /*Solicita al usuario que seleccione un destino para el viaje*/
        cout << "Selecciona un destino para el viaje: " << endl;

        /*Recorre el mapa de destinos y muestra las opciones*/
        for (auto it = destinos.begin(); it != destinos.end(); ++it)
        {
            cout << it->first << ": ";
            for (const auto &d : it->second)
            {
                cout << d << " ";
            }
            cout << endl;
        }

        cin >> destinoClave;

        /*Verifica si el destino seleccionado ya ha sido asignado a algún otro viaje*/
        for (const auto &v : viajes)
        {
            /*Comprueba si el destino del viaje actual (v.second.second) 
            es igual al destino seleccionado por el usuario (destinos[destinoClave])*/
            if (v.second.second == destinos[destinoClave])
            {
                cout << "El destino no puede ser el mismo que el de otro miembro.\n";
                return;
            }
        }

        /*Solicita al usuario que ingrese la fecha del viaje*/
        cout << "Ingresa la fecha del viaje (dd/mm/aa): ";
        cin >> fecha;

        /*Asigna el par de miembros seleccionados y destino al mapa de viajes con la fecha como clave*/
        viajes[fecha] = make_pair(miembrosSeleccionados, destinos[destinoClave]);
    }

    void consultarViajes()
    {
        /*Verifica si el mapa de viajes esta vacio y muestra un mensaje si es asi.*/
        if (viajes.empty())
        {
            cout << "No hay viajes planificados.\n";
            return;
        }
        /*Muestra la fecha, los miemrbos y el destino del viaje recorriendo el mapa de viajes.*/
        cout << "Viajes planificados: \n";
        for (const auto &v : viajes)
        {
            cout << "Fecha: " << v.first << "\n";
            cout << "Miembros: ";
            for (const auto &m : v.second.first)
            {
                cout << m << " ";
            }
            cout << "\nDestino: ";
            for (const auto &d : v.second.second)
            {
                cout << d << " ";
            }
            cout << "\n\n";
        }
    }

    void menu()
    {
        cout << "Bienvenido a nuestro sistema de planificacion de Vacaciones en Familia!!\n";
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

int main()
{
    Vacaciones vacaciones;

    vacaciones.menu();

    return 0;
}