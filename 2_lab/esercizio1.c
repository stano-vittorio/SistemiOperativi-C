/*
Utilizzando la variabile environ, scrivere un programma che legge lo username (variabile USER) e la home (variabile HOME) dell’utente utilizzatore.
Il programma confronta il path della sua attuale directory di lavoro con la home directory dell’utente.
Se la directory di lavoro non e’ una sotto directory della home directory dell’utente, il programma imposta la home directory dell’utente come sua directory di lavoro, crea un file di testo vuoto, e stampa a video: “Caro USER, sono dentro la tua home!”, dove USER e’ l’username dell’utente.
Se la directory di lavoro e’ una sotto directory della home directory dell’utente, il programma stampa a video: “Caro USER, sono gia’ nel posto giusto!”.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SZ 100
char buffer[BUFFER_SZ + 1];

int main (int argc, char *argv[]) {

    char *homeDir  = getenv("HOME");
    if (homeDir == NULL) {
        printf("unknown home directory\n");
        return 1;
    }

    char *username = getenv("USER");
    if (username == NULL) {
        username = "unknown";
    }

    if (getcwd(buffer, sizeof(buffer)) == NULL) {
        printf("getcwd failed\n");
        return 1;
    }

    int subDir = strncmp(buffer, homeDir, strlen(homeDir));

    if (subDir == 0) {
        printf("Caro %s, sono gia' nel posto giusto!\n", username);
    } else {

        if (chdir(homeDir) == -1) {
            printf("chdir failed");
            return 1;
        }

        int fd = open("empty_file.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

        if (fd == -1) {
            printf("open failed\n");
            return 1;
        }

        if (close(fd) == -1) {
            printf("close failed");
            return 1;
        }

        printf("Caro %s, sono dentro la tua home!\n", username);
    }

    return 0;
}