#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {

    FILE *ambiente = fopen("ambiente.txt","w");
    FILE *entrada = fopen("entrada.txt","w");

    int chamada, destino, TAM, i, q;
    int andares = 50, max = 15;
    srand((unsigned)time(NULL));


	fprintf(ambiente, "%d\n%d", max, andares);
	//entradas
    for (i = 0; i < 1000; i++) {
        chamada = rand() % andares;
        destino = rand() % andares;
        while (chamada == destino || chamada == 0 || destino == 0){
            chamada = rand() % andares;
            destino = rand() % andares;
        }
            fprintf(entrada, "%d %d\n",chamada,destino);
    }

    return 0;
}
