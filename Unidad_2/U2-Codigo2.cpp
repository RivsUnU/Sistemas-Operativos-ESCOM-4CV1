//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Ejemplo 2 Hilos asincronos
//Fecha: 17/Septiembre/2024
//Explicación:Este código crea dos hilos que se ejecutan en paralelo. El primer hilo imprime una serie de cinco mensajes secuenciales, mientras que el segundo hilo imprime diez mensajes numerados. Debido a la ejecución paralela,
//los mensajes de ambos hilos pueden aparecer mezclados en la salida. El programa espera a que ambos hilos terminen antes de mostrar un mensaje final.

#include <stdio.h>                            // Librería de entrada y salida estándar
#include <pthread.h>                          // Librería POSIX

// Apartado de funciones

void* funcionHilo1(void* arg) { // Funcion para primer hilo

        printf("Hilo 1: Mensaje 1\n");      // Impresión en pantalla de mensajes del primer hilo de manera lineal
        printf("Hilo 1: Mensaje 2\n");
        printf("Hilo 1: Mensaje 3\n");
        printf("Hilo 1: Mensaje 4\n");
        printf("Hilo 1: Mensaje 5\n\n");
          return NULL;
    }




void* funcionHilo2(void* arg) { // Función que se ejecutará en el segundo hilo
    for (int i = 1; i <= 10; i++) {               // Ciclo for inicializado en 2 con condición de paro cuando el contador es mayor a 10 evitando generacion lineal o manual
        printf("Hilo 2: Mensaje %d\n", i);      // Impresión en pantalla de mensajes del segundo hilo asistido por el for
    }
    return NULL;                              // Finalizacion
}

int main() {
    // ID'S Hilos
    pthread_t hilo1, hilo2;                              // Se declaran 2 estructuras de datos con pthread_t

    // Creación de hilos
    pthread_create(&hilo1, NULL, funcionHilo1, NULL);   //Hilo 1
    pthread_create(&hilo2, NULL, funcionHilo2, NULL);   // Hilo2

    // Espera a que los hilos terminen su ejecución si no, no ejecuta el programa
    pthread_join(hilo1, NULL);                          // Se espera a que hilo1 termine su ejecución
    pthread_join(hilo2, NULL);                          // Se espera a que hilo2 termine su ejecución

    printf("\nVamos hilos de Caldo de gallina!\n");  // Impresión de seguridad

    return 0;
}
