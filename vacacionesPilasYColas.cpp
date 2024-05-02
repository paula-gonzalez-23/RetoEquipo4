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

int main(){

    cout<<"Prueba"<<endl;

    return 0;
}