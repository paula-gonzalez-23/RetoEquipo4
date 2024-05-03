#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

class Vacaciones {

private:
    stack<string> destinos;
    queue<pair<string, pair<string, string>>> miembros_familia;

public:
    Vacaciones() {}

    void planificar_viaje() {
        string miembro, destino, fecha;

        cout << "Ingrese el nombre del miembro de la familia: ";
        cin >> miembro;

        pair<string, pair<string, string>> itinerario;

        char opcion;

        do {
            cout << "Ingrese el destino de su viaje: ";
            cin >> destino;

            if (!destinos.empty() && destinos.top() == destino) {
                cout << "El destino ya fue agregado por otro miembro de la familia" << endl;
                continue;
            }

            cout << "Ingrese la fecha (YYYY-MM-DD): ";
            cin >> fecha;

            bool fecha_superpuesta = false;
            queue<pair<string, pair<string, string>>> tmpQueue = miembros_familia;
            while (!tmpQueue.empty()) {
                auto front = tmpQueue.front();
                if (front.second.first == destino && front.second.second == fecha) {
                    fecha_superpuesta = true;
                    break;
                }
                tmpQueue.pop();
            }

            if (fecha_superpuesta) {
                cout << "Ya hay un viaje planificado para esa fecha :(, ingresa otra fecha" << endl;
                continue;
            }

            itinerario = make_pair(miembro, make_pair(destino, fecha));
            miembros_familia.push(itinerario);
            destinos.push(destino);

            cout << "¿Desea agregar otro destino? (s/n): ";
            cin >> opcion;

        } while (opcion == 's' || opcion == 'S');

        cout << "Viaje planificado para " << miembro << endl;
    }

    void agregar_actividad() {
        string miembro, destino, actividad, hora;
        char opcion;

        cout << "Ingrese el nombre del miembro: ";
        cin >> miembro;

        cout << "Ingrese el destino: ";
        cin >> destino;

        bool found = false;
        queue<pair<string, pair<string, string>>> tmpQueue = miembros_familia;
        while (!tmpQueue.empty()) {
            auto front = tmpQueue.front();
            if (front.first == miembro && front.second.first == destino) {
                found = true;
                break;
            }
            tmpQueue.pop();
        }

        if (!found) {
            cout << "El miembro de la familia no tiene ningún viaje planificado para ese destino. Planifique el viaje primero" << endl;
            return;
        }

        do {
            cout << "Ingrese la actividad que desea realizar: ";
            cin >> actividad;

            cout << "Ingrese la hora: ";
            cin >> hora;

            found = false;
            tmpQueue = miembros_familia;
            while (!tmpQueue.empty()) {
                auto front = tmpQueue.front();
                if (front.first == miembro && front.second.first == destino && front.second.second == hora) {
                    found = true;
                    break;
                }
                tmpQueue.pop();
            }

            if (found) {
                cout << "Ya hay una actividad planificada para esa hora. Por favor, ingrese otra hora" << endl;
                continue;
            }

            miembros_familia.push(make_pair(miembro, make_pair(destino, hora + ": " + actividad)));
            cout << "Actividad agregada al itinerario de: " << miembro << " en " << destino << " para la hora " << hora << endl;

            cout << "¿Desea agregar otra actividad? (s/n): ";
            cin >> opcion;

        } while (opcion == 's' || opcion == 'S');
    }

    void consultar_viajesxmiembro() {
        string miembro;
        cout << "Ingrese el nombre del miembro: ";
        cin >> miembro;

        bool found = false;
        queue<pair<string, pair<string, string>>> tmpQueue = miembros_familia;
        while (!tmpQueue.empty()) {
            auto front = tmpQueue.front();
            if (front.first == miembro) {
                found = true;
                break;
            }
            tmpQueue.pop();
        }

        if (!found) {
            cout << miembro << " no tiene viajes planificados" << endl;
            return;
        }

        cout << "Viajes planificados para: " << miembro << endl;
        tmpQueue = miembros_familia;
        while (!tmpQueue.empty()) {
            auto front = tmpQueue.front();
            if (front.first == miembro) {
                cout << "Destino: " << front.second.first << ", Hora: " << front.second.second << endl;
            }
            tmpQueue.pop();
        }
    }

    void encontrar_miembrosxdestino() {
        string destino;
        cout << "Ingrese el destino a buscar: ";
        cin >> destino;

        bool found = false;
        queue<pair<string, pair<string, string>>> tmpQueue = miembros_familia;
        cout << "Los siguientes miembros tienen planificado visitar " << destino << ": " << endl;
        while (!tmpQueue.empty()) {
            auto front = tmpQueue.front();
            if (front.second.first == destino) {
                cout << "- " << front.first << endl;
            }
            tmpQueue.pop();
        }
    }

    void menu() {
        cout << "Bienvenido a la agencia de viajes" << endl;
        cout << "Elija la opción que quiera realizar el día de hoy" << endl;
        cout << "1. Planificar un viaje" << endl;
        cout << "2. Agregar actividad" << endl;
        cout << "3. Consultar viajes por miembro" << endl;
        cout << "4. Consultar miembros por destino" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opción: ";
    }
};

int main() {
    Vacaciones viajes;
    int opcion;

    do {
        viajes.menu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                viajes.planificar_viaje();
                break;

            case 2:
                viajes.agregar_actividad();
                break;

            case 3:
                viajes.consultar_viajesxmiembro();
                break;

            case 4:
                viajes.encontrar_miembrosxdestino();
                break;

            case 5:
                cout << "Gracias por usar nuestro sistema" << endl;
                break;

            default:
                cout << "Opción no válida" << endl;
                break;
        }

    } while (opcion != 5);

    return 0;
}
