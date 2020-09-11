/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 * BARBARA BELIZE BOECHAT
 *
 * MAIN.C
 *
 * TRABALHO PRÁTICO I
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
 * */

#include "registro.h"
#include "estrategia1.h"
#include "estrategia2.h"
#include "tempo.h"

int main(int argc, char const *argv[]) {
	FILE *entrada, *ambiente;
    entrada = fopen(argv[1], "r");
	ambiente = fopen (argv[2], "r");
	char* saida = argv[3];

	//Variaveis para calcular tempo
	double tempoU,tempoS;
	struct rusage resources;
	struct timeval inicioU, inicioS, fimU, fimS;

	Tempo t;
	Elementob v;
	tneyfila *F;

	F = (tneyfila*) malloc(sizeof(tneyfila));

	// guarda quantos elementos estão inseridos na fila
	int qtd = 0, a;
	int capacidade, andares;
	elem l;
  elem h;
  tlista *L;

  L = (tlista*) malloc(sizeof(tlista));
	criaListaL(L);

	//ambiente do elevador
	fscanf(ambiente, "%d", &capacidade); fscanf (ambiente, "%d", &andares);
	//lendo o arquivo e adicionando os numeros na fila e lista
	while (fscanf(entrada, "%d", &v.chamada) && fscanf(entrada, "%d", &v.destino)!=EOF){
	  l.chamada = v.chamada;
	  l.destino = v.destino;
	  l.marcador = 0;
	  l.tDentro = 0;
	  l.tFora = 0;
	  inserirF(F, v);
	  inserirL(L,l);
	  qtd++;
	}

	//ESTRATÉGIA 1 - FILA
	iniciaTempo(&t);
	estr1(F, capacidade, andares, qtd, saida);
	finalizaTempo(&t, &tempoU, &tempoS);
	printf("Tempo de sistema Estrategia 1: %.9f\n",tempoS);
	printf("Tempo de usuário Estrategia 1: %.9f\n",tempoU);


	//ESTRATÉGIA 2 - LISTA
	iniciaTempo(&t);
	Ordena (L);
  estr2 (L, capacidade, andares, saida);
	finalizaTempo(&t, &tempoU, &tempoS);
	printf("Tempo de sistema Estrategia 2: %.9f\n",tempoS);
	printf("Tempo de usuário Estrategia 2: %.9f\n",tempoU);

	free(F);
	free(L);
	fclose(ambiente);
	fclose(entrada);

  return 0;
}
