#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Destino {
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