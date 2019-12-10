#include "paisADT.h"
#include "lectura.h"
#include "querys.h"
#include <time.h>

int main(int argc, char const *argv[])
{
	if(argc!=3)
	{
		printf("Uso 2 archivos.csv #ARCHIVO_NACIMIENTOS #ARCHIVO_PROVINCIAS\n");
		return 1;
	}
	paisADT argentina=generaPais();

	printf(">Cargando datos.\n\n\n");
	cargaDatosProvincias(argv[2],argentina);

	cargarDatosNacimientos(argv[1],argentina);
	printf("Carga completada.\n");

	int dim=0;
	struct prov ** arreglo;
		if ((arreglo=aArreglo(argentina,&dim))!=NULL)
		{
			query1(arreglo,dim);
			printf("Query 1 finalizado!\n");
			query3(arreglo,dim,argentina);
			printf("Query 3 finalizado!\n");
		}
		else //si aArreglo devuelve NULL es por que no pudo alocar memoria
		{
			printf("No se pudieron realizar querys 1 y 3.\n");
		}


	printf("Query 2 %s \n",query2(argentina)? "finalizado!":"no se pudo realizar.");
	
	// Se liberan los recursos utilizados
	for (int i=0;i<dim;i++)
	{
		free(arreglo[i]->nombre);
		free(arreglo[i]);
	}
	free(arreglo);
	freePais(argentina);

	return 0;
}
