//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Ejemplo 4
//Fecha: 17/Septiembre/2024
// este programa guarda en los hilos los mensajes que se escriben y los imprime desde los hilos

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Estructura para pasar multiples argumentos a la funcion del hilo
typedef struct {
    int thread_id;
    char message[100];
} ThreadArgs;

// Funcion que sera ejecutada por cada hilo ligero
void *funcion_hilo_ligero(void *arg) {
    ThreadArgs *thread_args = (ThreadArgs *)arg;

    // Imprimir el mensaje ingresado por el usuario y el ID del hilo
    printf("Mensaje desde hilo %d: %s\n", thread_args->thread_id, thread_args->message);

    pthread_exit(NULL); // Terminar el hilo ligero
}

int main() {
    pthread_t hilos[2]; // Array para almacenar los identificadores de los hilos ligeros
    ThreadArgs args[2]; // Array de estructuras para pasar argumentos a los hilos

    // Crear y configurar argumentos para cada hilo
    for (int i = 0; i < 2; i++) {
        args[i].thread_id = i + 1; // Asignar el ID del hilo

        // Solicitar al usuario ingresar un mensaje para cada hilo
        printf("Escribe mensaje para hilo %d: ", args[i].thread_id);
        fgets(args[i].message, sizeof(args[i].message), stdin); // Leer el mensaje desde la entrada estandar
    }

    // Crear hilos ligeros y pasar las funciones junto con los argumentos
    for (int i = 0; i < 2; i++) {
        pthread_create(&hilos[i], NULL, funcion_hilo_ligero, (void *)&args[i]); // Crear un nuevo hilo ligero
    }

    // Esperar la finalizacion de los hilos ligeros
    for (int i = 0; i < 2; i++) {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo ligero con el ID correspondiente termine
    }

    // Imprimir mensaje del hilo principal
    printf("Hilo principal: Todos los hilos han terminado su ejecucion.\n");

    return 0;
}
