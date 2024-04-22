#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Esta estructura representa un destino de vacaciones
struct Destino{
    string nombre;
    int fecha[3]; // fecha[0] = año, fecha[1] = mes, fecha[2] = día
    vector<string> actividades;

    // Sobrecarga del operador < para poder usar Destino en un set
    bool operator<(const Destino& destination) const{
        return nombre < destination.nombre;
    }
};

// Función que retorna la cantidad de días en un mes
int diasMes(int mes, int anio){
    if(mes == 2){
        return 28;
    }
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        return 30;
    }
    return 31;
}

// Función que imprime el calendario de un mes y año específicos
void imprimirCalendario(int mes, int anio){
    cout<<"Mon Tue Wed Thu Fri Sat Sun"<<endl;
    int dias = diasMes(mes, anio);
    for(int i=1; i<=dias; i++){
        cout<<i<<"   ";
        if (i % 7 == 0) {
            cout<<endl;
        }
    }
    cout<<endl;
}

// Función que imprime un mensaje indicando que se agregó un destino
void imprimirAgregadoDestino(const string& familiar, const Destino& destino){
    cout<<"Se agregó el destino "<<destino.nombre<<" para "<<familiar<<" en "<<destino.fecha[2]<<"/"<<destino.fecha[1]<<"/"<<destino.fecha[0]<<"."<<endl;
}

// Función que imprime los destinos de un miembro de la familia
void imprimirDestinosFamiliar(const map<string, set<Destino>>& destinosFamilia, const string& familiar){
    if(destinosFamilia.find(familiar) != destinosFamilia.end()){
        cout<<"Destinos para "<<familiar<<": "<<endl;
        for(const auto& destino : destinosFamilia.at(familiar)){
            cout<<destino.nombre<<" en "<<destino.fecha[0]<<"-"<<destino.fecha[1]<<"-"<<destino.fecha[2]<<endl;
        }
    }else{
        cout<<"No hay destinos planificados para "<<familiar<<"."<<endl;
    }
}

// Función que imprime todos los destinos con sus respectivos miembros de la familia, fechas y actividades
void imprimirDestinos(const map<string, set<Destino>>& destinosFamilia){
    for (const auto& familiar : destinosFamilia){
        for(const auto& destino : familiar.second){
            cout<<"Miembro de la familia: "<<familiar.first<<endl;
            cout<<"Destino: "<<destino.nombre<<endl;
            cout<<"Fecha: "<<destino.fecha[0]<<"/"<<destino.fecha[1]<<"/"<<destino.fecha[2]<<endl;
            cout<<"Actividades: ";
            for(size_t i = 0; i < destino.actividades.size(); i++){
                cout << destino.actividades[i];
                if(i != destino.actividades.size() - 1){
                    cout<< ", ";
                }else{
                    cout<<".";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

// Función que verifica si un destino se superpone con otro destino
bool superposicionDestino(const set<Destino>& destinos, const Destino& nuevoDestino){
    for(const auto& destino : destinos){
        if(destino.nombre == nuevoDestino.nombre){
            return true;
        }
    }
    return false;
}

// Función que imprime los miembros de la familia que quieren ir a un destino específico
void familiaresDestino(const map<string, set<Destino>>& destinosFamilia, const string& destino){
    cout<<"Miembros de la familia que quieren ir a "<<destino<<":"<<endl;
    for(const auto& familiar : destinosFamilia){
        for(const auto& currentDestino : familiar.second){
            if(currentDestino.nombre == destino){
                cout<<familiar.first<<endl;
                break;
            }
        }
    }
}

// Función que verifica si una fecha ya fue usada
bool fechaUsada(const set<Destino>& destino, const int fecha[3]){
    for(const auto& destino : destino){
        if(destino.fecha[0] == fecha[0] && destino.fecha[1] == fecha[1] && destino.fecha[2] == fecha[2]){
            return true;
        }
    }
    return false;
}

// Función principal de ejecución
int main() {
    // Mapa que contiene los destinos de cada miembro de la familia
    map<string, set<Destino>> destinosFamilia;
    int eleccion;

    // Bucle de ejecución de opciones
    do {
        // Menú de opciones
        cout<<"Bienvenido al planificador de vacaciones. ¿Qué desea hacer?"<<endl;
        cout<<"1. Planificar un nuevo viaje.\n2. Consultar destinos de un miembro de la familia.\n3. Consultar miembros de la familia que quieren ir a un destino específico.\n4. Ver todos los destinos.\n5. Salir"<<endl;
        cout<<"Ingrese una opción: ";
            cin>>eleccion;
        cout<<"------------------------------------------"<<endl;

        //Condicional para cada opción
        switch(eleccion){
            case 1:{
                // Variables para la creación de un nuevo destino
                string familiar;
                Destino destino;
                int numActividades;

                // Ingreso de datos para el nuevo destino
                cout<<"Ingrese el nombre del miembro de la familia: ";
                    cin>>familiar;
                cout<<"Ingrese el nombre del destino: ";
                    cin>>destino.nombre;
                // Ingreso de la fecha del viaje con validaciones
                do{
                    do{
                        cout<<"Ingrese el año del viaje (debe ser 2024 o posterior): ";
                            cin>>destino.fecha[0];
                    }while(destino.fecha[0] < 2024);
                    do{
                        cout<<"Ingrese el mes del viaje (no debe ser mayor a 12): ";
                            cin>>destino.fecha[1];
                    }while (destino.fecha[1] > 12);
                    // Impresión del calendario para el mes y año ingresados
                    imprimirCalendario(destino.fecha[1], destino.fecha[0]);
                    do{
                        cout<<"Ingrese el día del viaje (no debe exceder los días del mes): ";
                            cin>>destino.fecha[2];
                    }while(destino.fecha[2] > diasMes(destino.fecha[1], destino.fecha[0]));
                    // Validación de la fecha ingresada
                    if(fechaUsada(destinosFamilia[familiar], destino.fecha)){
                        cout<<"Ya existe un viaje en esta fecha. Por favor, ingrese una fecha diferente."<<endl;
                    }
                }while(fechaUsada(destinosFamilia[familiar], destino.fecha));
                // Ingreso de las actividades a realizar en el destino
                cout<<"Ingrese el número de actividades que vas a realizar: ";
                    cin>>numActividades;
                destino.actividades.resize(numActividades);
                // Ciclo para ingresar las actividades
                for(int i=0; i<numActividades; i++){
                    cout<<"Ingrese la actividad "<<i + 1<<": ";
                        cin>>destino.actividades[i];
                }
                // Validación de superposición de destinos
                if(superposicionDestino(destinosFamilia[familiar], destino)){
                    cout<<"El destino se superpone con un destino existente para este miembro de la familia."<<endl;
                }else{
                    destinosFamilia[familiar].insert(destino);
                    // Impresión de confirmación de la creación del destino
                    imprimirAgregadoDestino(familiar, destino);
                }
                break;
            }
            case 2:{
                // Consulta de destinos de un miembro de la familia
                string familiar;
                cout<<"Ingrese el nombre del miembro de la familia: ";
                    cin>>familiar;
                imprimirDestinosFamiliar(destinosFamilia, familiar);
                break;
            }
            case 3: {
                // Consulta de miembros de la familia que quieren ir a un destino específico
                string destino;
                cout<<"Ingrese el nombre del destino: ";
                    cin>>destino;
                familiaresDestino(destinosFamilia, destino);
                break;
            }
            case 4:
                // Impresión de todos los destinos de la familia con sus respectivos miembros, fechas y actividades
                imprimirDestinos(destinosFamilia);
                break;
            case 5:
                // Salida del programa
                cout<<"Saliendo..."<<endl;
                break;
            default:
                // Mensaje de error para opción inválida
                cout<<"Opción inválida."<<endl;
        }
    }while(eleccion != 5);

    return 0;
}