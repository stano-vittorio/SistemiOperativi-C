/*
Realizzare un programma che sfruttando le system call per la gestione dei file esegua un search_replace di un carattere all’interno di un file.
search_replace <source file> <destination file> <char search> <char replace>
Il programma copia il contenuto del file <source file> in un nuovo file di nome <destination file>. Dovrà sostituire tutte le occorrenze di <char search> con <char replace>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SZ 100
char buffer[BUFFER_SZ + 1];

int main(int argc, char *argv[]) {

    char *charSearch, *charReplace;
    char *fileSource, *fileDestination;

    if(argc != 5) {
        printf("Usage: %s <sourceFile> <destinationFile> <charSearch> <charReplace>\n", argv[0]);
        return 1;
    } else {
        fileSource = argv[1];
        fileDestination = argv[2];
        charSearch = argv[3];
        charReplace = argv[4];
    }

    int fileS = open(fileSource, O_RDONLY);

    if(fileS == -1) {
        printf("File %s not found!", fileSource);
        perror("Source file not found");
        exit(1);
    }

    int fileD = -1; // consideriamo che il file destinazione non esista

    if(access(fileDestination, F_OK) == 0) {
        printf("File %s already exist!", fileDestination);
        return 1;
    }

    // creazione file con permessi
    fileD = open(fileDestination, O_CREAT | O_EXCL | O_WRONLY, S_IREAD | S_IWRITE);

    // controllo apertura/creazione file
    if(fileS == -1) {
        perror("Open Failed");
        exit(1);
    }

    ssize_t bR;
    char c;

    do {
        ssize_t bR = read(fileS, &c, sizeof(char));

        if(bR == -1) {
            perror("Read Failed");
            exit(1);
        }

        if(c == *charSearch) {
            c = *charReplace;
        }

        if(write(fileD, &c, sizeof(char)) != sizeof(char)) {
            perror("Write Failed");
            exit(1);
        }
    } while(bR > 0);

    if(close(fileS) == -1 || close(fileD) == -1) {
        perror("Close Failed");
        exit(1);
    }

    return 0;
}