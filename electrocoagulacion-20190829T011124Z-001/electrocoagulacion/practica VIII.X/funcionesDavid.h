#ifndef FUNCIONES_DAVID
#define	FUNCIONES_DAVID
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include "funcionesDavid.c"

void ledestado(int tiempoled);
void enviarTrama(char *datos);
void enviarTramaSE(char *datos);
int conversionADMues(int canal);

