#include "lectura.h"

void cargaDatosProvincias(const char * archivo,paisADT pais)
{
	Fichero ArchivoProvs;
	ArchivoProvs=fopen(archivo,"r");
	char entrada[MAXLINE];

	//Salteamos los encabezados que por enunciado se asumen validos.
	fgets(entrada,MAXLINE,ArchivoProvs);

	//Cargamos los datos de las provincias al TAD
  //cargarPaisProvincias devuelve 0 si no hay mas memoria
  char *aux;
	while ((aux=fgets(entrada,MAXLINE,ArchivoProvs)) && cargarPaisProvincias(pais,entrada));

	fclose (ArchivoProvs);
	// si aux es distinto de NULL quiere decir que cargarPaisProvincias fallo y no hay nada que se pueda hacer
    if (aux!=NULL)
    {
       exit(1);
    }
}

void cargarDatosNacimientos(const char *archivoNacimientos, paisADT pais)
{
  Fichero ArchivoNac;
  ArchivoNac=fopen(archivoNacimientos,"r");
  char entrada[MAXLINE];

  int codigoProv,genero,anio,tipoParto;
  //Salteamos los encabezados que por enunciado se asumen validos.
  fgets(entrada,MAXLINE,ArchivoNac);
	char *aux;
	int flag=1;
  while ((aux=fgets(entrada,MAXLINE,ArchivoNac))&& flag)
  {
    sscanf(entrada,"%4d,%2d,%1d,%1d,",&anio,&codigoProv,&tipoParto,&genero);//
    	if (!agregarNacimiento(pais,codigoProv,anio,genero))
						flag=0;
  }

	  fclose(ArchivoNac);
		
	// si aux es distinto de NULL quiere decir que agregarNacimiento fallo y no hay nada que se pueda hacer
		if (aux!=NULL)
		{
			 exit(1);
		}
}
