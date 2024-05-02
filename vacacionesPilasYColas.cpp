#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

//Creación de la clase Destino
class Destino{
public:
    //Atributos de la clase Destino
    string nombre;
    string fechaInicio;
    string fechaFin;
    vector<string> actividades;

    //Constructor vacío y con parámetros
    Destino():nombre(""), fechaInicio(""), fechaFin("") {}
    Destino(string nombre, string fechaInicio, string fechaFin):nombre(nombre), fechaInicio(fechaInicio), fechaFin(fechaFin) {}

    //Método para agregar actividades
    void agregarActividad(string actividad){
        actividades.push_back(actividad);
    }
};

//Creación de la clase ProgramadorViajes que será utilizada por la clase Familia
class ProgramadorViajes{
    public:
    //Atributos de la clase ProgramadorViajes
    stack<Destino> pilaDestinos;
    queue<Destino> colaDestinos;
    set<string> destinosAgregados;

    //Método para verificar si las fechas de dos destinos se superponen
    bool fechasSeSuperponen(Destino d1, Destino d2){
        return d1.fechaInicio <= d2.fechaFin && d1.fechaFin >= d2.fechaInicio;
    }

    //Método para agregar un destino a la pila
    void agregarDestinoPila(Destino destino){
        //Crear una pila temporal
        stack<Destino> pilaTemp = pilaDestinos;
        //Verificar si las fechas del destino a agregar se superponen con algún destino existente en la pila
        while (!pilaTemp.empty()){
            if(fechasSeSuperponen(pilaTemp.top(), destino)){
                cout<<"Las fechas se superponen con un viaje existente."<<endl;
                return;
            }
            pilaTemp.pop();
        }
        //Verificar si el destino ya ha sido agregado a la pila y si no, agregarlo
        if(destinosAgregados.find(destino.nombre) == destinosAgregados.end()){
            pilaDestinos.push(destino);
            destinosAgregados.insert(destino.nombre);
        }else{
            cout<<"El destino ya ha sido agregado."<<endl;
        }
    }

    //Método para agregar un destino a la cola
    void agregarDestinoCola(Destino destino) {
        //Crear una cola temporal
        queue<Destino> colaTemp = colaDestinos;
        //Verificar si las fechas del destino a agregar se superponen con algún destino existente en la cola
        while(!colaTemp.empty()){
            if(fechasSeSuperponen(colaTemp.front(), destino)){
                cout<<"Las fechas se superponen con un viaje existente."<<endl;
                return;
            }
            colaTemp.pop();
        }
        //Verificar si el destino ya ha sido agregado a la cola y si no, agregarlo
        if(destinosAgregados.find(destino.nombre) == destinosAgregados.end()){
            colaDestinos.push(destino);
            destinosAgregados.insert(destino.nombre);
        }else{
        cout<<"El destino ya ha sido agregado."<<endl;
        }
    }
};

//Creación de la clase Familia
class Familia{
    public:
    //Atributo de la clase Familia
    map<string, ProgramadorViajes> miembros;

    //Método para agregar un miembro a la familia
    void agregarMiembro(string nombre, ProgramadorViajes programador){
        miembros[nombre] = programador;
    }

    //Método para agregar un destino a un miembro de la familia
    void agregarDestinoMiembro(string nombre, Destino destino, bool pilaCola){
        //Verificar si el miembro existe en la familia y si es así, agregar el destino a la pila o a la cola
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

    //Método para consultar los destinos de un miembro de la familia
    void consultarDestinosMiembro(string nombre){
        //Verificar si el miembro existe en la familia y si es así, mostrar los destinos de la pila y de la cola
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

    //Método de tipo vector para obtener los miembros de la familia que van a un mismo destino de las pilas y colas
    vector<string> miembrosVisitandoDestino(string nombreDestino){
        //Crear un vector de string para almacenar los resultados
        vector<string> resultados;
        //Recorrer los miembros de la familia y verificar si el destino se encuentra en la pila o en la cola
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
            //Verificar si el destino ya ha sido agregado a los resultados
            if(!resultados.empty() && resultados.back() == par.first) continue;
            //Si no se ha agregado, verificar si el destino se encuentra en la cola
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

    //Método de tipo vector para obtener las actividades de un destino
    vector<string> obtenerActividadesDestino(string nombreDestino){
        //Crear un vector de string para almacenar las actividades
        vector<string> actividades;
        //Recorrer los miembros de la familia y verificar si el destino se encuentra en la pila o en la cola para obtener las actividades
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
            //Verificar si las actividades ya han sido agregadas
            if(!actividades.empty()) continue;
            //Si no se han agregado, verificar si el destino se encuentra en la cola para obtener las actividades
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

//Función de ejecución principal
int main() {
    //Creación de un objeto de la clase Familia
    Familia familia;
    //Ciclo infinito para mostrar el menú de opciones
    while(true){
        //Declaración de variables locales 
        string nombre;
        string nombreDestino;
        string fechaInicio;
        string fechaFin;
        Destino destino;
        vector<string> miembros;
        vector<string> actividades;
        int eleccion;

        //Menú de opciones
        cout<<"Bienvenido al planificador de vacaciones. ¿Qué desea hacer?"<<endl;
        cout<<"1. Agregar miembro a la familia.\n2. Planificar un nuevo viaje.\n3. Consultar destinos de un miembro de la familia.\n4. Consultar miembros que van a un mismo destino.\n5. Salir."<<endl;
        cout<<"Ingrese una opción: "<<endl;
            cin>>eleccion;
        cout<<"------------------------------------------"<<endl;
        
        //Switch para ejecutar la opción seleccionada
        switch (eleccion) {
            //Caso 1: Agregar miembro a la familia
            case 1:{
                cout<<"Ingrese el nombre del miembro de la familia: "<<endl;
                    cin>>nombre;
                familia.agregarMiembro(nombre, ProgramadorViajes());
                cout<<"Miembro agregado."<<endl;
            }
            break;
            //Caso 2: Planificar un nuevo viaje para un miembro de la familia
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
                //Ciclo para agregar actividades al destino
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
                
                //Verificar si la elección es válida y agregar el destino a la pila o a la cola
                if(eleccion == 1){
                    familia.agregarDestinoMiembro(nombre, destino, false);
                }else if(eleccion == 2){
                    familia.agregarDestinoMiembro(nombre, destino, true);
                }else{
                    cout<<"Opción no válida."<<endl;
                }
            }
            break;
            //Caso 3: Consultar los destinos de un miembro de la familia
            case 3:{
                //Pedir el nombre del miembro de la familia
                cout<<"Ingrese el nombre del miembro de la familia: "<<endl;
                    cin>>nombre;
                familia.consultarDestinosMiembro(nombre);

                //Pedir el nombre del destino para obtener las actividades
                cout<<"Ingrese el nombre del destino: "<<endl;
                    cin>>nombreDestino;
                actividades = familia.obtenerActividadesDestino(nombreDestino);
                cout<<"Actividades para "<<nombreDestino<<":"<<endl;
                for(const string& actividad : actividades){
                    cout<<actividad<<endl;
                }
            }
            break;
            //Caso 4: Consultar los miembros de la familia que van a un mismo destino
            case 4:{
                //Pedir el nombre del destino para obtener los miembros de la familia que quieren ir a ese destino
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
            //Caso 5: Salir del programa
            case 5:{
                return 0;
            }
            //Caso por defecto: Opción no válida
            default:
                cout<<"Opción no válida."<<endl;
        }
    }
    return 0;
}