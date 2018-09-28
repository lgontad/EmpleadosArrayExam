#include "Funciones.h"
#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/*void inicializarEmpleados( eEmpleado* x, int tam)
{
    for(int i=0; i < tam; i++)
    {
        (x + i)->isEmpty = 0;
    }
}*/

/*int buscarLibre( eEmpleado x[], int tam)
{
    int indice = -1;

    for(int i=0; i< tam; i++)
    {

        if( (x+i)->isEmpty == 0)
        {
            indice = i;
            break;
        }
    }
    return indice;
}*/

int buscarEmpleado(ArrayList* x, int legajo)
{
    int indice = -1;
    eEmpleado* unEmpleado;
    for ( int i = 0; i< x->len(x); i++)
    {
        unEmpleado = (eEmpleado*)x->get(x,i);
        if( unEmpleado->legajo == legajo && unEmpleado->isEmpty == 1)
        {
            indice = i;
            break;
        }
    }
    return indice;
}

int menu()
{
    int opcion;
    system("cls");
    printf("\n      ***Menu de Opciones***\n\n");
    printf("   1- Alta\n");
    printf("   2- Baja\n");
    printf("   3- Modificar\n");
    printf("   4- Listar empleados\n");
    printf("   5- Ordenar empleados por nombre\n");
    printf("   6- Mostrar los datos de el/los empleados que mas ganan por sector\n");
    printf("   7- Listar todos los empleados de un sector\n");
    printf("   8- Sumatoria de sueldos por sexo\n");
    printf("   9- Filtrar femeninos con sueldo mayor a $15000\n");
    printf("  10- Guardar CSV\n");
    printf("  11- Salir\n");
    printf("\n   Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

void agregarEmpleado(ArrayList* empleados, eSector* sectores, int tamSector)
{
    eEmpleado* nuevoEmpleado;
    int esta;
    int legajo;

    system("cls");
    printf("\n   *** Alta Empleado ***\n\n");

    printf(" Ingrese legajo: ");
    scanf("%d", &legajo);

    esta = buscarEmpleado(empleados, legajo);

        if(esta != -1)
        {
            printf("Existe un empleado con el legajo %d\n", legajo);
            mostrarEmpleado( (eEmpleado*)empleados->get(empleados, esta), sectores, tamSector);
        }
        else
        {
            nuevoEmpleado = newEmpleado();
            if (nuevoEmpleado !=NULL)
                {

                    nuevoEmpleado->legajo = legajo;

                    printf(" Ingrese nombre: ");
                    fflush(stdin);
                    gets(nuevoEmpleado->nombre);

                    printf(" Ingrese sexo: ");
                    fflush(stdin);
                    scanf("%c", &nuevoEmpleado->sexo);

                    printf(" Ingrese sueldo: ");
                    fflush(stdin);
                    scanf("%f", &nuevoEmpleado->sueldo);

                    nuevoEmpleado->idSector = elegirSector(sectores, 5);

                    nuevoEmpleado->isEmpty = 1;

                    empleados->add(empleados, nuevoEmpleado);
                }

        }

    printf("\n");

}

void mostrarEmpleado(eEmpleado* emp, eSector* sectores, int tamSector)
{
    char descripcion[20];

    cargarDescripcion(sectores, tamSector, emp->idSector, descripcion);

    printf(" %4d %10s  %2c   %6.2f %10s \n\n", emp->legajo, emp->nombre, emp->sexo, emp->sueldo, descripcion);

}


void mostrarEmpleados(ArrayList* emp, eSector* sectores, int tamSector)
{

    int retorno = -1;
    eEmpleado* unEmpleado;

    system("cls");
    printf("------------------------------------------\n");
    printf(" Legajo   Nombre  Sexo   Sueldo     Sector\n");
    printf("------------------------------------------\n\n");

    if ( emp != NULL )
    {
        for(int i = 0; i < emp->len(emp); i++) // es para saber el size
        {
            unEmpleado = (eEmpleado*)emp->get(emp, i);// los casteo a puntero empleado
            if(unEmpleado->isEmpty == 1)
            {
                mostrarEmpleado(unEmpleado, sectores, tamSector);
                retorno = 0;

            }

        }
    printf("------------------------------------------\n\n");

    }
    return retorno;
}

void eliminarEmpleado(ArrayList* empleados, eSector* sectores, int tamSector)
{
    eEmpleado* unEmpleado;
    int legajo;
    int indice;
    char borrar;
    system("cls");
    printf("\n*** Borrar Empleado ***\n\n");
    printf(" Ingrese legajo: ");
    scanf("%d", &legajo);

    indice = buscarEmpleado(empleados, legajo);
    if( indice == -1)
    {
        printf("No hay ningun empleado con el legajo %d\n", legajo);
        system("pause");
    }
    else
    {
        unEmpleado = (eEmpleado*)empleados->get(empleados, indice);
        printf("\nEmpleado encontrado!!!\n\n");
        mostrarEmpleado( unEmpleado, sectores, tamSector);

        printf("\nConfirma borrado?: ");
        fflush(stdin);
        scanf("%c", &borrar);
        if(borrar != 's')
        {
            printf("Borrado cancelado\n\n");
        }
        else
        {
            unEmpleado->isEmpty = 0;
            printf("Se ha eliminado el empleado\n\n");
        }
        system("pause");
    }

}

void modificarEmpleado(ArrayList* empleados, eSector sectores[], int tamSector)
{

    eEmpleado* unEmpleado;
    int legajo;
    int indice;
    char modificar;
    float nuevoSueldo;

    printf("Ingrese legajo: ");
    scanf("%d", &legajo);

    indice = buscarEmpleado(empleados, legajo);

    if( indice == -1)
    {
        printf("No hay ningun empleado con el legajo %d\n", legajo);
    }
    else
    {
        unEmpleado = (eEmpleado*)empleados->get(empleados, indice);
        mostrarEmpleado( unEmpleado, sectores, tamSector);

        printf("\nModifica sueldo?: ");
        fflush(stdin);
        scanf("%c", &modificar);
        if(modificar != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {
            printf("Ingrese nuevo sueldo: ");
            scanf("%f", &nuevoSueldo);
            unEmpleado->sueldo = nuevoSueldo;
            printf("Se ha modificado el sueldo con exito\n\n");
        }

        system("pause");
    }

}


int elegirSector(eSector* sectores, int tam)
{
    int idSector;
    printf("\n  ***Sectores***\n\n");
    for(int i=0; i < tam; i++)
    {
        printf("  %d %s\n", (sectores + i)->id, (sectores + i)->descripcion);
    }
    printf("\n Seleccione sector: ");
    scanf("%d", &idSector);

    return idSector;
}

void cargarDescripcion(eSector* sectores, int tamSector, int idSector, char* cadena)
{
    for(int i=0; i < tamSector; i++)
    {
        if( (sectores + i)->id == idSector)
        {
            strcpy(cadena, (sectores + i)->descripcion);
            break;
        }
    }
}

void listarEmpleadosXSector(ArrayList* x, eSector* sectores, int tamSector)
{
    eEmpleado* unEmpleado;
    int idSector;
    char descripcion[20];
    int flag = 0;

    idSector = elegirSector(sectores, tamSector);

    cargarDescripcion(sectores, tamSector, idSector, descripcion);

    system("cls");
    printf("Empleados del sector %s\n\n", descripcion);
    for(int i=0; i< x->len(x); i++)
    {
        unEmpleado = (eEmpleado*)x->get(x,i);
        if( unEmpleado->isEmpty == 1 && unEmpleado->idSector == idSector)
        {
            mostrarEmpleado(unEmpleado, sectores, tamSector);
            flag = 1;
        }
    }

    if(flag == 0)
    {
        printf("No hay empleados que mostrar\n\n");
    }

}

/*void ordenarXSectorYNombre(ArrayList* x, eSector* sectores, int tamSector)  // sort, el array list le va a tirar 2 elementos del array
{
    eEmpleado* unEmpleadoi;
    eEmpleado* unEmpleadoj;
    char descripcionI[20];
    char descripcionJ[20];
    eEmpleado* auxEmpleado;

    for(int i=0; i< x->len(x)-1; i++)
    {
        unEmpleadoi = (eEmpleado*)x->get(x,i);
        for(int j = i +1; j < x->len(x); j++)
        {
            unEmpleadoj = (eEmpleado*)x->get(x,j);
            cargarDescripcion(sectores, tamSector, unEmpleadoi->idSector, descripcionI);
            cargarDescripcion(sectores, tamSector, unEmpleadoj->idSector, descripcionJ);
            if( strcmp(descripcionI, descripcionJ) > 0)
            {
                auxEmpleado = unEmpleadoi;
                unEmpleadoi = unEmpleadoj;
                unEmpleadoj = auxEmpleado;
            }
            else if( strcmp(descripcionI, descripcionJ) == 0 && unEmpleadoi->sexo > unEmpleadoj->sexo)
            {
                auxEmpleado = unEmpleadoi;
                unEmpleadoi = unEmpleadoj;
                unEmpleadoj = auxEmpleado;
            }
            else if( strcmp(descripcionI, descripcionJ) == 0 && unEmpleadoi->sexo == unEmpleadoj->sexo && strcmp(unEmpleadoi->nombre, unEmpleadoj->nombre) > 0)
            {
                auxEmpleado = unEmpleadoi;
                unEmpleadoi = unEmpleadoj;
                unEmpleadoi = auxEmpleado;
            }
        }
    }
    system("pause");
    printf("\nEmpleados ordenados con exito!!!\n\n");

}*/


int compararEmpleadosSueldo (void* x, void* y)
{

    eEmpleado* emp1 = (eEmpleado*)x;
    eEmpleado* emp2 = (eEmpleado*)y;
    int retorno;

    // con el sort le digo con que criterio quiero comprar

    if (emp1->sueldo == emp2->sueldo)
    {
        retorno = 0; // igual
    }
    else if (emp1->sueldo > emp2->sueldo)
    {
        retorno = 1; // mayor
    }
    else
    {
        retorno = -1;
    }
    return retorno;
}

int compararEmpleadosNombre (void* x, void* y)
{

    eEmpleado* emp1 = (eEmpleado*)x;
    eEmpleado* emp2 = (eEmpleado*)y;

    return strcmp(emp1->nombre, emp2->nombre);

}

int compararEmpleadosSexo (void* x, void* y)
{

    eEmpleado* emp1 = (eEmpleado*)x;
    eEmpleado* emp2 = (eEmpleado*)y;
    int retorno;

    // con el sort le digo con que criterio quiero comprar

    if (emp1->sexo == emp2->sexo)
    {
        retorno = 0; // igual
    }
    else if (emp1->sexo > emp2->sexo)
    {
        retorno = 1; // mayor
    }
    else
    {
        retorno = -1;
    }
    return retorno;
}

int compararEmpleadosLegajo (void* x, void* y)
{

    eEmpleado* emp1 = (eEmpleado*)x;
    eEmpleado* emp2 = (eEmpleado*)y;
    int retorno;

    // con el sort le digo con que criterio quiero comprar

    if (emp1->legajo == emp2->legajo)
    {
        retorno = 0; // igual
    }
    else if (emp1->legajo > emp2->legajo)
    {
        retorno = 1; // mayor
    }
    else
    {
        retorno = -1;
    }
    return retorno;
}

/*void harcodearEmpleados(eEmpleado* x)
{
    eEmpleado y[]=
    {
        {1111, "ana", 'f', 15000, 4, 1},
        {3333, "luis", 'm', 25000, 4, 1},
        {4444, "alberto", 'm', 30000, 5, 1},
        {5555, "julia", 'f', 30000, 1, 1},
        {1313, "julieta", 'f', 23000, 2, 1},
        {4545, "andrea", 'f', 30000, 5, 1},
        {3232, "mauro", 'm', 27000, 5, 1},
        {4545, "andres", 'm', 30000, 3, 1},
        {3232, "mariela", 'f', 27000, 3, 1}
    };

    for(int i=0; i<9; i++)
    {
       *(x + i) = *(y + i);
    }

}*/

void mostrarEmpleadosMasGanadores(ArrayList* x, eSector* sectores, int tamSector)
{
    float maxSueldo;
    char descripcion[20];
    int flag;
    eEmpleado* unEmpleado;

    for(int i=0; i < tamSector; i++){ // recorre sectores
         cargarDescripcion(sectores, tamSector, (sectores+i)->id, descripcion);
         printf("\nSector %s\n", descripcion);
         flag = 0;
         for(int j=0; j < x->len(x); j++){ // sueldo maximo del sector

            unEmpleado = (eEmpleado*)x->get(x,j);
            if(( unEmpleado->sueldo > maxSueldo && unEmpleado->isEmpty == 1 && unEmpleado->idSector == (sectores + i)->id) || ((flag == 0&& unEmpleado->isEmpty == 1 && unEmpleado->idSector == (sectores + i)->id))){
                maxSueldo = unEmpleado->sueldo;
                flag = 1;
            }
         }

          for(int j=0; j < x->len(x); j++){ // muestra todos los empleados del sector que cobran ese sueldo
            unEmpleado = (eEmpleado*)x->get(x,j);
            if( unEmpleado->sueldo == maxSueldo && unEmpleado->idSector == (sectores + i)->id &&  unEmpleado->isEmpty == 1){
                mostrarEmpleado(unEmpleado, sectores, tamSector);
            }
          }

    }

}


void parsearEmpleados ( char* path, ArrayList* listaEmpleados)
{
    FILE* f;

    eEmpleado* nuevoEmpleado; // variable vacia, que espera la DM de un empleado, debo construirlo
    int indice;
    int cant;
    char buffer[6][128];  // una vez abierto el archivo para lectura con fscanf lo que tenemos que comenzar a hacer es ir letendo lo que tenemos hasta las comas para recuperar los datos
                        // 6 filas y 128 columnas
    f = fopen(path, "r");

    if ( f != NULL && listaEmpleados != NULL)
     {
        fscanf(f, "%[^,], %[^,], %[^,], %[^,],%[^,],%s\n", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]); // lectrua fantasma de la linea 1

        while(!feof(f))
        {
            cant = fscanf(f, "%[^,], %[^,], %[^,], %[^,],%[^,],%s\n", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]);
            // leo toda la linea y me guardo la cantidad para evitar una escritura al final q no sirve
            if (cant == 6)
            {

                nuevoEmpleado = newEmpleado(); // pido espacio una vez que pude leer el archivo
                if (nuevoEmpleado != NULL)
                {

                nuevoEmpleado->legajo = atoi(buffer[0]);
                strcpy(nuevoEmpleado->nombre, buffer[1]);
                nuevoEmpleado->sexo = buffer[2][0]; // se obtiene de fila 2 columna 0, xq es una cadena "m" "\0"
                nuevoEmpleado->sueldo = atof(buffer[3]);
                nuevoEmpleado->idSector = atoi(buffer[4]);
                nuevoEmpleado->isEmpty = atoi(buffer[5]);

                listaEmpleados->add(listaEmpleados, nuevoEmpleado);// de la lista del array invoco la funcion ad

                }


            }
            else {
                break; // si no pudo leer los 6 datos salimos
            }


        }
         fclose(f); // para cerrar el archivo

     }


}

void guardarEmpleados (char* path, ArrayList* listaEmpleados)
{
    FILE* f;

    f = fopen(path, "w");
    eEmpleado* unEmpleado;

    if (f!=NULL)
    {
        fprintf(f, "id,Nombre,Sexo,Sueldo,idSector,IsEmpty\n");

        for (int i=0; i< listaEmpleados->len(listaEmpleados) ;i++)
        {
            unEmpleado = (eEmpleado*)listaEmpleados->get(listaEmpleados, i);
            fprintf(f, "%d,%s,%c,%.2f,%d,%d\n", unEmpleado->legajo,unEmpleado->nombre, unEmpleado->sexo,unEmpleado->sueldo,unEmpleado->idSector,unEmpleado->isEmpty);
        }

    fclose(f);

    }
    printf("Archivo guardado exitosamente.\n\n");
    system("pause");

}

void filtrarEmpleados (ArrayList* lista, eSector* sectores, int tamSector, ArrayList* lista2)
{

    eEmpleado* unEmpleado;

    for (int i = 0; i < lista->len(lista); i++)
    {
        unEmpleado = (eEmpleado*)lista->get(lista, i);
        if (unEmpleado->sexo == 'M' && unEmpleado->sueldo > 15000) //
        {
            lista2->add(lista2, unEmpleado);
        }

    }
    mostrarEmpleados(lista2, sectores, tamSector);

}

int funcionFiltrar(void* empleados)
{
    int retorno=0;
    eEmpleado* e;
    e = (eEmpleado*)empleados;
    if(empleados!=NULL)
    {
        if(e->sexo == 'F' && e->sueldo > 15000)
        {
                retorno=1;
        }
        else
        {
            retorno=0;
        }
    }
    return retorno;
}

void sumatoriaSueldos(ArrayList* x, eSector* sectores, int tamSector)
{

    float sueldoM = 0;
    float sueldoF = 0;
    eEmpleado* unEmpleado;

    if(x != NULL)
    {
        for(int i=0; i < x->len(x); i++)
        {

            unEmpleado = (eEmpleado*)x->get(x,i);
            if( unEmpleado->sexo == 'M' && unEmpleado->isEmpty == 1 )
            {
                sueldoM = unEmpleado->sueldo + sueldoM;
            }
            else
            {
                sueldoF = unEmpleado->sueldo + sueldoF;
            }

        }
        printf("Las sumatorias de sueldos serian:\n -Hombres: %.2f \n -Mujeres: %.2f\n", sueldoM, sueldoF);
    }
}



////////////// SET - GET ///////////////////////////


int empleado_getLegajo(eEmpleado* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->legajo;
    }
    return returnAux;
}

char* empleado_getNombre(eEmpleado* this)
{
    char* returnAux = NULL;
    if(this != NULL)
    {
        returnAux = this->nombre;
    }
    return returnAux;
}


char empleado_getSexo(eEmpleado* this)
{
    char* returnAux = NULL;
    if(this != NULL)
    {
        returnAux = this->sexo;
    }
    return returnAux;
}

int empleado_getSueldo(eEmpleado* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->sueldo;
    }
    return returnAux;
}

int empleado_getSector(eEmpleado* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = this->idSector;
    }
    return returnAux;
}


int empleado_setLegajo(eEmpleado* this, int legajo)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        this->legajo = legajo;
    }
    return returnAux;
}

char* empleado_setNombre(eEmpleado* this, char* nombre)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        strcpy(this->nombre, nombre);
    }
    return returnAux;
}


char empleado_setSexo(eEmpleado* this, char sexo)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        strcpy(this->sexo, sexo);
    }
    return returnAux;

}

float empleado_setSueldo(eEmpleado* this, float sueldo)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        this->sueldo = sueldo;
    }
    return returnAux;
}

int empleado_setSector(eEmpleado* this, int idSector)
{
    int returnAux = -1;
    if(this != NULL)
    {
        returnAux = 0;
        this->idSector = idSector;
    }
    return returnAux;
}
