#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
	int key;
	float value;
} Rec;

typedef struct node {
	Rec elem;
	struct node *next;
} Node;

typedef struct bucket {
	Node *begin;
	Node *end;
} Bucket;

void bucketsort(Rec *v, int N) {
	int i;

	// 1.o encontra o intervalo das chaves
	//     para alocar vetor de listas
	int max, min;
	max = min = v[0].key;
	for (i = 1; i < N; i++) {
		if (v[i].key > max) max = v[i].key;
		if (v[i].key < min) min = v[i].key;
	}

	// 2.o cria um vetor auxiliar de buckets (listas encadeadas)
	//     se o algoritmo for estavel implemento como *Fila*
	int sizeb = (max-min)+1;	
	Bucket *B = (Bucket *) calloc(sizeb, sizeof(Bucket));

	// 3.o preenche os buckets com as chaves do vetor de entrada
	for (i = 0; i < N; i ++) {
		int pos = v[i].key-min; // bucket da chave	
		
		// cria um novo no
		Node* newnode = malloc(sizeof(Node));
		newnode->elem = v[i];
		newnode->next = NULL;
		
		// se o bucket ainda estiver vaio
		if (B[pos].begin == NULL) {
			B[pos].begin = newnode;
		} else {
		// se houver algum elemento, insiro no final
			(B[pos].end)->next = newnode;
		}

		B[pos].end = newnode;		
	}

	// 4.o percorre cada bucket, removendo os elementos do inicio
	//     (Fila), e inserindo na posicao correta

	int j; // indice do bucket
	i = 0; // indice do vetor de saida
	for (j = 0; j < sizeb; j++) {
		
		// cria ponteiro apontando para o inicio da fila
		Node* p;
		p = B[j].begin;

		// enquanto bucket nao for vazio
		while (p != NULL) {
			// copia elemento para a lista
			v[i] = p->elem;
			i++;

			// remove elemento da fila
			Node* del = p;
			p = p->next; // atualiza proximo
			B[j].begin = p; // atualiza inicio
			free(del); // desaloca no
		}
	}

	// 5.o libera vetor de Buckets
	free(B);	

}


/* Radix sort com base 256 para ordenar numeros inteiros

*/
void radixsort(Rec *v, int N) {

	int i,j;
	int shift;

	int counting[256] = {0}; // vetor contagem
	int position[256]; // contagem acumulada - posicao

	// vetor com copia do original
	Rec *tmp = (Rec *) malloc(N * sizeof(Rec));	

	for(shift = 0; shift < 32; shift += 8){

		// 1 - counting sort (N)
		for(j = 0; j < N; j++) {
			i = (v[j].key >> shift) & 255;
			counting[i]++;
			// ao mesmo tempo copia o vetor
			tmp[j] = v[j];
		}

		// 2 - calcula vetor acumulado (encontrar as posicoes)
		//     256
		position[0] = 0;
		for (i = 1; i < 256; i++) {
			position[i] = position[i-1] + counting[i-1];

			// zera contagem para a proxima passada
			counting[i-1] = 0;
		}
		
		// 3 - copia o vetor tmp para o vetor de entrada
		//     considerando base 256
		//     (N)
		for (j = 0; j < N; j++) {
			i = (tmp[j].key >> shift) & 255;// encontra a posicao
			v[position[i]] = tmp[j]; // copia para a posicao
			position[i]++; // incrementa posicao da proxima chave
		}
	}

	free(tmp);

}


void countingsort_rec(Rec* v, int N) {

	int i, j; // indices

	// Preciso criar uma copia do vetor para reposicionar os elementos
	Rec* vcopy = (Rec *) malloc(sizeof(Rec) * N);

	// 1.o encontrar maior e menor chaves
	//     contagem = 'n'
	int max, min;
	max = min = v[0].key;
	vcopy[0] = v[0];
	for (i = 1; i < N; i++) {
		if (v[i].key > max) max = v[i].key;
		if (v[i].key < min) min = v[i].key;

		vcopy[i] = v[i]; // aproveita para copiar
	}

	// 2.o cria vetor auxiliar de contagem
	//     contagem = sizevec = 'k'
	int sizevec = (max-min)+1;
	int *C = (int *) calloc(sizevec, sizeof(int));	

	// 3.o - conta a frequencia de cada chave em 'v'
	for (i = 0; i < N; i++) {
		int pos = v[i].key-min;		
		C[ pos ]++;
	}

	// 4.o - calcula vetor de contagem acumulada	
	int *CA = (int *) calloc(sizevec, sizeof(int));
	CA[0] = 0;
	for (i = 1; i < sizevec; i++) {
		CA[i] = CA[i-1]+C[i-1];
	}

	free(C);

	/* 5.o - passagem final, percorre o vetor de copia
		posicionando os elementos no vetor original
		-> a posicao eh dada pelo vetor de contagem
		   acumulada
	*/
	// para cada elemento do vetor copiado
	for (j = 0; j < N; j++) {
		// acha a posicao correta do elemento	
		int pos = CA[ vcopy[j].key-min ];

		// copia para a posicao correta
		v[pos] = vcopy[j];

		// incrementa o vetor de contagem
		CA[ vcopy[j].key-min ]++;

	}

	free(CA);
	free(vcopy);
}


/* Algoritmo Quicksort
	ordena vetor 'v'
   Parametros:
	int* v: vetor a ser ordenado
	int ini: primeira posicao do vetor
	int fim: posical final do vetor
	int strat: estrategia de escolha do pivo
*/
void quicksort(Rec *v, int ini, int fim, int strat) {

	//printf("%d %d\n", ini, fim);	
	if (fim <= ini) return; // condicao de parada

	// 1.o escolhe pivo
	int p = fim; // estragegia preguicosa

	// 2.o particiona com base no pivo
	int i = ini;  // indexa elementos ANTES do pivo
	int j = fim-1;// indexa elementos APOS o pivo 

	while (i < j) {
		// encontrando elementos candidatos para troca
		while (v[i].key <= v[p].key) i++;
		while (j >= ini && v[j].key >= v[p].key) j--;

		// caso seja necessario, troca os elementos
		// v[j] deve estar apos v[i]
		if (j > i) {
			Rec tmp = v[i];
			v[i] = v[j];
			v[j] = tmp;
		}	
	}
	// o indice 'i' contem a posicao correta do pivo

	// troco o pivo para que ele fique na sua posicao correta
	Rec tmp = v[p];
	v[p] = v[i];
	v[i] = tmp;

	p = i; // pivo esta agora na posicao 'i'

	// 3.o chama quicksort recursivamente
	quicksort(v, ini, p-1,strat);
	quicksort(v, p+1, fim,strat);
}



int main (int argc, char* argv[]) {

	int N = atoi(argv[1]);
	int i;

	srand(time(NULL));
	Rec* vr = (Rec *)malloc(sizeof(Rec)*N);
	Rec* vb = (Rec *)malloc(sizeof(Rec)*N);
	Rec* vc = (Rec *)malloc(sizeof(Rec)*N);
	Rec* vq = (Rec *)malloc(sizeof(Rec)*N);
	for (i = 0; i < N; i++) {
		vq[i].key = vb[i].key = vc[i].key = vr[i].key = rand()% (int)(N);
		vb[i].value = vc[i].value = vr[i].value = (float)i+1;
		//printf("%d (%.2f)\n", vr[i].key, vr[i].value);
	}

	double radix_t, count_t, bucket_t, quick_t;
	clock_t t1, t2;

	t1 = clock();
	radixsort(vr, N);
	t2 = clock();
	radix_t = (t2 - t1)/(double)CLOCKS_PER_SEC;
	printf("Radix\t:%lf\n", radix_t);

	t1 = clock();
	countingsort_rec(vc, N);
	t2 = clock();
	count_t = (t2 - t1)/(double)CLOCKS_PER_SEC;
	printf("Count.\t:%lf\n", count_t);


	t1 = clock();
	bucketsort(vb, N);
	t2 = clock();
	bucket_t = (t2 - t1)/(double)CLOCKS_PER_SEC;
	printf("Bucket\t:%lf\n", bucket_t);

	t1 = clock();
	quicksort(vq, 0, N-1, 4);
	t2 = clock();
	quick_t = (t2 - t1)/(double)CLOCKS_PER_SEC;
	printf("Quick\t:%lf\n", quick_t);

	printf("Radixsort:\n");
	for (i = 0; i < N; i++) {
		printf("%d (%.2f)\n", vr[i].key, vr[i].value);
	}	
	printf("\n");
	

	free(vr);
	free(vb);
	free(vc);
	free(vq);

	return 0;
}
