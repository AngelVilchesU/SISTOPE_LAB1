#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    char *palabra = "5000";
    char string[100];
    FILE *archivo = fopen("datos_juegos.csv", "r");
    int pos;
    int temp;
    int anteriorSalto = 0;
    long t = 261;
    /*
    11111,1111 \n <-
    1515665,5000 \n
    kjkjzxkc,1651
    */
    while (fgets(string, 100, archivo) != NULL)
    {
        //printf("%s \n", string);
        if (strstr(string, palabra) != 0)
        {
            //printf("Encontro el año\n");
            //temp = ftell(archivo);
            pos = anteriorSalto;
            printf("%d\n", temp);
            // printf("%s \n",string);
        }
        anteriorSalto = ftell(archivo);
    }

    printf("%d\n", pos);
    fseek(archivo, pos, SEEK_SET);
    fgets(string, 100, archivo);
    printf("STRING SETEADO: %s\n", string);

    return 0;
}
