#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "arraylist.h"

eEmpleado* newEmpleadoParam(int legajo, char* nombre, char sexo, float sueldo, int idSector);
eEmpleado* newEmpleado(); // constructor


int main()
{
    ArrayList* lista = al_newArrayList();
    ArrayList* lista2 = al_newArrayList();
    char seguir = 's';
    if (lista == NULL)
    {
        exit(1);
    }
    eSector sectores[] =
    {
        {1, "RRHH"},
        {2, "Ventas"},
        {3, "Compras"},
        {4, "Contable"},
        {5, "Sistemas"}
    };


    parsearEmpleados("Empleados.csv", lista);

    do
    {
        switch(menu())
        {

        case 1:
            agregarEmpleado(lista, sectores, 5);
            system("pause");
            break;
        case 2:
            eliminarEmpleado(lista, sectores, 5);
            break;
        case 3:
            modificarEmpleado(lista, sectores, 5);
            break;
        case 4:
            mostrarEmpleados(lista, sectores, 5);
            system("pause");
            break;
        case 5:
            lista->sort(lista,compararEmpleadosNombre,1);
            mostrarEmpleados(lista, sectores,5);
            system("pause");
            break;
        case 6:
            mostrarEmpleadosMasGanadores(lista, sectores, 5);
            system("pause");
            break;
        case 7:
            listarEmpleadosXSector(lista, sectores, 5);
            system("pause");
            break;
        case 8:
            sumatoriaSueldos(lista, sectores, 5);
            system("pause");
            break;
        case 9:
            lista2= al_filter(lista,funcionFiltrar);
            mostrarEmpleados(lista2, sectores, 5);
            system("pause");
            break;
        case 10:
            guardarEmpleados("Filtrado.csv", lista2);
            break;
        case 11:
            seguir = 'n';
            guardarEmpleados("Empleados.csv", lista);
            break;
        }

    }
    while(seguir == 's');

    return 0;
}

// Funcion Constructora
eEmpleado* newEmpleado()
{
    eEmpleado* nuevoEmpleado;
    nuevoEmpleado = (eEmpleado*)malloc(sizeof(eEmpleado));
    if (nuevoEmpleado != NULL)
    {
        nuevoEmpleado->legajo = 0;
        strcpy(nuevoEmpleado->nombre, "");
        nuevoEmpleado->sexo = ' ';
        nuevoEmpleado->sueldo = 0;
        nuevoEmpleado->idSector = 0;
        nuevoEmpleado->isEmpty = 0;
    }

return nuevoEmpleado;
}

eEmpleado* newEmpleadoParam(int legajo, char* nombre, char sexo, float sueldo, int idSector) // le paso todos los datos al constructor del empleado
{
        eEmpleado* nuevoEmpleado;
        nuevoEmpleado = newEmpleado();
        if (nuevoEmpleado != NULL)
        {
            nuevoEmpleado->legajo = legajo;
            strcpy(nuevoEmpleado->nombre, nombre);
            nuevoEmpleado->sexo = sexo;
            nuevoEmpleado->sueldo = sueldo;
            nuevoEmpleado->idSector = idSector;
            nuevoEmpleado->isEmpty = 1;
        }

    return nuevoEmpleado; // con esto le tiro los datos para usarlo luego en el add
}


