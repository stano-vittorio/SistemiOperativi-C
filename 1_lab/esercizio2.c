/*
Utilizzando solamente le system call open, read, lseek, e write, realizzare un programma che simuli il comportamento del comando tac. Al contrario di cat, il comando tac stampa il contenuto di un file al contrario (dall’ultimo carattere al primo)
Utilizzo:
my_tac <file1> ... <filen>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>     // READ - WRITE - LSEEK
#include <sys/types.h>
#include <sys/stat.h>   // OPEN
#include <fcntl.h>      // OPEN

int main(int argc, char *argv[]) {

    // per ogni file fornito come parametro di input
    // iniziamo da 1 perchè in pos 0 == nome
    for(int i = 1; i < argc; ++i) {

        /*
        apertura file in sola lettura
        MODELLO OPEN -->
        int open(const char *pathname, int flags, ...);
        */
        int file = open(argv[i], O_RDONLY);

        // controllo esistenza file
        // -1 = codice errore file non esiste
        if(file == -1) {
            printf("\n** Il file %s non esiste **\n", argv[i]);
            continue; // va a quello successivo
        }

        /*
        sposto il pointer alla fine del file
        MODELLO LSEEK -->
        off_t lseek(int fd, off_t offset, int whence);
        */
        off_t currentOffset = lseek(file, -1, SEEK_END);
        char c; // nuovo carattere

        while(currentOffset >= 0) {

            /*
            lettura del file pos per pos
            MODELLO READ -->
            ssize_t read(int fd, void *buf, size_t count);
            */
            ssize_t bR = read(file, &c, sizeof(char));

            /*
            si scrive 'c' fino a sizeof(char) byte in output + controllo
            MODELLO WRITE -->
            ssize_t write(int fd, void *buf, size_t count);
            */
            if(bR == sizeof(char)) {
                if(write(STDOUT_FILENO, &c, sizeof(char)) != sizeof(char)) {
                    perror("Write fail!");
                    exit(1);
                }
            }

            currentOffset = lseek(file, -2, SEEK_CUR); // da pos ATTUALE            
        }

        close(file);    // chiusura file descriptor

        // stampo carattere a capo per secondo file
        c = '\n';
        write(STDOUT_FILENO, &c, sizeof(char));
    }
    
    return 0;
}