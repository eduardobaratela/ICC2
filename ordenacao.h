// para evitar inclusoes de arquivos .h de forma circular
// usamos um define para esse arquivo, caso ele ainda nao tenha sido
// definido (ifndef) entao define e inclui o arquivo

#ifndef _ORDENACAO_H_
#define _ORDENACAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VET 100000
#define FAIL -1

/* Gera vetor de inteiros com numeros
    aleatorios entre 0 e MAX_VET-1
   Parametros:
	int N - tamanho do vetor
	in** v - ponteiro para o vetor a ser alocado
*/
void gera_vetor_aleatorio(int N, int** v) {	
	(*v) = (int *) malloc(sizeof(int)*N);
	int i;
	for (i = 0; i < N; i++) {
		(*v)[i] = rand()%MAX_VET;
	}
}

/* Cria novo vetor, copiando um ja existente
*/
void clona_vetor(int N, int** des, int* ori) {	
	(*des) = (int *) malloc(sizeof(int)*N);
	int i;
	for (i = 0; i < N; i++) {
		(*des)[i] = ori[i];
	}
}


/* Gera vetor de inteiros com numeros ordenados
   Parametros:
	int N - tamanho do vetor
	in** v - ponteiro para o vetor a ser alocado
*/
void gera_vetor_ordenado(int N, int** v) {	
	(*v) = (int *) malloc(sizeof(int)*N);
	int i;
	(*v)[0] = 0;
	for (i = 1; i < N; i++) {
		(*v)[i] = (*v)[i-1] + (rand()%4)+1;
	}
}

/* Busca sequencial
   Parametros:
	int *v - vetor com numeros
	int num - numero a ser consultado
	int N - tamanho do vetor
   Retorno:
	FAIL se busca sem sucesso
	ou posicao em que o numero foi encontrado
*/
int busca_sequencial(int *v, int num, int N) {
	int j;
	for (j = 0; j < N; j++) {
		if (v[j] == num) return j;
	}	
	return FAIL;
}
/* Busca sequencial recursiva
   Igual a sequencial iterativa, mas precisa adicionalmente 
   da posicao 'j' onde realizar a busca 
   OBS: na primeira chamada, usar j = 0
*/
int busca_sequencial_recursiva(int *v, int num, int N, int j) {
	
	if (j >= N) return FAIL;
	if (v[j] == num) return j;
	else return busca_sequencial_recursiva(v,num,N,j+1);
}

/* Busca binaria
   Parametros:
	int *v - vetor de numeros inteiros
	int num - numero a ser consultado
	int ini - posicao inicial da regiao de busca
	int fim - posicao final da regiao de busca
   Retorno:
	int: posicao do valor encontrado ou FAIL se nao encontrado
*/

int busca_binaria(int *v, int num, int ini, int fim) {

	// 1 - consultar o elemento central

	// ex. vetor consultando na regiao ini=5, fim=7
	int tam = (fim-ini+1); // tamanho do vetor (ex. = 3)
	int cen = (int) (tam/2.0)+ini; // (int)(3/2) = 1 + ini = 6
	//int cen = (int) (fim+ini)/2.0; // ponto medio entre inicio e fim

	// verifica se encontrei o numero
	if (v[cen] == num) {
		return cen; // fim, encontrei o numero na posicao 'cen'
		// caso base!
	}
	// caso o vetor tenha tamanho unitario (1), cheguei no caso base
	if (tam == 1) {
		return FAIL;
	}

	// 2 - divide a regiao de busca em duas partes
	// se o elemento a ser procurado for menor do que o central
	// entao o final da regiao de busca passa a ser centro - 1
	if (num < v[cen]) {
		return busca_binaria(v, num, ini, cen-1);
	}
	// senao, o inicio da regiao de busca passa a ser centro + 1
	else {
		return busca_binaria(v, num, cen+1, fim);
	}

}

/* Insertion sort
   Ordena um vetor de inteiros: modifica o vetor 
   de forma que esteja ordenado
   Parametros:
	int* v: vetor a ser ordenado
	int N: tamanho do vetor
*/
void insertionsort(int *v, int N) {
	int chave, j, i;

	// no inicio tenho uma lista ordenada = v[0]

	for (i = 1; i < N; i++) {
		chave = v[i]; // primeiro elemento a ser inserido
		j = i-1; // comeco a comparar um elemento antes da chave
		while (j >= 0 && v[j] > chave) {
			v[j+1] = v[j]; // copia v[j] para a proxima posicao
			j--;
		}
		v[j+1] = chave; // j+1 e' a posicao correta da chave

		// aqui a lista ordenada sera v[0..i]
	}
}


/* Merge sort
   Ordena um vetor de inteiros: modifica o vetor 
   de forma que esteja ordenado
   Parametros:
	int* v: vetor a ser ordenado
	int ini: posicao inicial do vetor (ex. 0)
	int fim: posical final do vetor (ex. N-1)
*/

int mergesort(int *v, int ini, int fim) {

	// verificar caso base
	if (fim == ini) {
		return 1;
	}

	int meio = (int) ((fim+ini) / 2.0);

	// divisao (chamadas recursivas para metades do vetor)
	mergesort(v, ini, meio);
	mergesort(v, meio+1, fim);

	// passo de intercalacao (merge)
	int i,j,k; // k: vetor ordenado, i: lista 1, j: lista 2
	
	i = ini;
	j = meio+1;
	k = 0;

	// vetor temporario para armazenar a intercalacao
	int *v_int = malloc(sizeof(int)*(fim-ini+1));

	// intercala os dois vetores enquanto houver elementos 
	// em ambas as listas (vetores ordenados)
	while (i <= meio && j <= fim) {
		if (v[i] < v[j]) {
			v_int[k] = v[i];
			i++;
		} else {
			v_int[k] = v[j];
			j++;
		}
		k++;
	}
	// copiar todos os elementos restantes da lista 1
	while (i <= meio) {
		v_int[k] = v[i];
		k++; i++;
	}
	// copiar todos os elementos restantes da lista 2
	while (j <= fim) {
		v_int[k] = v[j];
		k++; j++;
	}

	// copia do temporario para o original
	int l;
	for (k = 0, l = ini; l <= fim; l++, k++) {
		v[l] = v_int[k];
	}

	/*
	// alternativa usando while
	l = ini; k =0;
	while (l <= fim) {
		v[l] = v_int[k];
		k++; l++;
	}
	*/

	free(v_int);

}


/* funcao heapify para um max-heap
   Parametros:
	int *v: vetor
	int  n: tamanho do vetor
	int  p: posicao para iniciar a verificacao
*/
void maxHeapify(int* v, int n, int p) {

	// v[p] => v[p*2], v[p*2 + 1]
	// trocar se for o caso
	// atualizar p para o maior

	// 'm' sera o maior dos filhos
	// comeco verificando o filho da esquerda
	int m = 2*p; // filho da esquerda

	// verifico se o filho da esquerda existe
	if (m <= n) {

		// verifico se o filho da direita existe ( m+1 <= n )
		// E se ele e' maior do que o da esquerda
		if ( m+1 <= n && v[m+1] > v[m]) {
			m = m+1;	
		}
		// nesse ponto terei na variavel 'm' o indice maior dos filhos
		// devo trocar?
		if (v[m] > v[p]) {
			int aux = v[p];
			v[p] = v[m];
			v[m] = aux;

			// chama recursivamente para m = p*2 (ou (p*2)+1)
			maxHeapify(v, n, m);
		}
	}
}


/* Funcao Heapsort
	1.o - monta max-heap
	2.o - pega maior e refaz heap

   Parameter:
	int *v : vetor
	int n  : tamanho do vetor	
*/
void heapsort(int *v, int n) {

	// 1.o montar max-heap
	int j;
	for (j = (int)(n/2.0); j >=1 ; j--) {
		maxHeapify(v, n, j);
	}	


	// 2.o move os maiores elementos para o final e remonta o heap
	int ultimo;
	for (ultimo = n; ultimo >=2; ultimo--) {
		int maxv = v[1]; // extrai o maior da heap
		v[1] = v[ultimo];
		v[ultimo] = maxv; // coloca na ultima posicao
	
		// remonta o heap a partir da raiz (1)
		maxHeapify(v, ultimo-1, 1);

	}
}


/* Escolha da estrategia do Pivo

   Parametros:
	v   - vetor 
	ini - inicio do vetor
	fim - fim do vetor
	strat - estrategia (0 = inicio, 1 = fim, 2 = meio, 3 = mediana, 4 = aleatorio)
   Retorno:
	int posicao do pivo
*/
int quickpivo(int *v, int ini, int fim, int strat) {

	int mid = (int)(ini+fim)/2.0;
	int ps[3];

	switch(strat) {
		case 0: return ini;
			break;

		case 1: return fim;
			break;

		case 2: return (int)(ini+fim)/2.0;
			break;

		case 3: ps[0]=v[ini]; ps[1]=v[mid]; ps[2]=v[fim];
			insertionsort(ps, 3);
			return ps[1];
			break;

		case 4: return (rand()%(fim-ini+1))+ini;
			break;
	}

	printf("apos switch");
	return mid;

}


/* Algoritmo Quicksort
	ordena vetor 'v'
   Parametros:
	int* v: vetor a ser ordenado
	int ini: primeira posicao do vetor
	int fim: posical final do vetor
	int strat: estrategia de escolha do pivo
*/
void quicksort(int *v, int ini, int fim, int strat) {

	if (fim <= ini) return; // condicao de parada

	// 1.o escolhe pivo
	int p = quickpivo(v, ini, fim, strat); // estragegia preguicosa

	// 2.o particiona com base no pivo
	int i = ini;  // indexa elementos ANTES do pivo
	int j = fim-1;// indexa elementos APOS o pivo 

	while (i < j) {
		// encontrando elementos candidatos para troca
		while (v[i] < v[p]) i++;
		while (j >= ini && v[j] > v[p]) j--;

		// caso seja necessario, troca os elementos
		// v[j] deve estar apos v[i]
		if (j > i) {
			int tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}	
	}
	// o indice 'i' contem a posicao correta do pivo

	// troco o pivo para que ele fique na sua posicao correta
	int tmp = v[p];
	v[p] = v[i];
	v[i] = tmp;

	p = i; // pivo esta agora na posicao 'i'

	// 3.o chama quicksort recursivamente
	quicksort(v, ini, p-1,strat);
	quicksort(v, p+1, fim,strat);
}




// fecha o 'ifndef' da primeira linha
#endif
