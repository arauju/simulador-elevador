/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 * BARBARA BELIZE MOREIRA BOECHAT
 *
 * ESTRATÉGIA1.C
 porta ++;
 *
 * TRABALHO PRÁTICO I
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
 * */

#include "estrategia1.h"
#include "tempo.h"

//ESTRATEGIA 1

int estr1 (tneyfila *F, int capacidade, int andares, int qtd, char *saida){


	FILE *out;
	out = fopen (saida,"a");


	int andarA = 1, i = 0, j = 0, k, l = 0, dif = 0, ocup = 0, distTotal = 0, porta = 0, guardatFora = 0, tempoTotalD = 0, tempoTotalF = 0;
	float ocupMedia = 0.0, ocupTotal = 0.0;
	Resul r[capacidade];
	nodetype *aux;
	nodetype *aux2;


	for (k = 0; k < capacidade; k++){
		r[k].tDentro = 0;
		r[k].tFora = 0;
		r[k].id = 0;
	}

	aux = F->inicio;
	aux2 = F->inicio;

	fprintf(out, "\nESTRATEGIA 1");
	//fprintf (out, "\nPassageiros\n");

	while (aux->prox != NULL){
		//Ação de pegar os passageiros até obter a capacidade máxima do elevador
		while ((ocup < capacidade) && (aux->prox != NULL)) {
			if (i == 0){
				aux = F->inicio;
				aux2 = F->inicio;
			} else {
				aux2= aux->prox;
				aux = aux->prox;
			}
			dif = abs (aux->dado.chamada - andarA);
			distTotal += dif;
			porta ++;
			r[j].id = i;
			andarA = aux->dado.chamada;

			//Calcula o tempo fora da primeira pessoa
			r[j].tFora = dif + guardatFora;

			i++; ocup ++; j++;
			while ((aux->prox != NULL) && (ocup < capacidade)){
				aux = aux->prox;
				dif = abs (aux->dado.chamada - andarA);
				distTotal += dif;
				porta ++;
				r[j].id = i;
				andarA = aux->dado.chamada;

				//calcula-se o tempo fora das demais pessoas
				r[j].tFora = r[j-1].tFora + 1 + dif;

				//calcula-se o tempo dentro do elevador enquanto as pessoas são pegas
				for (k = 0; k < ocup; k++) {
					r[k].tDentro += dif + 1;
				}
				i++; ocup ++; j++;
			}
		}

		j = 0;

		//Ação de levar todos os passageiros que estão dentro do elevador ao seu destino
		while ((ocup != 0) && (aux2->prox != NULL)){
			dif = abs (aux2->dado.destino - andarA);
			distTotal += dif;
			andarA = aux2->dado.destino;

			//tempo da primeira pessoa deixada
			r[j].tDentro += dif;

			//Adiciona esse tempo as pessoas seguintes, mais o tempo de abrir e fechar a porta para a pessoa descer
			for (k = 1; k < ocup; k++){
				r[k].tDentro += dif + 1;
			}

			ocup --; j++;

			//Deixando as demais pessoas no andar de destino
			while ((aux2->prox != NULL) && (ocup != 0)){
				aux2 = aux2->prox;
				dif = abs (aux2->dado.destino - andarA);
				distTotal += dif;
				porta ++;
				andarA = aux2->dado.destino;

				//Soma-se em cada passageiro o tempo gasto para se deixar a pessoa em questão
				r[j].tDentro += dif;
				for (k = j + 1; k < capacidade; k++){
					r[k].tDentro += dif + 1;
				}
				ocup --; j++;
			}
		}

		//Imprime os resultados
		for (k = 0; k < capacidade; k++){
			if (l < qtd){
				//fprintf (out, "%d. Tempo dentro do elevador: %d Jepslons, tempo fora: %d Jepslons\n", r[k].id + 1, r[k].tDentro, r[k].tFora);
				tempoTotalD += r[k].tDentro;
				tempoTotalF += r[k].tFora;
				l ++;
			}
		}

		// guarda o tempo da ultima pessoa que foi deixada, servindo de base para quem está fora do elevador
		guardatFora = r[capacidade-1].tDentro;

		j = 0;

		//o vetor que guarda os resultados é zerado
		for (k = 0; k < capacidade; k++){
			r[k].tDentro = 0;
			r[k].tFora = 0;
			r[k].id = 0;
		}
	}

	//Imprime os resultados
	fprintf (out, "\nTempo médio total de cada pessoa DENTRO: %d Jepslons, FORA: %d Jepslons\n", tempoTotalD/qtd, tempoTotalF/qtd);
	fprintf (out, "\nElevador\n");
	fprintf (out, "Numero de vezes que a porta abriu: %d \nDistancia total percorrida: %d andares\n\n", porta, distTotal);

}
