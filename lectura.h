#ifndef LECTURA
#define LECTURA
#include "paisADT.h"
#define MAXLINE 200

/*"Se asume que el formato y contenido de los archivos es correcto"*/

typedef FILE * Fichero;

void cargaDatosProvincias(const char * archivo, paisADT pais);
void cargarDatosNacimientos(const char * archivoNacimientos, paisADT pais);

#endif
