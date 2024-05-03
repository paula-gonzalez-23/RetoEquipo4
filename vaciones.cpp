#include <iostream>
#include <stack>
#include <queue>
using namespace std;

//Cola de Destinos.
queue <string> destinos;
//Pila de Familiares.
stack <string> familiares;

//Función para agregar un destino.
void agregarDestino()
{
string destino;
cout<<"Ingresa el destino que deseas agregar: "<<endl;
cin>>destino;
destinos.push(destino);
}
//Función para consultar los destinos.
void consultarDestinos()
{
cout<<"Los destinos del plan son los siguientes: "<<endl;
if (destinos.empty()) 
{
cout << "No hay destinos en el plan." << endl;
return;
}
queue<string> destinos2 = destinos; 
while (!destinos2.empty()) {
cout << destinos2.front() << endl;
destinos2.pop();
}
}

//Función para agregar un familiar al Plan.
void agregarFamiliar()
{
string familiar;
cout<<"Ingresa el Familiar que deseas agregar al Plan: "<<endl;
cin>>familiar;
familiares.push(familiar);
}

//Función para consultar los Familiares en el plan.
void consultarFamiliares()
{
cout<<"Los Familiares del plan son los siguientes: "<<endl;
if (familiares.empty()) 
{
cout << "No hay Familiares en el plan." << endl;
return;
}
stack<string> familiares2 = familiares; 
while (!familiares2.empty()) {
cout << familiares2.top() << endl;
familiares2.pop();
}
}
//Función para el menu.
void menu()
{
int opcion = 0;
string dato;
while (opcion != 5)
{
    cout <<"Bienvenido a tu Planeador Vacacional. "<<endl;
    cout <<"Que deseas realizar el día de hoy."<<endl;
    cout <<"1) Agregar un destino al Plan"<<endl;
    cout <<"2) Consultar los destinos del Plan."<<endl;
    cout <<"3) Agregar un familiar al Plan."<<endl;
    cout <<"4) Consultar los familiares en el Plan."<<endl;
    cout <<"5) Salir del sistema"<<endl;
    cout <<"Ingresa tu opción: "<<endl;
    cin >>opcion;


    if (opcion==1)
    {
    agregarDestino();
    }if (opcion==2)
    {
    consultarDestinos();
    }if (opcion==3)
    {
    agregarFamiliar();
    }if (opcion==4)
    {
    consultarFamiliares();
    }if (opcion==5)
    {
    cout <<"Usted ha salido exitosamente del sistema."<<endl;
    }else
    {
    cout <<"Opción Invalida."<<endl;
    }
    
}
}
int main()
{
 menu();
}