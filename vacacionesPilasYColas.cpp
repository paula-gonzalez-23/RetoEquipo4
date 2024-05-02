#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Destino{
public:
    string nombre;
    string fechaInicio;
    string fechaFin;
    vector<string> actividades;

    Destino():nombre(""), fechaInicio(""), fechaFin("") {}
    Destino(string nombre, string fechaInicio, string fechaFin):nombre(nombre), fechaInicio(fechaInicio), fechaFin(fechaFin) {}

    void agregarActividad(string actividad){
        actividades.push_back(actividad);
    }
};

class ProgramadorViajes{
    public:
    stack<Destino> pilaDestinos;
    queue<Destino> colaDestinos;
    set<string> destinosAgregados;

    bool fechasSeSuperponen(Destino d1, Destino d2){
        return d1.fechaInicio <= d2.fechaFin && d1.fechaFin >= d2.fechaInicio;
    }

    void agregarDestinoPila(Destino destino){
        stack<Destino> pilaTemp = pilaDestinos;
        while (!pilaTemp.empty()){
            if(fechasSeSuperponen(pilaTemp.top(), destino)){
                cout<<"Las fechas se superponen con un viaje existente."<<endl;
                return;
            }
            pilaTemp.pop();
        }

        if(destinosAgregados.find(destino.nombre) == destinosAgregados.end()){
            pilaDestinos.push(destino);
            destinosAgregados.insert(destino.nombre);
        }else{
            cout<<"El destino ya ha sido agregado."<<endl;
        }
    }

    void agregarDestinoCola(Destino destino) {
        queue<Destino> colaTemp = colaDestinos;
        while(!colaTemp.empty()){
            if(fechasSeSuperponen(colaTemp.front(), destino)){
                cout<<"Las fechas se superponen con un viaje existente."<<endl;
                return;
            }
            colaTemp.pop();
        }

        if(destinosAgregados.find(destino.nombre) == destinosAgregados.end()){
            colaDestinos.push(destino);
            destinosAgregados.insert(destino.nombre);
        }else{
        cout<<"El destino ya ha sido agregado."<<endl;
        }
    }
};

class Familia{
    public:
    map<string, ProgramadorViajes> miembros;

    void agregarMiembro(string nombre, ProgramadorViajes programador){
        miembros[nombre] = programador;
    }

    void agregarDestinoMiembro(string nombre, Destino destino, bool pilaCola){
        if(miembros.find(nombre) != miembros.end()){
            if(pilaCola){
                miembros[nombre].agregarDestinoPila(destino);
            }else{
                miembros[nombre].agregarDestinoCola(destino);
            }
        }else{
            cout<<"Miembro no encontrado."<<endl;
        }
    }

    void consultarDestinosMiembro(string nombre){
        if (miembros.find(nombre) != miembros.end()){
            ProgramadorViajes programador = miembros[nombre];
            cout<<"Destinos en pila para "<<nombre<<":"<<endl;
            while(!programador.pilaDestinos.empty()){
                cout<<programador.pilaDestinos.top().nombre<<endl;
                programador.pilaDestinos.pop();
            }
            cout<<"Destinos en cola para "<<nombre<<":"<<endl;
            while(!programador.colaDestinos.empty()){
                cout<<programador.colaDestinos.front().nombre<<endl;
                programador.colaDestinos.pop();
            }
        }else{
            cout<<"Miembro no encontrado."<<endl;
        }
    }

    vector<string> miembrosVisitandoDestino(string nombreDestino){
        vector<string> resultados;
        for(auto& par : miembros){
            ProgramadorViajes programador = par.second;
            stack<Destino> pila = programador.pilaDestinos;
            while(!pila.empty()){
                if(pila.top().nombre == nombreDestino){
                    resultados.push_back(par.first);
                    break;
                }
                pila.pop();
            }
            if(!resultados.empty() && resultados.back() == par.first) continue;
            queue<Destino> cola = programador.colaDestinos;
            while(!cola.empty()){
                if(cola.front().nombre == nombreDestino){
                    resultados.push_back(par.first);
                    break;
                }
                cola.pop();
            }
        }
        return resultados;
    }

    vector<string> obtenerActividadesDestino(string nombreDestino){
        vector<string> actividades;
        for(auto& par : miembros){
            ProgramadorViajes programador = par.second;
            stack<Destino> pila = programador.pilaDestinos;
            while(!pila.empty()){
                if(pila.top().nombre == nombreDestino){
                    for(const string& actividad : pila.top().actividades){
                        actividades.push_back(actividad);
                    }
                    break;
                }
                pila.pop();
            }
            if(!actividades.empty()) continue;
            queue<Destino> cola = programador.colaDestinos;
            while(!cola.empty()){
                if(cola.front().nombre == nombreDestino){
                    for(const string& actividad : cola.front().actividades){
                        actividades.push_back(actividad);
                    }
                    break;
                }
                cola.pop();
            }
        }
        return actividades;
    }
};

int main() {
    Familia familia;
    while(true){
        string nombre;
        string nombreDestino;
        string fechaInicio;
        string fechaFin;
        Destino destino;
        vector<string> miembros;
        vector<string> actividades;
        int eleccion;

        cout<<"Bienvenido al planificador de vacaciones. ¿Qué desea hacer?"<<endl;
        cout<<"1. Agregar miembro a la familia.\n2. Planificar un nuevo viaje.\n3. Consultar destinos de un miembro de la familia.\n4. Consultar miembros que van a un mismo destino.\n5. Salir."<<endl;
        cout<<"Ingrese una opción: "<<endl;
            cin>>eleccion;
        cout<<"------------------------------------------"<<endl;
        
        switch (eleccion) {
            case 1:{
                cout<<"Ingrese el nombre del miembro de la familia: "<<endl;
                    cin>>nombre;
                familia.agregarMiembro(nombre, ProgramadorViajes());
                cout<<"Miembro agregado."<<endl;
            }
            break;
            case 2:{
                cout<<"Ingrese el nombre del miembro de la familia: "<<endl;
                    cin>>nombre;
                cout<<"Ingrese el nombre del destino: "<<endl;
                    cin>>nombreDestino;
                cout<<"Ingrese la fecha de inicio (AAAA/MM/DD): "<<endl;
                    cin>>fechaInicio;
                cout<<"Ingrese la fecha de fin (AAAA/MM/DD): "<<endl;
                    cin>>fechaFin;
            
                Destino destino(nombreDestino, fechaInicio, fechaFin);
            
                string actividad;
                while(true){
                    cout<<"Ingrese una actividad para este destino ('X' para terminar): "<<endl;
                        cin>>actividad;
                    if(actividad == "X"){
                        break;
                    }
                    destino.agregarActividad(actividad);
                }
            
                cout<<"¿Desea agregar el destino a la pila o a la cola? (1: Pila, 2: Cola): "<<endl;
                    cin>>eleccion;
            
                if(eleccion == 1){
                    familia.agregarDestinoMiembro(nombre, destino, false);
                }else if(eleccion == 2){
                    familia.agregarDestinoMiembro(nombre, destino, true);
                }else{
                    cout<<"Opción no válida."<<endl;
                }
            }
            break;
            case 3:{
                cout<<"Ingrese el nombre del miembro de la familia: "<<endl;
                    cin>>nombre;
                familia.consultarDestinosMiembro(nombre);

                cout<<"Ingrese el nombre del destino: "<<endl;
                    cin>>nombreDestino;
                actividades = familia.obtenerActividadesDestino(nombreDestino);
                cout<<"Actividades para "<<nombreDestino<<":"<<endl;
                for(const string& actividad : actividades){
                    cout<<actividad<<endl;
                }
            }
            break;
            case 4:{
                cout<<"Ingrese el nombre del destino: "<<endl;
                    cin>>nombreDestino;
                miembros = familia.miembrosVisitandoDestino(nombreDestino);
                cout<<"Miembros de la familia que quieren ir a "<<nombreDestino<<":"<<endl;
                for(const string& miembro : miembros){
                    cout<<miembro<<endl;
                }

                actividades = familia.obtenerActividadesDestino(nombreDestino);
                cout<<"Actividades para "<<nombreDestino<<":"<<endl;
                for(const string& actividad : actividades){
                    cout<<actividad<<endl;
                }
            }
            break;
            case 5:{
                return 0;
            }
            default:
                cout<<"Opción no válida."<<endl;
        }
    }
    return 0;
}