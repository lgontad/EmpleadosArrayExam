#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "arraylist.h"

#define TAM 40

typedef struct
{
    int legajo;
    char nombre[20];
    char sexo;
    float sueldo;
    int idSector;
    int isEmpty;
} eEmpleado;

typedef struct
{
    int id;
    char descripcion[20];
} eSector;

//SETERS//
int empleado_setSector(eEmpleado* this, int idSector);
float empleado_setSueldo(eEmpleado* this, float sueldo);
char empleado_setSexo(eEmpleado* this, char sexo);
char* empleado_setNombre(eEmpleado* this, char* nombre);
int empleado_setLegajo(eEmpleado* this, int legajo);


//GETERS//
int empleado_getSector(eEmpleado* this);
int empleado_getSueldo(eEmpleado* this);
char empleado_getSexo(eEmpleado* this);
char* empleado_getNombre(eEmpleado* this);
int empleado_getLegajo(eEmpleado* this);

int compararEmpleadosSueldo(void* x, void* y);
int compararEmpleadosNombre (void* x, void* y);
int compararEmpleadosSexo (void* x, void* y);
int compararEmpleadosLegajo (void* x, void* y);
void sumatoriaSueldos(ArrayList* x, eSector* sectores, int tamSector);

int funcionFiltrar(void* empleados);
void filtrarEmpleados (ArrayList* lista, eSector* sectores, int tamSector, ArrayList* lista2);
void guardarEmpleados (char* path, ArrayList* listaEmpleados);
void parsearEmpleados ( char* path, ArrayList* listaEmpleados);

//void inicializarEmpleados( eEmpleado* x, int tam);
//int buscarLibre( eEmpleado* x, int tam);
//int buscarEmpleado(ArrayList* x, int legajo);
void mostrarEmpleado(eEmpleado* emp, eSector* sectores, int tamSector);
void mostrarEmpleados(ArrayList* emp, eSector* sectores, int tamSector);
void agregarEmpleado(ArrayList* empleados, eSector* sectores, int tamSector);



void eliminarEmpleado(ArrayList* empleados, eSector* sectores, int tamSector);
void modificarEmpleado(ArrayList* empleados, eSector* sectores, int tamSector);
int elegirSector(eSector* sectores, int tam);
void cargarDescripcion(eSector* sectores, int tamSector, int idSector, char* cadena);

void listarEmpleadosXSector(ArrayList* x, eSector* sectores, int tamSector);
void ordenarXSectorYNombre(ArrayList* x, eSector* sectores, int tamSector);
void mostrarEmpleadosMasGanadores(ArrayList* x, eSector* sectores, int tamSector);

//void harcodearEmpleados(ArrayList* x); no hace falta por que esta el parser
int menu();
