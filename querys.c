#include "querys.h"

// Prototipo de las funciones static que se utilizan
static void ordenarAlfabeticamente(struct prov ** arreglo,int dim);
static void swap(struct prov ** arreglo,int inicial,int final);
static double porcentaje(size_t total,size_t x);
static void ordenarPorCantNacimientos(struct prov ** arreglo,int dim);

void query1(struct prov ** arreglo,int dim)
{
	Fichero archivoQuery1;
	archivoQuery1=fopen("query1.csv","w");

  ordenarAlfabeticamente(arreglo,dim);

	fprintf(archivoQuery1, "Provincia;Nacimientos\n");

	for (int i=0;i<dim;i++)
		fprintf(archivoQuery1, "%s;%ld \n",arreglo[i]->nombre,arreglo[i]->cantNacimientos);

	fclose(archivoQuery1);
}


int  query2(paisADT pais)
{
	int fils,cols,i;
	int **m=aniosAMatriz(pais,&fils,&cols);
	if (m==NULL)
		return 0;

	Fichero archivoQuery2;
	archivoQuery2=fopen("query2.csv","w");

	fprintf(archivoQuery2, "Anio;Varon;Mujer\n");
	for (i=0;i<fils;i++)
	{
			fprintf(archivoQuery2, "%d;%d;%d\n",m[i][0],m[i][1],m[i][2]);
			free(m[i]);
	}
	free(m);
	fclose(archivoQuery2);
	return 1;
}


void query3(struct prov  ** arreglo,int dim,paisADT pais)
{
	size_t total=cantidadNacimientos(pais);

	Fichero archivoQuery3;
	archivoQuery3=fopen("query3.csv","w");
	fprintf(archivoQuery3,"Provincia;Porcentaje\n");

	ordenarPorCantNacimientos(arreglo,dim);

	for (int i=0;i<dim;i++)
	{
		fprintf(archivoQuery3,"%s;%.2g%%\n",arreglo[i]->nombre,porcentaje(total,arreglo[i]->cantNacimientos));
	}

	fclose(archivoQuery3);
}


static void swap(struct prov ** arreglo,int inicial,int final)
{
	struct prov *aux;
	aux=arreglo[inicial];
	arreglo[inicial]=arreglo[final];
	arreglo[final]=aux;
}

static double porcentaje(size_t total,size_t x)
{
	return (x*100)/(double)total;
}

static void ordenarPorCantNacimientos(struct prov ** arreglo,int dim)
{
	int i,j;
	for (i=0;i<dim;i++)
	{
		for (j=dim-1;j>0;j--)
		{
			if (arreglo[j]->cantNacimientos > arreglo[j-1]->cantNacimientos)
			{
				swap(arreglo,j,j-1);
			}
			else if ( arreglo[j]->cantNacimientos == arreglo[j-1]->cantNacimientos)
				if (strcmp(arreglo[j]->nombre,arreglo[j-1]->nombre)<0)
					swap(arreglo,j,j-1);
		}
	}
}

static void ordenarAlfabeticamente(struct prov ** arreglo,int dim)
{
	int i,j;

	for (i=0;i<dim;i++)
	{
		for (j=dim-1;j>0;j--)
		{
			if (strcmp(arreglo[j]->nombre,arreglo[j-1]->nombre) < 0)
			{
				swap(arreglo,j,j-1);
			}
		}
	}
}
