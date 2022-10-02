#include "hijo.h"

void calculos(TDAlista *lista)
{

    int cantNodos = nroNodosLista(lista);
    char str[cantNodos][300];

/*
    while (!esListaVacia(lista))
    {
        int pos = retornarDato(lista);
        printf("pos: %d\n", pos);
        eliminarInicio(lista);
        char linea[300];

        FILE *dctoInt = fopen("archivo_intermedio.csv", "r");
        if (dctoInt == NULL)
        {
            printf("intermediate file read error\n");
            exit(-1);
        }
        else
        {
            fseek(dctoInt, pos, SEEK_SET);
            fgets(linea, 300, dctoInt);
            
            printf("%s\n", linea);

        }
        
        fclose(dctoInt);
        

        
    }
    */

    for (int i = 0; i < cantNodos; i++){
        int pos = retornarDato(lista);
        printf("pos: %d\n", pos);
        eliminarInicio(lista);
        char linea[300];

        FILE *dctoInt = fopen("archivo_intermedio.csv", "r");
        if (dctoInt == NULL)
        {
            printf("intermediate file read error\n");
            exit(-1);
        }
        else
        {
            fseek(dctoInt, pos, SEEK_SET);
            fgets(linea, 300, dctoInt);
            printf("%s\n", linea);
            strcpy(str[i], linea);
        }
        fclose(dctoInt);
    }

    for (int i = 0; i < cantNodos; i++)
    {
        printf("Linea: %s", str[i]);
    }
    
    exit(printf("FINALIZADA LA TAREA DEL HIJO\n"));
}

/*//////////////////////////////////////////////////////////////////////////*/

TDAlista *crearListaVacia()
{
    TDAlista *lista = (TDAlista *)malloc(sizeof(TDAlista));
    lista->inicio = NULL;
    return lista;
}

void liberarLista(TDAlista *lista)
{
    free(lista);
}

void insertarInicio(TDAlista *lista, int dato)
{
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->puntero = lista->inicio;
    lista->inicio = nuevo;
}

int esListaVacia(TDAlista *lista)
{
    if (lista->inicio == NULL)
        return 1;
    else
        return 0;
}

void recorrerLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            printf("%d ", auxiliar->dato);
            auxiliar = auxiliar->puntero;
        }
        printf("\n");
    }
    else
        printf("La lista está vacía\n");
}

int retornarDato(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        nodo *auxiliar = lista->inicio;
        int dato = auxiliar->dato;
        auxiliar = auxiliar->puntero;
        return dato;
    }
    else
    {
        return -1;
    }
    return -1;
}

void eliminarInicio(TDAlista *lista)
{
    nodo *auxiliar;
    if (!esListaVacia(lista))
    {
        auxiliar = lista->inicio;
        lista->inicio = lista->inicio->puntero;
        free(auxiliar);
    }
}

int nroNodosLista(TDAlista *lista)
{
    if (!esListaVacia(lista))
    {
        int nroNodos = 0;
        nodo *auxiliar = lista->inicio;
        while (auxiliar != NULL)
        {
            auxiliar = auxiliar->puntero;
            nroNodos++;
        }
        return nroNodos;
    }
    return 0;
}