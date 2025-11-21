#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

// CONSTANTES
#define MAX_STRING 25

// ESTRUTURAS
typedef struct Sala {
	char nome[MAX_STRING];
	struct Sala* esquerda;
	struct Sala* direita;
} Sala;

// FUNÇÕES
Sala* criarSala(const char* nome);
void explorarSalas(Sala* raiz);
void conectarSalas(Sala* raiz, Sala* esquerda, Sala* direita);
void limparSalas(Sala* sala);

// IMPLEMENTAÇÃO DAS FUNÇÕES

// aloca e inicia o valor de uma sala e retornando sua referência
Sala* criarSala(const char* nome) {
	// define o vetor para alocar as salas
	Sala* sala = (Sala*)malloc(sizeof(Sala));

	// se falhar na alocação fecha o programa
	if (sala == NULL) {
		printf("[!] Falha de alocação da nova sala!\n");
		exit(-1);
	}

	// inicializa os valores da nova sala
	strcpy(sala->nome, nome);
	sala->esquerda = nullptr;
	sala->direita = nullptr;

	// retorna a referência da nova sala
	return sala;
}

void conectarSalas(Sala* raiz, Sala* esquerda, Sala* direita) {
	// se a raiz for nula, cancela operação
	if (raiz == NULL) return;

	// não há problema dos nós esquerda/direita serem nós nulos
	raiz->esquerda = esquerda;
	raiz->direita = direita;
}

void explorarSalas(Sala* raiz) {
	// verifica se a sala atual é nula
	if (raiz == NULL)
		return;


	char escolha;
	do {
		// verifica se sala atual é um nó-folha
		if (raiz->esquerda == NULL && raiz->direita == NULL) {
			printf("[!] Não há mais caminhos para explorar!\n");
			printf("[*] Fim de jogo...\n");
			return;
		}

		printf("------------------------------\n");
		printf(" > Você está na sala: %s\n", raiz->nome);
		printf(" > Selecione uma ação:\n");

		if (raiz->esquerda != NULL) {
			printf(" - [Q]: Ir para esquerda (%s)\n", raiz->esquerda->nome);
		}

		if (raiz->direita != NULL) {
			printf(" - [E]: Ir para direita (%s)\n", raiz->direita->nome);
		}

		printf(" - [S]: Encerrar o jogo\n");
		printf("------------------------------\n");
		printf(">> ");
		scanf(" %c", &escolha);

		printf("\n------------------------------\n");
		switch (escolha) {
		case 's':
		case 'S':
			printf("[*] Saindo do jogo...\n");
			return; // esse return é valido para encerrar a função explorarSalas(Sala*)

		case 'q':
		case 'Q':
			if (raiz->esquerda != NULL) {
				printf("[*] Indo para esquerda... (%s)\n", raiz->esquerda->nome);
				raiz = raiz->esquerda;
			} else {
				printf("[!] Não há salas na esquerda!");
			}

			break;

		case 'e':
		case 'E':
			if (raiz->direita != NULL) {
				printf("[*] Indo para direita... (%s)\n", raiz->direita->nome);
				raiz = raiz->direita;
			} else {
				printf("[!] Não há salas na direita!");
			}
			break;

		default:
			printf("[!] Opção inválida\n");
			break;
		}
	} while (escolha != 's' && escolha != 'S');
}

// limpa da memória, usando recursão
// em sentido pós-fixo transversal (Esquerda - Direita - Raiz)
void limparSalas(Sala* sala) {
	if (sala == NULL) {
		return;
	}

	limparSalas(sala->esquerda);
	limparSalas(sala->direita);

	free(sala);
}


int main() {
	Sala* hall = criarSala("Hall de Entrada");
	Sala* salaEstar = criarSala("Sala de Estar");
	Sala* cozinha = criarSala("Cozinha");
	Sala* biblioteca = criarSala("Biblioteca");
	Sala* quartos = criarSala("Quartos");
	Sala* armazem = criarSala("Armazém");
	Sala* jardim = criarSala("Jardim");

	conectarSalas(hall, salaEstar, cozinha);
	conectarSalas(salaEstar, quartos, biblioteca);
	conectarSalas(cozinha, armazem, jardim);

	/*
	 *              Hall de Entrada
	 *          /                    \
	 *    Sala de Estar            Cozinha
	 *       /     \               /     \
	 *   Quartos  Biblioteca  Armazém  Jardim
	 */

	explorarSalas(hall);

	limparSalas(hall);

	return 0;
}
