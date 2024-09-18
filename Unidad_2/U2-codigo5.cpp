//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Ejemplo 5
//Fecha: 17/Septiembre/2024
// este programa guarda los numeros del arreglo e imprime la suma de todos sus numeros naturales de cada uno
#include <stdio.h>
#include <pthread.h>

// Funcion que sera ejecutada por cada hilo pesado para calcular la suma de los primeros n numeros naturales
void *calcular_suma(void *arg) {
    int n = *((int *) arg);
    int suma = 0;

    // Calcular la suma de los primeros n numeros naturales
    for (int i = 1; i <= n; i++) {
        suma += i;
    }

    // Imprimir el resultado calculado por el hilo
    printf("Hilo pesado: La suma de los primeros %d numeros naturales es %d\n", n, suma);

    pthread_exit(NULL); // Terminar el hilo pesado
}

int main() {
    pthread_t hilos[3]; // Array para almacenar los identificadores de los hilos pesados
    int numeros[] = {3, 30, 12}; // Array de numeros para cada hilo pesado

    // Crear hilos pesados y pasar los numeros para el calculo de la suma
    for (int i = 0; i < 3; i++) {
        pthread_create(&hilos[i], NULL, calcular_suma, (void *) &numeros[i]); // Crear un nuevo hilo pesado
    }

    // Esperar la finalizacion de los hilos pesados
    for (int i = 0; i < 3; i++) {
        pthread_join(hilos[i], NULL); // Esperar a que el hilo pesado con el ID correspondiente termine
    }

    printf("Hilo principal: Todos los calculos de sumas han terminado.\n");

    return 0;
}
