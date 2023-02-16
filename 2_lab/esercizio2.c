/*
Scrivere un programma che legge da riga di comando un intero positivo N.
Il programma successivamente crea N processi figlio. Ogni processo figlio, stampa a video il suo PID, il PID del suo processo padre, ed infine termina con un codice di terminazione (un numero casuale tre 0 e 255). Dopo avere creato N processi figlio, il programma attende la terminazione di ogni processo figlio. Ogni qualvolta un processo figlio termina, il programma stampa a video il codice di terminazione del figlio.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s NUMSUBPROC\n", argv[0]);
        exit(0);
    }

    int n = atoi(argv[1]);

    srand(time(0));

    pid_t pid;

    for(int i = 0; i < n; i++) {
        int code = (int)(((double)rand() / RAND_MAX) * 255);

        pid = fork();

        if(pid == -1) {
            printf("child %d not created\n", i);
        } else if(pid == 0) {
            printf("PID: %d, PPID: %d. Exit code: %d\n", getpid(), getppid(), code);
            exit(code);
        }

        int status = 0;

        while((pid = wait(&status)) != -1) {
            printf("Child %d exited --> status = %d\n", pid, WEXITSTATUS(status));
        }
    }

    return 0;
}