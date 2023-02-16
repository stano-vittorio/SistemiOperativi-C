#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage: %s n m\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    printf("Il prodotto di %d e %d è: %d", n, m, (n * m));

    return 0;
}