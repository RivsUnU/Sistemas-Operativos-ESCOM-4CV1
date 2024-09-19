#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {
    int i;
    printf("Ejecutando el programa invocador (abcd.c). Sus argumentos son:\n");
    for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
    sleep(10);
    printf("%s", argv[0]);
    strcpy(argv[0], "abcd");
    printf("%d", execv ("./abcd", argv));
    if (execv ("./abcd", argv) < 0) {
    printf("Error en la invocacion a execprog2\n");
    exit(1);
    
 };
    exit(0);
}

/*
Programa el cual mediante un arreglo 0 llama el nombre, despues hace una copia del arreglo argv y redirige haia el directorio del programa invocador "abcd", 
con execv buscara en el terminal un archivo (en este caso ejecutable al no contar con alguna extension) pero si el execv no encuentra el programa, te mandara el error
de la invocacion.











*/