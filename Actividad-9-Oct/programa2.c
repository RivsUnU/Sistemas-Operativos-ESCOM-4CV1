 // Codigo modificado por el equipo Caldo de Gallina - Agregando Semaforos, Mutex, Hilos, Tuberias. Swap, Algoritmos de planificacion, Memoria.


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_HILOS 4  // Número de hilos a usar
#define TIME_QUANTUM 2  // Tiempo máximo para cada hilo en el algoritmo de planificación

// Semáforo para sincronizar el acceso a sumaTotal
sem_t semaforo;

// Datos compartidos
int sumaTotal = 0;   // Suma total de los elementos del arreglo

// Estructura para pasar datos a cada hilo
typedef struct {
    int *arr;
    int start;
    int end;
    int pipefd[2];  // Tubo para la comunicación entre hilos
} ThreadData;

// Función que ejecutará cada hilo
void* sumarParteArreglo(void* arg) {
    ThreadData* datos = (ThreadData*) arg;
    int sumaLocal = 0;

    // Cada hilo suma su parte del arreglo
    for (int i = datos->start; i < datos->end; i++) {
        sumaLocal += datos->arr[i];
        usleep(50000);  // Simula una operación lenta
    }

    // Escribir la suma parcial en la tubería
    write(datos->pipefd[1], &sumaLocal, sizeof(sumaLocal));

    pthread_exit(NULL);  // Finaliza el hilo
}

// Planificador Round Robin
void planificador(int hilosActivos[], int n) {
    int i = 0;
    while (n > 0) {
        if (hilosActivos[i] > 0) {
            sleep(TIME_QUANTUM);  // Simula el tiempo que el hilo está en ejecución
            hilosActivos[i]--;
            if (hilosActivos[i] == 0) {
                n--;
            }
        }
        i = (i + 1) % MAX_HILOS;  // Mover al siguiente hilo
    }
    
}

int main() {
    clock_t inicio, fin;
    double tiempo;
    int n, i;
    int *arr;


    inicio = clock();
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

    // Inicializar el semáforo
    sem_init(&semaforo, 0, 1);

    // Crear tubería
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("Error al crear la tubería");
        return 1;
    }

    // Crear hilos
    pthread_t hilos[MAX_HILOS];
    ThreadData datos[MAX_HILOS];
    int elementosPorHilo = n / MAX_HILOS;
    int hilosActivos[MAX_HILOS] = {1, 1, 1, 1}; // Simula la carga para Round Robin

    for (i = 0; i < MAX_HILOS; i++) {
        datos[i].arr = arr;
        datos[i].start = i * elementosPorHilo;
        datos[i].end = (i == MAX_HILOS - 1) ? n : (i + 1) * elementosPorHilo;
        datos[i].pipefd[0] = pipefd[0];
        datos[i].pipefd[1] = pipefd[1];

        // Crear el hilo
        pthread_create(&hilos[i], NULL, sumarParteArreglo, &datos[i]);
    }

    // Planificar la ejecución de los hilos usando Round Robin
    planificador(hilosActivos, MAX_HILOS);

    // Proceso principal (padre) recoge los resultados de los hilos
    int sumaParcial;
    int sumaTotal = 0;
    close(pipefd[1]);  // Cerrar el extremo de escritura de la tubería en el proceso principal

    for (i = 0; i < MAX_HILOS; i++) {
        read(pipefd[0], &sumaParcial, sizeof(sumaParcial));

        // Bloquear el semáforo antes de actualizar sumaTotal
        sem_wait(&semaforo);
        sumaTotal += sumaParcial;
        sem_post(&semaforo);  // Liberar el semáforo
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < MAX_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Imprimir la suma total
    printf("La suma total es: %d\n", sumaTotal);

    // Destruir el semáforo
    sem_destroy(&semaforo);

    // Cerrar el extremo de lectura de la tubería
    close(pipefd[0]);

    // Liberar la memoria
    free(arr);
    fin = clock();
        tiempo = ((double)fin - inicio);
        printf("Tiempo %.2fms \n",tiempo);
    return 0;
}
