/*
 * JULIANA DE FÁTIMA OVÍDIO ARAÚJO
 * BARBARA BELIZE MOREIRA BOECHAT
 *
 * ESTRATÉGIA2.C
 *
 * TRABALHO PRÁTICO I
 *
 * CIÊNCIA DA COMPUTAÇÃO
 * ALGORITMOS E ESTRUTURAS DE DADOS III
 * 2/2016
 *
 * */

#include "estrategia2.h"

void estr2 (tlista *L, int capacidade, int andares, char *saida){

	FILE *out;
	out = fopen(saida,"w");

	lno *aux, *aux2;
	int andarA = 1, ocup = 0, porta = 0, distTotal = 0, marcd = 0, k = 0, tForaTotal = 0, nPessoas = L->tamanho, portaAberta = 0, tempoTotalF = 0, tempoTotalD = 0,ocupTotal;

	aux = (lno*) malloc(sizeof(lno));
	aux2 = (lno*) malloc(sizeof(lno));

	aux = L->primeira;
	aux2 = L->primeira;


	//Imprimir os resultados no arquivo de saída
	fprintf (out, "\n\nESTRATEGIA 2");
	//fprintf (out, "\nPassageiros\n");

	while (listVaziaL(L) == 0){
		andarA = 1;

		//ato do elevador subir
		while (andarA <= andares){

			//verifica se alguem pode descer
			aux = L->primeira;
			while (aux->proxima != NULL && (L->tamanho != 0)){
				if ((aux->passageiro.marcador == 1) && (andarA == aux->passageiro.destino)){
					ocup --;
					aux->passageiro.tDentro = tForaTotal - aux->passageiro.tFora;
					marcd ++;
					aux->passageiro.id = marcd;

					//Imprimir os resultados no arquivo de saída
					fprintf (out, "%d. Tempo dentro do elevador: %d Jepslons, tempo fora: %d Jepslons\n", aux->passageiro.id, aux->passageiro.tDentro, aux->passageiro.tFora);
					tempoTotalD += aux->passageiro.tDentro;
					tempoTotalF += aux->passageiro.tFora;

					//verificar se a porta já está aberta
					if (portaAberta == 0){
						porta ++;
					}

					portaAberta = 1;
					tForaTotal ++;
					removerL(L, aux->passageiro);
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL (L) == 0){
					aux = aux->proxima;
				}else{
					aux = L->primeira;
				}
			}

			//faz o ponteiro voltar para onde estava antes
			aux = aux2;

			//pegar os passageiros daquele andar
			while ((aux != NULL) && (andarA == aux->passageiro.chamada)){
				if ((ocup < capacidade) && (aux->passageiro.destino > andarA) && (aux->passageiro.marcador == 0)){
					ocup ++;
					aux->passageiro.tFora = tForaTotal;
					aux->passageiro.marcador = 1;

					//verificar se a porta já está aberta
					if (portaAberta == 0){
						porta ++;
					}

					portaAberta = 1;
					tForaTotal ++;
				}
				if (listVaziaL (L) == 0){
					aux = aux->proxima;
				}else{
					aux = L->primeira;
				}
			}

			//Elevador vai para andar seguinte, e a distância percorrida é acrescida
			ocupTotal += ocup;
			andarA ++;
			distTotal ++;
			tForaTotal ++;
			portaAberta = 0;
		}

		//Para começar a descer os andares, os auxiliares são apontados pra a ultima pessoa na lista
		aux = L->ultima;
		aux2 = L->ultima;
		andarA = andares;
		portaAberta = 0;



		//ato de descer o elevador
		while (andarA >= 1 && (listVaziaL (L) == 0)){
			aux = L->primeira;

			//percorre toda a lista para verificar se alguem pode descer
			while (aux != NULL && L->tamanho != 0){
				if ((aux->passageiro.marcador == 1) && (andarA == aux->passageiro.destino)){
					ocup --;
					aux->passageiro.tDentro = tForaTotal - aux->passageiro.tFora;
					marcd ++;
					aux->passageiro.id = marcd;

					//Imprimir os resultados no arquivo de saída
					fprintf (out, "%d. Tempo dentro do elevador: %d Jepslons, tempo fora: %d Jepslons\n", aux->passageiro.id, aux->passageiro.tDentro, aux->passageiro.tFora);
					tempoTotalD += aux->passageiro.tDentro;
					tempoTotalF += aux->passageiro.tFora;

					//verificar se a porta já está aberta
					if (portaAberta == 0){
						porta ++;
					}

					portaAberta = 1;
					tForaTotal ++;
					removerL (L, aux->passageiro);
				}

				//aponta-se para o próximo passageiro, caso a lista não esteja vazia
				if (listVaziaL (L) == 0){
					aux = aux->proxima;
				}else{
					aux = L->primeira;
				}
			}

			//faz o ponteiro voltar para a pessoa em questão
			if (listVaziaL (L) == 0){
				aux = aux2;
			}

			//pegar os passageiros daquele andar
			while ((aux != NULL) && (andarA == aux->passageiro.chamada)){
				if ((ocup < capacidade) && (aux->passageiro.destino < andarA)){
					ocup ++;
					aux->passageiro.tFora = tForaTotal;

					//verificar se a porta já está aberta
					if (portaAberta == 0){
						porta ++;
					}

					portaAberta = 1;
			 		porta ++;
			 		tForaTotal ++;
					aux->passageiro.marcador = 1;
				}

				//aponta-se para o passageiro anterior, caso a lista não esteja vazia
				if (listVaziaL (L) == 0){
					aux2 = aux->anterior;
					aux = aux->anterior;
				}
			}

			//Elevador vai para andar anterior, e a distância percorrida é acrescida
			ocupTotal += ocup;
			andarA --;
			distTotal ++;
			tForaTotal ++;
			portaAberta = 0;
		 }
	}

	//Imprimir os resultados no arquivo de saída
	fprintf (out, "\nTempo médio total de cada pessoa DENTRO: %d Jepslons, FORA: %d Jepslons\n", tempoTotalD/nPessoas, tempoTotalF/nPessoas);
	fprintf (out, "\n Elevador\n");
	fprintf (out, "Numero de vezes que a porta abriu: %d \nDistancia total percorrida: %d andares\n\n", porta, distTotal);
	free(aux);
	free(aux2);
	fclose (out);
}
