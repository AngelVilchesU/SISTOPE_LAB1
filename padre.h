#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "tda_lista.h"

void crearHijos(TDAlista *);

int aniosDocumento(char*);

void archivoIntermedioOrd(char*, int);