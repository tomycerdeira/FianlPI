# Uso

```
make
./nacidos ARCHIVO_NACIMIENTOS ARCHIVO_PROVINCIAS
```

Los archivos generados por el ejecutbale se crean en el mismo directorio en donde se encuentra el mismo.

# Descripcion Funcional

La funcion del programa creado es la lectura y el ordenamiento de ARCHIVO_NACIMIENTOS en base a distintos criterios llamados "querys";

# Información disponible

nacimientos.csv:
- AN: anio de nacimiento.
- PROVRES: codigo de la provincia de residencia habitual de la madre.
- SEXO: codigo de sexo del nacido vivo. (1=Varon;2=Mujer;9=SinEspecificar).
- IMEDAD: intervalo de edad de la madre.
- IMINSTRUC: nivel maximo de intruccion alcanzado por la madre.
- IPESONAC: intervalo de peso al nacer.
(para detalles extra, revisar documentacion entregada por la catedra)


provincias.csv:
- CODIGO: entero positivo de dos digitos.
- VALOR: nombre de la provincia.

```
Se asume que el formato y contenido de los archivos es correcto.
```

# Querys solicitados

Query 1: Nacimientos por provincia. Imprime "nombreProvinica ; cantidadNacimientos".

Query 2: Nacimientos por anio y por sexo. Imprime "anio ; cantSexoVaron ; cantSexoMujer".

Query 3: Porcentaje de nacimientos por provincia. Imprime "nombreProvincia ; porcentajeDeNacimientos".


# TAD
## Estructuras usadas
### paisCDT
    size_t totalNacidos;
    struct prov ** Provincias;
    size_t totalProvincias;
    size_t dim; //Es la cantidad de memoria reservada para Provincias.
    struct an * PrimerAnio;
    int cantAnios; //Almacena la cantidad de anios que se analizan.

### prov
    char *nombre;
    size_t cantNacimientos;
    int codigo;

### an
    struct  an *  siguiente;
    int anio;
    size_t varon;
    size_t mujer;

# Mapa de funciones

FRONTEND: main.c, lectura.c, querys.c

BACKEND: paisADT.c

## main.c
~ newPais(); (paisADT.c)

~ cargaDatosProvincias(); (lectura.c)

~ cargarDatosNacimientos(); (lectura.c)

~ aArreglo(); (paisADT.c)

~ query1(); (querys.c)

~ query2(); (querys.c)

~ query3(); (querys.c)

~ freePais(); (paisADT.c)

## paisADT.c

~ paisADT generaPais();

~ void freePais(paisADT pais);
- freeProv(paisADT pais);
- freeRec(struct an * anio);
- free();

~ int agregarNacimiento(paisADT pais,int codigoProv,int anioAgregar,int genero);
- agregaNacimientoProv(struct prov ** provincia, int codigo, int dim);
^ errorProvincias(paisADT pais,int error);
- agregarNacimientoAnioRec(struct an * anio, int anioAgregar, int genero, paisADT pais,int *flag);
^ compara(int anio, int anioAgregar);
^ AgregaGenero(struct an * actual, int genero);
^ freePais(paisADT pais);


~ int ** aniosAMatriz(paisADT pais,int *filas,int *cols);

~ int cantidadDeProvincias(paisADT pais);

~ int cantidadNacimientos(paisADT pais);

~ void cargarPaisProvincias(paisADT pais,char * entrada);
- freePais(paisADT pais);

~ struct prov ** aArreglo(paisADT pais, int *dim);

## queries.c

~ void query1(struct prov ** arreglo, int dim);
  - ordenarAlfabeticamente(struct prov ** arreglo, int dim);
  ^ swap(struct prov ** arreglo, int inicial, int final);

~ int query2(paisADT pais);
  - aniosAMatriz(); (paisADT.c)

~ void query3(struct prov ** arreglo, int dim, paisADT pais);
  - cantidadNacimientos(); (paisADT.c)
  - ordenarPorCantNacimientos(struct prov ** arreglo, int dim);
  - porcentaje(size_t total, size_t x);

## lectura.c

~ void cargaDatosProvincias(const char * archivo, paisADT pais);
- cargarPaisProvincias(paisADT pais, char * entrada;

~ void cargarDatosNacimientos(const char *archivoNacimientos, paisADT pais);
- agregarNacimiento(paisADT pais, int codigoProv, int anio, int genero);
