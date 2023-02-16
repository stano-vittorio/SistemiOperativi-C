/*
Scrivere:
a) un programma che legge da riga di comando due interi n, m. Il programma stampa a video la stringa: “Il prodotto di n e m e’: x“, dove x e’ il risultato dell’operazione n*m
b) un secondo programma che genera due numeri casuali. Mediante la system call exec, il programma utilizza il programma descritto nel punto a) per calcolarne il prodotto.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define MAX_NUM 100

int main(int argc, char *argv[]) {

    srand(time(0));

    int n = (int)(((double)rand() / RAND_MAX) * MAX_NUM);
    int m = (int)(((double)rand() / RAND_MAX) * MAX_NUM);

    char nStr[100];
    char mStr[100];

    sprintf(nStr, "%d", n);
    sprintf(mStr, "%d", m);

    execl("moltiplicatore", "moltiplicatore", nStr, mStr, (char *) NULL);
    printf("execl failed\n");
    return 1;
}