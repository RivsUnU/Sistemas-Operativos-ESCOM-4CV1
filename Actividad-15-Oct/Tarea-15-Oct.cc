//Nombre: Caldo de Gallina.
//Version: 1.0.0 - Tarea 1 , 2 , 3 , 4
//Fecha: 15/Octubre/2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE_LEN 1024

// Función para leer líneas alternas (pares e impares) y escribir en pipes
void tarea1(int pipe1[2], int pipe2[2], const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo el archivo");
        exit(1);
    }

    char line[MAX_LINE_LEN];
    int line_number = 0;

    // Cerrar las lecturas de los pipes ya que vamos a escribir en ellos
    close(pipe1[0]);
    close(pipe2[0]);

    while (fgets(line, sizeof(line), file)) {
        if (line_number % 2 == 0) {
            write(pipe1[1], line, strlen(line));  // Líneas pares
        } else {
            write(pipe2[1], line, strlen(line));  // Líneas impares
        }
        line_number++;
    }

    close(pipe1[1]);
    close(pipe2[1]);
    fclose(file);
}

void tarea2(int pipe_in[2], int pipe_out[2], const char *word) {
    // Cerrar las escrituras de los pipes ya que solo vamos a leer
    close(pipe_in[1]);
    close(pipe_out[0]);

    // Redirigir entrada y salida
    dup2(pipe_in[0], STDIN_FILENO);
    dup2(pipe_out[1], STDOUT_FILENO);

    // Ejecutar grep
    execlp("grep", "grep", word, NULL);

    perror("Error ejecutando grep");
    exit(1);
}

void tarea3(int pipe_in[2], int pipe_out[2], const char *word) {
    // Igual a tarea 2 pero para líneas impares
    close(pipe_in[1]);
    close(pipe_out[0]);

    dup2(pipe_in[0], STDIN_FILENO);
    dup2(pipe_out[1], STDOUT_FILENO);

    execlp("grep", "grep", word, NULL);

    perror("Error ejecutando grep");
    exit(1);
}

void tarea4(int pipe_in[2]) {
    // Redirigir entrada desde la pipe y ejecutar sort
    close(pipe_in[1]);

    dup2(pipe_in[0], STDIN_FILENO);
    execlp("sort", "sort", NULL);

    perror("Error ejecutando sort");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <archivo> <palabra_pares> <palabra_impares>\n", argv[0]);
        exit(1);
    }

    const char *filename = argv[1];
    const char *word_pares = argv[2];
    const char *word_impares = argv[3];

    // Crear pipes
    int pipe1[2], pipe2[2], pipe3[2];
    pipe(pipe1);  // Para líneas pares
    pipe(pipe2);  // Para líneas impares
    pipe(pipe3);  // Para salida de grep y entrada de sort

    // Tarea 1: dividir el archivo en líneas pares e impares
    if (fork() == 0) {
        tarea1(pipe1, pipe2, filename);
        exit(0);
    }

    // Tarea 2: grep en líneas pares
    if (fork() == 0) {
        tarea2(pipe1, pipe3, word_pares);
        exit(0);
    }

    // Tarea 3: grep en líneas impares
    if (fork() == 0) {
        tarea3(pipe2, pipe3, word_impares);
        exit(0);
    }

    // Tarea 4: sort en el resultado de las líneas seleccionadas
    if (fork() == 0) {
        tarea4(pipe3);
        exit(0);
    }

    // Cerrar pipes y esperar a los hijos
    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    close(pipe3[0]); close(pipe3[1]);

    // Esperar a que los procesos hijos terminen
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}
