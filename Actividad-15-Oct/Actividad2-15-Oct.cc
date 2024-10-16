//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Actividad 2 - Banco
//Fecha: 15/Octubre/2024

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Variable global que representa el saldo
int saldo = 1000;

// Mutex para garantizar operaciones atómicas
pthread_mutex_t candado;

// Función para depositar
void *depositar(void *arg) {
    int deposito = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&candado); // Bloquear el mutex
        saldo += deposito;
        printf("Depósito realizado: +%d, Saldo actual: %d\n", deposito, saldo);
        pthread_mutex_unlock(&candado); // Desbloquear el mutex
        sleep(1); // Simular una operación más larga
    }
    return NULL;
}

// Función para retirar
void *retirar(void *arg) {
    int retiro = *(int *)arg;
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&candado); // Bloquear el mutex
        if (saldo >= retiro) {
            saldo -= retiro;
            printf("Retiro realizado: -%d, Saldo actual: %d\n", retiro, saldo);
        } else {
            printf("Fondos insuficientes para retirar %d, Saldo actual: %d\n", retiro, saldo);
        }
        pthread_mutex_unlock(&candado); // Desbloquear el mutex
        sleep(1); // Simular una operación más larga
    }
    return NULL;
}

int main() {
    pthread_t hilo_deposito, hilo_retiro;
    int cantidad_deposito = 200;
    int cantidad_retiro = 150;

    // Inicializar el mutex
    pthread_mutex_init(&candado, NULL);

    // Crear los hilos
    pthread_create(&hilo_deposito, NULL, depositar, &cantidad_deposito);
    pthread_create(&hilo_retiro, NULL, retirar, &cantidad_retiro);

    // Esperar a que los hilos terminen
    pthread_join(hilo_deposito, NULL);
    pthread_join(hilo_retiro, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&candado);

    printf("Saldo final: %d\n", saldo);
    return 0;
}
