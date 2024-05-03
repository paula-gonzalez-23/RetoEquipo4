//registro de un plan de vacaciones, busqueda por fecha y ordenamiento de la fecha mas proxima a la mas lejana.

#include <iostream>
#include <queue>
#include <vector>
using namespace std;


//Cola de Ubicaciones.
queue <string> ubicaciones;

//Cola de Familiares.
queue <string> familiares;

//Cola de Fechas.
queue <string> fechas;

//Función para agregar las ubicaciones deseadas por el usuario al Plan.
void agregarUbicaiones()
{
string destino, fecha;
cout<<"Ingrese por favor el Destino que desean agregar al plan vacacional: "<<endl;
getline(cin,destino);
ubicaciones.push(destino);
cout<<"Ingrese la Fecha de el Destino (dd/mm/aa): "<<endl;
getline(cin,fecha);
fechas.push(fecha);
}

//Función para verificar los destinos disponibles para el plan vacacional, proporcionados por el Usuario.
void verificarDestinosYFechas()
{
cout <<"Estos son los destinos con sus fechas disponibles para su Plan Vacacional: "<<endl;
//Verificar si la cola esta Vacia.
if (ubicaciones.empty())
{
cout <<"Por favor ingrese Destinos a los cuales desearia viajar por favor."<<endl;
}
//Copia de la cola (ubicaciones).
queue <ubicacion> = ubicaciones;
//Si es diferente de vacio enseña las ubicaciones.
while (!ubicaion.empty())
{
cout <<ubicacion.front()<<endl;
ubicacion.pop();
}
if (fechas.empty())
{
cout <<"Por favor ingrese fechas a las cuales desearia viajar por favor."<<endl;
}
//Copia de la cola (Fechas).
queue <fecha> = fechas;
//Si es diferente de vacio enseña las fechas.
while (!fecha.empty())
{
cout <<fecha.front()<<endl;
fecha.pop();
}
}

//Función para agregar familiares al Plan.
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
//Verifica si la cola de Familiares esta Vacia.
if (familiares.empty()) 
{
cout << "No hay Familiares incluidos en el plan." << endl;
return;
}
queue <string> familiares2 = familiares; 
//Si es diferente de vacio enseña los familiares.
while (!familiares2.empty()) {
cout << familiares2.front() << endl;
familiares2.pop();
}
}
// Función para mostrar las fechas ordenadas de la más próxima a la más lejana
void fechasOrdenadas() {
//Vector para guardar el registro de las Fechas.
vector<string> fechas2;
//Copia de la Cola de Fechas.
queue<string> fecha = fechas;
//Copia de la Cola de ubicaciones.
queue<string> ubicacion = ubicaciones;
//Si es diferente de vacio enseña las fechas y los destinos iniciales.
while (!fecha.empty()) {
fechas2.fecha = fecha.front();
fechas2.ubicacion = ubicaciones.front();
fechasCopy.pop();
ubicacionesCopy.pop();
fechas2.push_back(fechas2);
}
//Se usa el metodo de ordenamiento sort siendo begin el inicial y end el final.
sort(fechas2.begin(), fechas2.end());
// Mostrar las fechas ordenadas de la más próxima a la más lejana
cout << "Fechas ordenadas de la más próxima a la más lejana:" << endl;
for (const auto& Fechas : fechas2) {
cout << fechas2.fecha << endl;
}
}

//Función Menú.
void menu()
{
int opcion;
cout <<"Bienvenido al menú"<<endl;
cout <<"1) Agregar Ubicaión al Plan."<<endl;
cout <<"2) Verificar destinos y fechas del Plan."<<endl;
cout <<"3) Agregar Familiar al Plan."<<endl;
cout <<"4) Verificar Familiares en el Plan."<<endl;
cout <<"5) Ver las fechas Ordenadas por fecha desde la mas Proxima a la más Lejana."<<endl;
cout <<"6) Salir del Programa"<<endl;
cin >>opcion;

  if (opcion==1)
    {
    agregarUbicaiones();
    }else if (opcion==2)
    {
    verificarDestinosYFechas();
    }else if (opcion==3)
    {
    agregarFamiliar();
    }else if (opcion==4)
    {
    consultarFamiliares();
    }else if (opcion==5)
    {
    fechasOrdenadas();
    }else if (opcion==6)
    {
    cout <<"Usted ha salido exitosamente del sistema."<<endl;
    }
    else
    {
    cout<<"Seleccione una opción Valida por favor."
    }
    }
    