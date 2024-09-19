#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void imprimeDePipe(int leePipe);  // Funcionalidad para el hijo
void enviaAPipe(int escribePipe); // Funcionalidad para el padre

int main() {
    pid_t procHijo;
    int pipeFileDescriptors[2]; // Descriptores de ambos extremos
    
    // Genera pipe
    if (pipe(pipeFileDescriptors) == -1) {
        printf("Error al crear pipe\n");
        exit(1);
    }

    procHijo = fork(); // Genera proceso hijo
    if (procHijo < 0) {
        int errnum = errno; // Preservamos código de error
        printf("Error %d al generar proceso hijo con fork\n", errnum);
        exit(1);
    }

    if (procHijo == 0) {
        // Es el hijo, cierra pipe de envío y procede
        close(pipeFileDescriptors[1]);
        imprimeDePipe(pipeFileDescriptors[0]);
    }

    if (procHijo > 0) {
        // Es el padre, cierra pipe de recepción y procede
        close(pipeFileDescriptors[0]);
        enviaAPipe(pipeFileDescriptors[1]);
    }

    return 0;
}

void imprimeDePipe(int leePipe) {
    char buf; // Carácter de buffer
    printf("Proceso hijo, esperando cadena...\n");
    while (read(leePipe, &buf, 1) > 0) {
        write(STDOUT_FILENO, &buf, 1);
    }
    write(STDOUT_FILENO, "\n", 1); // Fin de línea
    close(leePipe);
    printf("Proceso hijo, finalizando\n");
    exit(0);
}

void enviaAPipe(int escribePipe) {
    char buf[10]; // Buffer de hasta 10 caracteres
    printf("Proceso padre, ingresa una cadena de 10 caracteres y enter:\n");
    scanf("%10s", buf); // Leemos hasta 10 caracteres
    printf("\n\n"); // Separador de salida
    write(escribePipe, buf, strlen(buf));
    close(escribePipe); // Presenta EOF al proceso hijo
    wait(NULL); // Espera la terminación del hijo
    printf("Hijo terminado, terminando proceso padre\n");
    exit(0);
}
