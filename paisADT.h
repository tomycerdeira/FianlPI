#ifndef PAIS
#define PAIS
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#define VARON 1
#define MUJER 2
#define GENEROS 2

/*"Se asume que el formato y contenido de los archivos es correcto"*/


typedef struct paisCDT * paisADT;

/* Le brindamos acceso a esta estructura al usuario para que pueda manejar una copia de la informacion obtenida */
struct prov
{
	char *nombre;
	size_t cantNacimientos;
	int codigo;
};

/*Crea la estructura que dara soporte al almacenamiento de datos*/
paisADT generaPais();


/* Libera todos los recursos reservados por el TAD */
void freePais(paisADT pais);


/*Suma un nacimiento al total del pais, su respectiva provincia dada por "codigoProv" y un nacimiento de "genero" a "anioAgregar", retorna 1 si pudo agregarlo, 0 si no*/
int  agregarNacimiento(paisADT pais,int codigoProv,int anioAgregar,int genero);


/*Almacena en un matriz los datos de los anios que se leyeron. En la primer columna se almacena el anio correspondiente, en la segunda se almacena
la cantidad de nacimientos de varones y en la tercera los de las mujeres.*/
int ** aniosAMatriz(paisADT pais,int *filas,int *cols);


/*Retorna la cantidad de provincias que se cargaron */
int cantidadDeProvincias(paisADT pais);


/*Retorna la cantidad de nacimientos en el pais*/
int cantidadNacimientos(paisADT pais);


/*Almacena de forma ascendente las provincias leidas del string s segun su codigo.Aumentando la cantidad de provincias total.*/
int cargarPaisProvincias(paisADT pais,char * entrada); // Devuelve si hubo error o no.


/*Copia a un arreglo los datos de cada provincia con el orden establecido por la funcion "cargarPaisProvincias"; guardando en el paremetro dim la dimension del mismo.*/
struct prov ** aArreglo(paisADT pais,int *dim);
#endif
