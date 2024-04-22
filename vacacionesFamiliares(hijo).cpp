//"Planeador vacaiones familiares para El Hijo de la familia".
#include <iostream>
#include <set>
#include <map>
#include <vector>

#include <set>
using namespace std;

typedef pair<string, string> Fechas;
typedef pair<string, Fechas> Viaje;
typedef pair<const string, Viaje> MiembroViaje;

set<string> destinos;
map<string, vector<MiembroViaje>> miembrosViajes;

//Función para agregar destino del usuario.
void agregarDestino(const string& destino) {
    destinos.insert(destino);
}

//Función para planear el viaje del usuario.
void planificarViaje(const string& miembro, const string& destino, const string& fechas) {
    Fechas fechasPair(fechas, ""); 
    // Crear un viaje con el destino y las fechas
    Viaje viaje(destino, fechasPair); 
    MiembroViaje miembroViaje(miembro, viaje); 
    miembrosViajes[miembro].push_back(miembroViaje); 

}

//Función para consultar el o los destinos del usuario.
void consultarDestino(const string& miembro) {
    if (miembrosViajes.find(miembro) != miembrosViajes.end()) {
        cout << "Destinos planificados para " << miembro << ":" << endl;
        for (const auto& viaje : miembrosViajes[miembro]) {
            cout << "- " << viaje.first << ": " << viaje.second.first << endl;
        }
    } else {
        cout << "No hay destinos planificados para el " << miembro << endl;
    }
}

//Función para encontrar el destino del usuario, a donde planea viajar cada familiar.
void encontrarDestino(const string& destino) {
    cout << "Familiares planeando visitar " << destino << ":" << endl;
    bool encontrado = false;
for (const auto& miembroViaje : miembrosViajes) {
    for (const auto& viaje : miembroViaje.second) {
    if (viaje.second.first == destino) {
        cout << "- " << miembroViaje.first << endl;
        encontrado = true;
        break;
}
}
}
if (!encontrado) {
cout << "Ningún miembro planea visitar " << destino << endl;
}
}


int main() {

    //Agregar destinos
    agregarDestino("Disney World");
    agregarDestino("Orlando Universal");
    agregarDestino("España");

    //Planear un viaje con su sitio y fechas (en forma de intervalo).
    planificarViaje("Hijo", "Disney World", "Junio 15 - Junio 22");
    planificarViaje("Hijo", "Orlando Universal", "Junio 23 - Junio 30");
    planificarViaje("Padre", "Disney World", "Junio 15 - Junio 22");
    planificarViaje("Madre", "España", "Junio 23 - Junio 30");


    //Consultar destinos planeados para un familiar en especifico.
    consultarDestino("Hijo");
    consultarDestino("Padre");
    consultarDestino("Madre");

    //Encontrar los familiares que van a cierto lugar. 
    encontrarDestino("Disney World");
    encontrarDestino("Orlando Universal");
    encontrarDestino("España");

 

//typedef, se usa para simplificar el codigo.
typedef pair<string,string> par1;

    return 0;
}