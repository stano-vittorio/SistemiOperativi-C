/*
Modificare il programma dell’ “Ese_2” affinche’ il processo parent attenda solo la terminazione dell’ultimo figlio creato. L’attesa deve avvenire in modalità polling!
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
    }

    int status, res;

    do {
        res = waitpid(pid, &status, WNOHANG);

        if(res == -1) {
            printf("waitpid failed\n");
            return 1;
        }
    } while(res == 0);

    printf("Child %d exited --> status = %d\n", pid, WEXITSTATUS(status));

    return 0;
}