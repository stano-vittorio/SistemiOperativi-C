/*
Scrivere un programma che legge della riga di comando un comando di sistema X e i suoi argomenti.
Il programma crea un processo figlio, il quale, utilizzando la system call exec, esegue X redirezionando il suo standard output ed error su un file di testo. Il
processo parent attende la terminazione del processo figlio, stampa a video il codice di terminazione, ed infine termina.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char *fileName = "myfile1";

int main (int argc, char *argv[]) {

    if (argc <= 1) {
        printf("Usage: %s cmd [arguments]\n", argv[0]);
        return 0;
    }

    switch (fork()) {
        case -1: {
            printf("fork failed");
            return 1;
        }
        case 0: {
            close(STDOUT_FILENO); // close file descriptor 1
            close(STDERR_FILENO); // close file descriptor 2

            int fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

            if (fd == -1) {
                printf("open failed");
                return 1;
            }

            dup(fd);

            execvp(argv[1], &argv[1]);
            printf("execvp failed");
            return 1;
        }

        default: {
            int status;

            if (wait(&status) == -1) {
                printf("wait failed");
                return 1;
            }

            printf("Command %s exited with status %d\n", argv[1], WEXITSTATUS(status));
        }
    }

    return 0;
}