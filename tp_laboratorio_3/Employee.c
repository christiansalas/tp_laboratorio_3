#include "Employee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"
#include "utn.h"




Employee* Employee_new()
{
    Employee* this;
    this=malloc(sizeof(Employee));
    return this;
}

void Employee_delete(Employee* this)
{
    free(this);
}

Employee* Employee_newConParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* this;
    this=Employee_new();


    if(isValidSoloNumeros(idStr,10)==0&& utn_isValidNombre(nombreStr,128)==0
    && isValidSoloNumeros(horasTrabajadasStr,100)==0 && isValidSoloNumeros(sueldoStr,100)==0)
  // )
    {
      /*if(
    !Employee_setId(this,atoi(idStr))&&
    !Employee_setNombre(this,nombreStr)&&
    !Employee_setHorasTrabajadas(this,atoi(horasTrabajadasStr))&&
    !Employee_setSueldo(this,atoi(sueldoStr*/

        Employee_setId(this,atoi(idStr));
    Employee_setNombre(this,nombreStr);
    Employee_setHorasTrabajadas(this,atoi(horasTrabajadasStr));
    Employee_setSueldo(this,atoi(sueldoStr));

        return this;

    }


    Employee_delete(this);
    return NULL;
}

int Employee_setId(Employee* this,int id)
{
    int retorno=-1;
    static int proximoId=-1;

    if(this!=NULL && id==-1)
    {
        proximoId++;
        this->id=proximoId;
        retorno=0;
    }
    else if(id>proximoId)
    {
        proximoId=id;
        this->id=proximoId;
        retorno=0;
    }
    return retorno;
}

int Employee_getId(Employee* this,int* id)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *id=this->id;
        retorno=0;
    }
    return retorno;
}

int Employee_setNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        /*if (utn_isValidNombre(nombre,1024))
        {*/
            strncpy(this->nombre,nombre,128 /*strlen(nombre)*/);
            retorno=0;
        //}
    }
    return retorno;
}

int Employee_getNombre(Employee* this,char* nombre)
{
    int retorno=-1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}

int Employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno=-1;
    if(this!=NULL)
    {
        this->horasTrabajadas=horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int Employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *horasTrabajadas=this->horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int Employee_setSueldo(Employee* this,int sueldo)
{
    int retorno=-1;
    if(this!=NULL)
    {
        this->sueldo=sueldo;
        retorno=0;
    }
    return retorno;
}

int Employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno=-1;
    if(this!=NULL)
    {
        *sueldo=this->sueldo;
        retorno=0;
    }
    return retorno;
}

/** \brief Mostrar todos los empleados
 *
 * \param arrayy
 * \param
 * \return int
 *
 */
 int Employee_criterioSortEmpleados(void* thisA, void* thisB)
 {
   int retorno = 0;
   char nombreA[50];
   char nombreb[50];
   Employee_getNombre(thisA, nombreA);
   Employee_getNombre(thisA, nombreb);
   if(strcmp(nombreA, nombreb) > 0)
   {
        retorno = 1;
   }else if(strcmp(nombreA, nombreb) <0)
   {
        retorno = -1;
   }
    return retorno;
 }

 /**
* \brief    Se utiliza esta funcion para obtener un nuevo id
*           declarando una variable static para el id y suma 1 al anterior
* \return devuelve un id vacio
*/
int getNextId(LinkedList* pArrayListEmployee)
{
    static int ultimoId = -1;
    int i;
    int id;
    Employee * auxPunteroEmpleado;
    if(pArrayListEmployee != NULL)
    {
        for (i = 1; i<= ll_len(pArrayListEmployee); i++)
        {
            if(i == ll_len(pArrayListEmployee))
            {
                auxPunteroEmpleado = ll_get(pArrayListEmployee,i-1);
                Employee_getId(auxPunteroEmpleado, &id);
                ultimoId = id + 1;
            }
        }
    }
    return ultimoId;
}

/** \brief Busca empleado por Id
*
*
**/
int Employee_BuscarPorId (LinkedList * pArrayListEmployee, int id)
{
    int retorno = -1;
    int i;
    int bufferId;
    char bufferNombre[128];
    int bufferHorasTrabajo;
    int bufferSueldo;
    Employee * auxPunteroEmpleado;
    if (pArrayListEmployee != NULL && id >= 0)
    {
        for (i = 1; i< ll_len(pArrayListEmployee); i++)
        {
            auxPunteroEmpleado = ll_get(pArrayListEmployee,i);
            Employee_getId(auxPunteroEmpleado,&bufferId);
            if ( bufferId == id &&
                utn_getNombre(bufferNombre,128,"Modifique el nombre\n", "Nombre Invalido\n",3) ==0 &&
                utn_getEntero(&bufferHorasTrabajo,10,"Modifique las horas Trabajadas\n", "Horas invalidas\n",3) == 0 &&
                utn_getEntero(&bufferSueldo, 10, "Modifique el Sueldo\n","Sueldo invalido\n",3)==0)
            {
               Employee_setNombre(auxPunteroEmpleado,bufferNombre);
               Employee_setHorasTrabajadas(auxPunteroEmpleado, bufferHorasTrabajo);
               Employee_setSueldo(auxPunteroEmpleado,bufferSueldo);
               retorno = 0;
               break;
            }
        }
    }

    return retorno;
}

/** \brief Funcion que ordena por nombre
* \param thisA *void
* \param thisB *void
* \return retorna 1 si es de el primero es mayor al segundo y -1 alreves.
*/
int employee_criterioSortNombre(void* thisA,void* thisB)
{
    char nombreA[100];
    char nombreB[100];
    int retorno = 0;

    if(thisA != NULL && thisB != NULL)
    {
        Employee_getNombre(thisA,nombreA);
        Employee_getNombre(thisB,nombreB);
        if(strcmp(nombreA,nombreB) > 0)
        {
            retorno = 1;
        }
        else if(strcmp(nombreA,nombreB) < 0)
        {
           // printf("\nMENOR");
            retorno = -1;
        }
    }
    return retorno;
}
/** \brief Funcion que ordena por id
* \param thisA *void
* \param thisB *void
* \return retorna 1 si es de el primero es mayor al segundo y -1 alreves.
*/
int Employee_sortById(void* thisA,void* thisB)
{
    int idA;
    int idB;
    int retorno = 0;

    if(thisA != NULL && thisB != NULL)
    {
        Employee_getId(thisA, &idA);
        Employee_getId(thisB, &idB);
        if( idA > idB)
        {
            retorno = 1;
        }
        else if(idA < idB)
        {
            retorno = -1;
        }
    }
    return retorno;
}

