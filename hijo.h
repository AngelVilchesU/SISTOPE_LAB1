#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

////////////////// Estructura de Datos ///////

// Estructura cuyo dato corresponde a la posición de la línea del archivo que el hijo debe
// evaluar por concepto de lógica de solución
typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* puntero;
}nodo;

// Cabecera de la estructura anterior con la cual se realiza una lista enlazada
typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;

/*------------- operaciones -------------*/

TDAlista* crearListaVacia();

void liberarLista(TDAlista* );

void insertarInicio(TDAlista*, int);

int esListaVacia(TDAlista* );

int retornarDato(TDAlista* );

char** calculos(TDAlista* );

void eliminarInicio(TDAlista* );

int nroNodosLista(TDAlista * );