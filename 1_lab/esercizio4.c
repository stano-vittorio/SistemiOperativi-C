/*
Realizzare un programma che simuli il comportamento del comando cp, con i seguenti scenari di utilizzo:

1. my_cp <source> <destination>: Il programma copia il contenuto del file <source> in un nuovo file di nome <destination>. Se il file <destination> gia’ esiste, il programma stampa a video la stringa:
“Il file <destination> gia’ esiste!”
2. my_cp -s <source> <destination>: Il programma copia il contenuto del file <source> in un nuovo file di nome <destination>. Se il file <destination> gia’ esiste, il programma sovrascrivere il contenuto del file <destination> con il contenuto del file <source>.
3. my_cp -a <source> <destination>: Il programma aggiunge in fondo al file <destination> il contenuto del file <source>. Se il file <destination> non esiste, il programma stampa a video la stringa: “Il file <destination> non esiste!”
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

     if(argc != 3 && argc != 4) {
        printf("Usage: %s [option] <sourceFile> <destinationFile>\n", argv[0]);
        printf("Option:\n");
        printf("-a: append\n");
        printf("-s: overwrite\n");
        return 1;
    }

    char *flag = NULL;
    char *fileSource, *fileDestination;

    if(argc == 4) {
        flag = argv[1];
        fileSource = argv[2];
        fileDestination = argv[3];
    } else {
        fileSource = argv[1];
        fileDestination = argv[2];
    }

    int fileS = open(fileSource, O_RDONLY);

    if(fileS == -1) {
        perror("Open failed");
        exit(1);
    }

    int fileD = -1;

    if(flag == NULL) {

        if(access(fileDestination, F_OK) == 0) {
            printf("Il file %s esiste già\n", fileDestination);
            return 1;
        }

        fileD = open(fileDestination, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR);

    } else if(strcmp(flag, "-s") == 0) {

        fileD = open(fileDestination, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    
    } else if(strcmp(flag, "-a") == 0) {

        if(strcmp(fileSource, fileDestination) == 0) {
            printf("The same file!");
            return 1;
        }

        if(access(fileDestination, F_OK | W_OK) != 0) {
            printf("The file %s does not exist or cannot be written!\n", fileDestination);
            return 1;
        }

        fileD = open(fileDestination, O_WRONLY);

        if(fileD != -1 && lseek(fileD, 0, SEEK_END) == -1) {
            perror("lseek failed");
            exit(1);
        }

    } else {
        perror("Flag not valid");
        exit(1);
    }

    if(fileD == -1) {
        perror("Open failed");
        exit(1);
    }

    ssize_t bR = 0;

    do {
        bR = read(fileS, buffer, BUFFER_SZ);

        if(bR == -1) {
            perror("Read failed");
            exit(1);
        }

        if(bR > 0 && write(fileD, buffer, bR) != bR) {
            perror("Write failed");
            exit(1);
        }

    } while(bR > 0);

    if(close(fileS) == -1 || close(fileD) == -1) {
        perror("Close failed");
    }

    return 0;
}
