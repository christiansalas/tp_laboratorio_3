#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
#include "utn.h"



/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *    10. Salir

 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    int retorno = -1;
    pArchivo = fopen(path,"r");
    if(!parser_EmployeeFromText(pArchivo, pArrayListEmployee))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{

  FILE* pArchivo;
    int retorno = -1;
    pArchivo = fopen(path,"rb");
    if(!parser_EmployeeFromBinary(pArchivo, pArrayListEmployee))
    {
        retorno = 0;
    }
    fclose(pArchivo);
    return retorno;
}

/** \brief Funcion que da de alta a un empleado.
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    char auxNombre[128];
    int auxHorasTrabajadas;
    float auxSueldo;
    int auxId;

    Employee* nuevoEmpleado;

    if(pArrayListEmployee!= NULL)
        {
           nuevoEmpleado= Employee_new();
           if(nuevoEmpleado!= NULL && utn_getNombre(auxNombre,128,"\nIngrese nombre\n","\n Nombre Incorrecto\n",2)== 0
              &&utn_getEntero(&auxHorasTrabajadas,9,"\n Ingrese cantidad de horas trabajadas\n","\n Error, ingrese un numero\n",2)==0
              &&utn_getEntero(&auxSueldo,10,"Ingrese Sueldo \n", "Error, ingrese un sueldo valido \n",2)==0 )
           {
                auxId=getNextId(pArrayListEmployee);
                Employee_setId(nuevoEmpleado,auxId);
                Employee_setNombre(nuevoEmpleado,auxNombre);
                Employee_setHorasTrabajadas(nuevoEmpleado,auxHorasTrabajadas);
                Employee_setSueldo(nuevoEmpleado,auxSueldo);
                 ll_add(pArrayListEmployee,nuevoEmpleado);
                retorno = 0;
           }
        }


    return retorno;
}

/** \brief Funcion que modifica los datos del empleado.-
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
int retorno = -1;
int id;
        if (pArrayListEmployee != NULL
            &&
            utn_getEntero(&id, 10, "\n Ingrese id\n", "id invalido\n", 3) == 0
            &&
            Employee_BuscarPorId (pArrayListEmployee, id)== 0)
            {

            retorno =0 ;
                printf("Empleado modificado\n");

            }
            else
            {
            printf("\n El Id no existe!! \n");
            }

        return retorno;
}
/** \brief Funcion que da de baja un empleado.
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    int id;
    int bufferId;
    char bufferNombre[128];
    int bufferSueldo;
    int bufferHoras;
     int opcion = 9;

    Employee * auxPunteroEmpleado;
    if (pArrayListEmployee != NULL &&
        utn_getEntero(&id, 10, "Ingrese Id\n", "Id invalido", 3) == 0)
    {
        for (i = 1; i< ll_len(pArrayListEmployee); i++)
        {
            auxPunteroEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getId(auxPunteroEmpleado,&bufferId);
            if(bufferId == id)
            {

                 Employee_getNombre(auxPunteroEmpleado, bufferNombre);
                 Employee_getHorasTrabajadas(auxPunteroEmpleado, &bufferHoras);
                 Employee_getSueldo(auxPunteroEmpleado,&bufferSueldo);
                 printf("\nEl empleado es :  %s\n horas Trabajdas: %d \n Sueldo: %d\n", bufferNombre, bufferHoras, bufferSueldo);
                 printf("Desea eliminar empleado 1-SI/N2- NO\n");
                 scanf("%d",&opcion);
                 if(opcion== 1)
                         {
                            Employee_delete(auxPunteroEmpleado);
                            ll_remove(pArrayListEmployee,i);
                            printf("\n Empleado Borrado con exito!!\n");
                            retorno = 0;
                            break;
                         }
                    else
                        {
                            break;
                        }

            }
        }

    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    Employee* auxPunteroEmpleado;
    char nombre[1024];
    int id;
    int bufferHorasTrabajo;
    int bufferSueldo;
    if(pArrayListEmployee != NULL)
    {
        for (i = 0; i< ll_len(pArrayListEmployee); i++)
        {
             auxPunteroEmpleado = ll_get(pArrayListEmployee,i);
             Employee_getNombre(auxPunteroEmpleado,nombre);
             Employee_getId(auxPunteroEmpleado, &id);
             Employee_getHorasTrabajadas(auxPunteroEmpleado, &bufferHorasTrabajo);
             Employee_getSueldo(auxPunteroEmpleado, &bufferSueldo);
             printf("\nId %d - Nombre: %s - Horas: %d - Sueldo: %d \n",id, nombre, bufferHorasTrabajo, bufferSueldo);
             retorno = 0;
        }
    }

    return retorno;
}
/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
int retorno = -1;
int respuestaMenu = 99;
int flag = 1;
 do
    {
        printf("1- Ordenar por id\n 2- Ordenar por nombre\n3-Volver a Menu Principal\n");

        scanf("%d", &respuestaMenu);
        switch(respuestaMenu)
        {
            case 1:
            ll_sort(pArrayListEmployee, Employee_sortById, 1);
            controller_ListEmployee(pArrayListEmployee);
            flag = 0;

            break;
            case 2:
            ll_sort(pArrayListEmployee,employee_criterioSortNombre,1);
            controller_ListEmployee(pArrayListEmployee);
           flag = 0;
            break;
            case 3:
            break;
            default:
            printf("\nOpcion  invalida, Reeingrese opcion..\n");
            break;
        }
        retorno = 0;
    }while (respuestaMenu != 3 && flag != 0);
    return retorno;
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    FILE* pArchivo = fopen(path,"w+");
    Employee* pEmpleado = NULL;
    int i;
    char bufferNombre[1024];
    int bufferId;
    int bufferHorasTrabajadas;
    int bufferSueldo;
   if(pArchivo != NULL && pArrayListEmployee != NULL)
    {
        for(i=0; i<ll_len(pArrayListEmployee); i++)
        {
            if(i==0)
            {
                fprintf(pArchivo,"id,nombre,horas,sueldo\n");
            }
            pEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getNombre(pEmpleado,bufferNombre);
            Employee_getHorasTrabajadas(pEmpleado,&bufferHorasTrabajadas);
            Employee_getSueldo(pEmpleado,&bufferSueldo);
            Employee_getId(pEmpleado,&bufferId);
            fprintf(pArchivo,"%d,%s,%d,%d\n",bufferId,bufferNombre,bufferHorasTrabajadas,bufferSueldo);
            retorno = 0;
        }
    }
    fclose(pArchivo);
    return retorno;
}
/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
    FILE *pArchivo = fopen(path,"wb");
    Employee * pEmpleado;
    int i;

    int retorno = -1;
    if(pArchivo!= NULL)
    {

    for (i=0;i<ll_len(pArrayListEmployee);i++)
        {
       pEmpleado=ll_get(pArrayListEmployee,i);
      // Employee_getNombre(pEmpleado,nombre);
       //printf("\n %s",nombre);
       fwrite(pEmpleado,sizeof(Employee),1,pArchivo);
       retorno= 0;

        }

    }
    fclose(pArchivo);

    return retorno;
}


void controller_init()
{

    int opcionMenu;
    LinkedList* listaEmpleados = ll_newLinkedList();


do{
    printf("\n Ingrese una Opcion: \n");
    printf("\n1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).");
    printf("\n2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).");
    printf("\n3. Alta de empleado ");
    printf("\n4. Modificar datos de empleado");
    printf("\n5. Baja de empleado");
    printf("\n6. Listar empleados  ");
    printf("\n7. Ordenar empleados");
    printf("\n8. Guardar los datos de los empleados en el archivo data.csv (modo texto). ");
    printf("\n9. Guardar los datos de los empleados en el archivo data.csv (modo binario).");
    printf("\n10. Salir\n");
    scanf("%d",&opcionMenu);

        switch(opcionMenu)
        {
            case 1:
            printf("\nSize de la lista %d", ll_len(listaEmpleados));
            controller_loadFromText("data.csv",listaEmpleados);
            printf("\nSize de la lista %d\n", ll_len(listaEmpleados));
            controller_ListEmployee(listaEmpleados);
            break;

            case 2:
                 controller_loadFromBinary("data.bin",listaEmpleados);
                break;
            case 3:
                if(controller_addEmployee(listaEmpleados)==0)
                {
                    printf("\n Se ha cargado con exito el empleado!! \n");
                }
                break;

            case 4:
                controller_editEmployee(listaEmpleados);
                break;
            case 5 :
                    controller_removeEmployee(listaEmpleados);
                    break;
            case 6 :
                    controller_ListEmployee(listaEmpleados);
                    break;
            case 7:
                    controller_sortEmployee(listaEmpleados);
                    break;
            case 8:
                    if (controller_saveAsText("data.csv", listaEmpleados) == 0)
                    {
                        printf("\nSe guardo lista existosamente\n");
                    }
                    else
                    {
                        printf("No hay ninguna lista cargada\n");
                    }
                    break;
            case 9 :
                    controller_saveAsBinary("data.bin",listaEmpleados);
                    break;
            case 10:
                    printf("\Saliendo! \n");
            default:
                    printf("\nOpcion no Valida!!!\n");

        }
    }while(opcionMenu!= 10);


    return 0;



}



