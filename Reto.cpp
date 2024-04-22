#include <iostream>
#include <map>
#include <set>
using namespace std;

class Vacaciones {

    private:
    
    set<string> destinos;
    map<string, map<string, map<string, string>>> miembros_familia;

    public:

    Vacaciones(){

    }

    void planificar_viaje(){

        string miembro;

        cout << "Ingrese el nombre del miembro de la familia: ";
        cin >> miembro;

        map <string, map<string, string>> itinerario;
        string destino, fecha;

        char opcion;

        do {

            cout << "Ingrese el destino de su viaje: " << endl;
            cin >> destino;

            if(destinos.find(destino) != destinos.end()){
                cout << "El destino ya fue agregado por otro miembro de la familia" << endl;
                continue;
            }

            cout << "Ingrese la fecha (YYYY-MM-DD): ";
            cin >> fecha;

            bool fecha_superpuesta = false;
            for (const auto& miembro_familia : miembros_familia){
                for (const auto& destino_itinerario : miembro_familia.second){
                    const auto& itinerario_fecha = destino_itinerario.second;

                    if (itinerario_fecha.find(destino) != itinerario_fecha.end() && itinerario_fecha.at(destino) == fecha){
                        fecha_superpuesta = true;
                        break;
                    }
                }
            }

            if (fecha_superpuesta){
                cout << "Ya hay un viaje planificado para esa fecha :(, ingresa otra fecha" << endl;
                continue;
            }

            
            itinerario[miembro][destino] = fecha;
            destinos.insert(destino);

            cout << "¿Desea agregar otro destino? (s/n): " << endl;
            cin >> opcion;

        } while (opcion == 's' || opcion == 'S');

        miembros_familia[miembro] = itinerario;

        cout << "Viaje planificado para " << miembro << endl;
    }

    void agregar_actividad(){

        string miembro, destino, actividad, hora;
        char opcion;

        cout << "Ingrese el nombre del miembro: " << endl;
        cin >> miembro;

        cout << "Ingrese el destino: " << endl;
        cin >> destino;

        if (miembros_familia.find(miembro) == miembros_familia.end() || miembros_familia[miembro].find(destino) == miembros_familia[miembro].end()){
            cout << "El miembro de la familia no tiene ningun viaje planificado, para ese destino. Planifique el viaje primero" << endl;
            return;
        }

        do {

            cout << "Ingrese la actividad que desea realizar: " << endl;
            cin >> actividad;

            cout << "Ingrese la hora: " << endl;
            cin >> hora;

            if (miembros_familia[miembro][destino].find(hora) != miembros_familia[miembro][destino].end()){
                cout << "Ya hay una actividad planificada para esa hora. Por favor, ingrese otra hora" << endl;
                continue;
            }

            miembros_familia[miembro][destino][hora] = actividad;
            cout << "Actividad agregada al itinerario de: " << miembro << " en " << destino << " para la hora " << hora << endl;

            cout << "¿Desea agregar otra actividad? (s/n): " << endl;
            cin >> opcion;
        
        } while (opcion == 's' || opcion == 'S');
    }

    void consultar_viajesxmiembro(){

        string miembro;

        cout << "Ingrese el nombre del miembro: " << endl;
        cin >> miembro;

        if (miembros_familia.find(miembro) != miembros_familia.end()){
            cout << "Viajes planificados para: " << miembro << endl;
            for (const auto& destino_itinerario : miembros_familia[miembro]){
                cout << "Destino: " << destino_itinerario.first << endl;

                for (const auto& hora_actividad : destino_itinerario.second){
                    cout << " - Hora: " << hora_actividad.first << ", Actividad: " << hora_actividad.second << endl;
                }
            }
        } else {
            cout << miembro << " no tiene viajes planificados" << endl;
        }
    }

    void encontrar_miembrosxdestino(){

        string destino;

        cout << "Ingrese el destino a buscar: " << endl;
        cin >> destino;

        cout << "Los siguientes miembros tienen planificado visitar " << destino << ": " << endl;
        for (const auto& miembro_familia : miembros_familia){
            for (const auto& destino_itinerario : miembro_familia.second){
                if (destino_itinerario.first == destino){
                    cout << "- " << miembro_familia.first << endl;
                    break;
                }
            }
        }
    }

    void menu(){

        cout << "Bienvenido a la agencia de viajes" << endl;
        cout << "Elija la opcion que quiera realizar el dia de hoy" << endl;
        cout << "1.Planificar un viaje" << endl;
        cout << "2.Agregar actividad" << endl;
        cout << "3.Consultar viajes por miembro" << endl;
        cout << "4.Consultar miembros por destino" << endl;
        cout << "5.Salir" << endl;
        cout << "Ingrese su opcion: " << endl;
    }
};

int main(){

    Vacaciones viajes;
    int opcion;

    do {

        viajes.menu();
        cin >> opcion;

        switch(opcion) {
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
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opcion != 5); 

    return 0;

}