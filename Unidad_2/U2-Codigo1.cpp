//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Ejemplo 1
//Fecha: 17/Septiembre/2024
//Explicación:  Este programa crea dos hilos paralelos, uno que realiza la suma y otro la multiplicación de los mismos números (2 y 3), y luego imprime los resultados en la consola.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *sumar(void*arg){    //Funcion sumar para hilo 1
    int a=2, b=3;
    int resultado= a+b;
    printf("La suma de %d y %d es: %d\n", a, b, resultado);
    pthread_exit(NULL);
    return 0;
}

void *multiplicar(void*arg){ // funcion multiplicar para hilo 2
    int a=2, b=3;
    int resultado = a*b;
  printf("El producto de %d y %d es: %d", a, b, resultado);
    pthread_exit(NULL);
    return 0;

}

int main() {
  // ID'S Hilos
    pthread_t hiloSuma, hiloMultiplicacion;

    if (pthread_create(&hiloSuma, NULL, sumar, NULL) != 0) {
        perror("Error al crear el primer hilo"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }


    if(pthread_create(&hiloMultiplicacion, NULL, multiplicar, NULL) !=0) { //condicional para detectar error de creacion de hilos.
      perror("Error al crear el segundo hilo"); // Imprimir error si falla la creación del hilo
      exit(EXIT_FAILURE);
    }



    pthread_join(hiloSuma, NULL);   // Esperar a que el hilo con el ID correspondiente termine
    pthread_join(hiloMultiplicacion, NULL);

    return 0;
}
