#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
int main() {
    pid_t rf;
    rf = fork();
    switch (rf) {
        case -1:
            printf("\nNo he podido crear el proceso hijo");
            break;
        case 0:
            printf("\nSoy el hijo, mi PID es %d y mi PPID es %d", getpid(), getppid());
          //  sleep(10);
            break;
        default:
            printf("\nSoy el padre, mi PID es %d y el PID de mi hijo es %d", getpid(), rf);
    }
    printf("\nFinal de ejecucion de %d \n", getpid());
    exit(0);
}

/*
Programa que divide en 2 el proceso creando proceso padre e hijo, donde despues con un print mostramos el PID asignado por el SO al hijo y despues se repite 
el proceso pero con el proceso padre.


*/