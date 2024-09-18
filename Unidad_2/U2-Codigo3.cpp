//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Ejemplo 3
//Fecha: 17/Septiembre/2024
//Explicación:  Este código crea cuatro hilos, cada uno de los cuales imprime una letra del abecedario ('A', 'B', 'C', 'D') como texto.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>  // Para usar malloc y free

// Función que será ejecutada por cada hilo
void *funcion_hilo(void *arg) {
    char *texto = (char *)arg;  // Convertir el argumento a cadena
    printf("Hilo ejecutado: %s\n", texto);  // Imprimir el texto del hilo
    free(texto);  // Liberar la memoria asignada
    pthread_exit(NULL);  // Terminar el hilo
    return 0;
}

int main() {
    pthread_t hilos[4];  // Array para almacenar los identificadores de los hilos

    // Crear hilos
    for (int i = 0; i < 4; i++) {
        // Asignar memoria para el texto del hilo
        char *texto = (char *)malloc(2 * sizeof(char));  // Solo necesitamos espacio para 1 carácter + '\0'
        // Convertir el índice a una letra del abecedario (A, B, C, D)
        texto[0] = 'A' + i;  // 'A' + 0 -> 'A', 'A' + 1 -> 'B'
        texto[1] = '\0';    // Terminar la cadena con el carácter nulo
        // Crear un nuevo hilo
        pthread_create(&hilos[i], NULL, funcion_hilo, (void *)texto);
    }

    // Esperar la finalización de los hilos
    for (int i = 0; i < 4; i++) {
        pthread_join(hilos[i], NULL);  // Esperar a que el hilo termine
    }

    return 0;
}
