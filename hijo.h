#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

/*------------- estructura de datos -------------*/

typedef struct nodoGenerico
{
  int dato;
  struct nodoGenerico* puntero;
}nodo;

typedef struct listaGenerica
{
  nodo* inicio;
}TDAlista;

/*------------- operaciones -------------*/

TDAlista* crearListaVacia();

void liberarLista(TDAlista* );

void insertarInicio(TDAlista*, int);

int esListaVacia(TDAlista* );

void recorrerLista(TDAlista* );

int retornarDato(TDAlista* );

void calculos(TDAlista* );

void eliminarInicio(TDAlista* );

int nroNodosLista(TDAlista * );