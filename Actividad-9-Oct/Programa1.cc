#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define MAX_HILOS 4  // Número de hilos a usar

// Datos compartidos
int sumaTotal = 0;   // Suma total de los elementos del arreglo
sem_t semaforo;      // Semáforo para sincronización

// Estructura para pasar datos a cada hilo
typedef struct {
    int *arr;
    int start;
    int end;
} ThreadData;

// Función que ejecutará cada hilo
void* sumarParteArreglo(void* arg) {
    ThreadData* datos = (ThreadData*) arg;
    int sumaLocal = 0;

    // Cada hilo suma su parte del arreglo
    for (int i = datos->start; i < datos->end; i++) {
        sumaLocal += datos->arr[i];
    }

    // Bloqueamos con el semáforo antes de actualizar la suma total
    sem_wait(&semaforo);
    sumaTotal += sumaLocal;
    sem_post(&semaforo);  // Liberamos el semáforo

    pthread_exit(NULL);  // Finaliza el hilo
}

int main() {
    int n, i;
    int *arr;

    // Pedir el tamaño del arreglo
    printf("Introduce el número de elementos del arreglo: ");
    scanf("%d", &n);

    // Asignar memoria para el arreglo
    arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Llenar el arreglo con valores ingresados por el usuario
    printf("Introduce los %d elementos del arreglo:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Inicializamos el semáforo
    sem_init(&semaforo, 0, 1);

    // Crear hilos
    pthread_t hilos[MAX_HILOS];
    ThreadData datos[MAX_HILOS];
    int elementosPorHilo = n / MAX_HILOS;

    for (i = 0; i < MAX_HILOS; i++) {
        datos[i].arr = arr;
        datos[i].start = i * elementosPorHilo;
        datos[i].end = (i == MAX_HILOS - 1) ? n : (i + 1) * elementosPorHilo;

        // Crear el hilo
        pthread_create(&hilos[i], NULL, sumarParteArreglo, &datos[i]);
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < MAX_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir la suma total
    printf("La suma total es: %d\n", sumaTotal);

    // Destruir el semáforo
    sem_destroy(&semaforo);

    // Liberar la memoria
    free(arr);

    return 0;
}

/*EL programa hace una suma de los numeros dados como entrada
  Analizado por el equipo: Caldo de gallina - 4CV1
*/
