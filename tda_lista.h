#include <stdio.h>
#include <stdlib.h>

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
