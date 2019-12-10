 #include "paisADT.h"
#define BLOQUE 10
struct paisCDT
{
    size_t totalNacidos;
    struct prov ** Provincias; //arreglo que contiene la informacion de las provincias
    size_t totalProvincias;
    size_t dim; // es la cantidad de memoria reservada para el arreglo de "Provincias"
    struct an * PrimerAnio;
    int cantAnios; // almacena la cantidad de anios que se analizan
};

/* Lista que dara soporte a los nacidos por anio */
struct an
{
    struct  an *  siguiente;
    int anio;
    size_t varon;
    size_t mujer;
};


static int  compara(int anio,int anioAgregar)
{
    return (anio-anioAgregar);
}

paisADT generaPais()
{
  paisADT pais;
   if ((pais=calloc(1,sizeof(struct paisCDT)))==NULL)
       fprintf(stderr, "Valor de errno: %d Error %s \nNo se pude generar el pais\n",errno,strerror(errno));

     return pais;
}

/* valida si el genero es correcto y se lo asigna al anio correspondiente */
static void agregaGenero(struct an * actual,int  genero)
{
    if (genero ==VARON)
        actual->varon+=1;
    else if (genero==MUJER)
        actual->mujer+=1;
}

/* genera la lista en la que cada "anio" contiene la cantidad de nacimientos separados por generos */
static struct an * agregarNacimientoAnioRec(struct an * anio,int anioAgregar,int  genero,paisADT pais,int * flag )
{
    int c;
    if (anio==NULL || (c=compara(anio->anio,anioAgregar))<0)// compara devuelve negativo si el anio a agregar es mayor al que se esta comparando
    {
        struct an * nuevo;
        if ((nuevo=calloc(1,sizeof(struct an)))==NULL)
        {
          fprintf(stderr, "Valor de errno: %d Error %s \n",errno,strerror(errno));
          freePais(pais);
          *flag=0;
        }
        else
        {
          nuevo->anio=anioAgregar;
          agregaGenero(nuevo,genero);
          nuevo->siguiente=anio;
          pais->cantAnios+=1;
        }
        return nuevo;
    }
    if (c==0)
    {
        agregaGenero(anio,genero);
        return anio;
    }

    anio->siguiente=agregarNacimientoAnioRec(anio->siguiente,anioAgregar,genero,pais,flag);

    return anio;
}

static void freeRec(struct an * anio)
{
  if (anio==NULL)
  return;
  freeRec(anio->siguiente);
  free(anio);
}

static void freeProv(paisADT pais)
{
	for (int i=0;i<pais->totalProvincias ;i++)
  {
    free(pais->Provincias[i]->nombre);
		free(pais->Provincias[i]);
  }
	free(pais->Provincias);
}

void freePais(paisADT pais)
{
	freeProv(pais);
  freeRec(pais->PrimerAnio);
  free(pais);
}

 //Se implementa el algoritmo de busqueda binaria para sumar nacimientos a las provincias
static void agregarNacimientoProv(struct prov ** Provincias,int codigo,int dim)
{
	if (Provincias[dim/2]->codigo == codigo )
	{
		Provincias[dim/2]->cantNacimientos++;

	}
	 else if (Provincias[dim/2]->codigo > codigo )
		agregarNacimientoProv(Provincias,codigo,(dim+1)/2);
	else
    agregarNacimientoProv(Provincias+dim/2,codigo,(dim+1)/2);
}


 int agregarNacimiento(paisADT pais,int codigoProv,int anioAgregar,int genero)
{
    pais->totalNacidos+=1;
    int flag=1;// si se cambia flag es por que no se pudo agregar el nacimiento
 	  agregarNacimientoProv(pais->Provincias,codigoProv,pais->totalProvincias);
    pais->PrimerAnio=agregarNacimientoAnioRec(pais->PrimerAnio,anioAgregar,genero,pais,&flag);
    return flag;
}


int ** aniosAMatriz(paisADT pais,int *filas,int *cols)
{
  int ** matriz;
  if ((matriz=calloc(1,sizeof(int *)*(pais->cantAnios+1)))==NULL)
  {
    fprintf(stderr, "Valor de errno: %d:Error %s \nNo se pudo crear matriz.\n",errno,strerror(errno));

  }
  else
  {
       struct an * aux=pais->PrimerAnio;
       int *aux2;
      for (int j=pais->cantAnios-1;j>=0;j--)
      {
          if ((aux2=realloc(matriz[j],(GENEROS+1)*sizeof(int)))== NULL)
          {
              fprintf(stderr, "Valor de errno: %d:Error %s \nNo se pudo crear matriz.\n",errno,strerror(errno));
            /* Si no hay memoria no hay nada que se pueda hacer, se liberan todos los recursos que se usaron hasta el momento */
              for (int i=0;i<j- pais->cantAnios ;i++)
                free(matriz[j]);
              free(matriz);
              return NULL;
          }
          matriz[j]=aux2;
          matriz[j][0]=aux->anio;
          matriz[j][1]=aux->varon;
          matriz[j][2]=aux->mujer; ///// FIJARSE DE COMENTAR ALGO ACA
          aux=aux->siguiente;
      }
  }
    *filas=pais->cantAnios;
    *cols=GENEROS+1;
    return matriz;
}

int cantidadDeProvincias(paisADT pais)
{
  return pais->totalProvincias;
}


int cantidadNacimientos(paisADT pais)
{
  return pais->totalNacidos;
}

/* se encarga de manejar los errores ocasionados al cargar las provincias */
static int errorProvincia(paisADT pais,int error)
{
  fprintf(stderr, "Valor de errno: %d:Error %s \nNo se pudieron cargar las provincias.\n",errno,strerror(errno));
  freePais(pais);
  return 0;
}

/* se asume que en el string "entrada" su marca de final es \n  (condicion necesaria)*/
int cargarPaisProvincias(paisADT pais,char * entrada)
{
	char *token;
  int errnum;
  struct prov ** aux2;
  if (pais->totalProvincias %BLOQUE ==0)
  {
      if ((aux2=realloc(pais->Provincias,(pais->totalProvincias+BLOQUE)*sizeof(struct prov *))) == NULL)
      {
        errnum=errno;
        return errorProvincia(pais,errnum);
      }
  		pais->Provincias=aux2;
  		pais->dim+=BLOQUE;
  }

  if((pais->Provincias[pais->totalProvincias]=calloc(1,sizeof(struct prov)))==NULL)
  {
      errnum=errno;
      return errorProvincia(pais,errnum);
  }

  token=strtok(entrada,",\n");
  pais->Provincias[pais->totalProvincias]->codigo=atoi(token);
  token=strtok(NULL,",\n");

  if ((pais->Provincias[pais->totalProvincias]->nombre=malloc(sizeof(char)*(strlen(token)+1)))==NULL)
  {
      errnum=errno;
      return errorProvincia(pais,errnum);
  }
  strcpy(pais->Provincias[pais->totalProvincias]->nombre,token);
      /* se elimina el \n que copia al final */
  pais->Provincias[pais->totalProvincias]->nombre[strlen(token)-1]=0;

  pais->totalProvincias++;
  		//Ordenamos el arreglo en funcion de los codigos de forma ascendente
  struct prov * aux;
  	// leemos los datos asi por que
  int esMenor=1;
  for (int j=pais->totalProvincias-1;j>0 && esMenor;j--) 			//Si falla en algun lado, ver esto
  	{
  		if (pais->Provincias[j]->codigo < pais->Provincias[j-1]->codigo)
  			{
  				aux=pais->Provincias[j];
  				pais->Provincias[j]=pais->Provincias[j-1];
  				pais->Provincias[j-1]=aux;
  			}
  		else
  				esMenor=0;
  	}
  return 1;
}

struct prov ** aArreglo(paisADT pais,int *dim)
{
	*dim=pais->totalProvincias;
	struct prov ** arreglo;
	if ((arreglo=malloc(sizeof(struct prov *)*(*dim)))== NULL)
  {
    fprintf(stderr, "Valor de errno: %d:Error %s\nNo se pudo crear arreglo\n",errno,strerror(errno));
  }
  else
  {
	   for (int i=0;i<*dim;i++)
	   {                   /*Asigna memoria para cada estructura del arreglo, si no hay memoria libera los recursos que se usaron y devuelve NULL*/
		    if ((arreglo[i]=malloc(sizeof(struct prov)))==NULL ||  (arreglo[i]->nombre=malloc(sizeof(char)*(strlen(pais->Provincias[i]->nombre)+1)))==NULL )
        {
          fprintf(stderr, "Valor de errno:%d.Error %s \nNo se pudo crear arreglo\n",errno,strerror(errno));
          for (int j=0;j<i;j++)
          {
            free(arreglo[i]->nombre);
            free(arreglo[i]);
          }
          free(arreglo);
          return NULL;
        }

		    arreglo[i]->codigo=pais->Provincias[i]->codigo;
		    strcpy(arreglo[i]->nombre,pais->Provincias[i]->nombre);
		    arreglo[i]->cantNacimientos=pais->Provincias[i]->cantNacimientos;
	   }
  }
	return arreglo;
}
