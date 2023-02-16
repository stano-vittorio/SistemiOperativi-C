/*
Utilizzando solamente le system call open e read, e la funzione printf, realizzare un programma che simuli il comportamento del comando cat. Utilizzo: my_cat <file1> ... <filen>
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>     // READ
#include <sys/types.h>
#include <sys/stat.h>   // OPEN
#include <fcntl.h>      // OPEN

#define BUFFER_SZ 100       // open e read hanno bisogno di un buffer
char buffer[BUFFER_SZ + 1]; // dimensione del buffer sempre aumentate di 1

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
        ssize_t è un tipo intero senza segno che C garantisce sia sufficientemente grande per poter rappresentare le dimensioni di un determinato oggetto
        */
        ssize_t bR = 0;

        do {
            /*
            lettura del file pos per pos
            MODELLO READ -->
            ssize_t read(int fd, void *buf, size_t count);
            */
            bR = read(file, buffer, BUFFER_SZ);

            if(bR > 0) {                // in caso abbia letto qualcosa
                buffer[bR] = '\0';      // termino la stringa in fondo
                printf("%s", buffer);   // stampa carattere
            }
        } while(bR > 0);                // fino a che leggo qualcosa

        close(file);    // chiusura file descriptor
        printf("\n");   // stampo carattere a capo per secondo file
    }

    return 0;
}