#include <stdio.h>
#include <stdlib.h>

typedef struct rec {
	int key;
	float value1;
	char value2;
} Rec;


typedef struct node {
	Rec elem;
	struct node *next;
} Node;

typedef struct bucket {
	Node *begin;
	Node *end;
} Bucket;


int i;

	// 1.o encontra o intervalo das chaves

void bucketsort(Rec *v, int N) {
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


int main(int argc, char* argv[]){

	if (argc < 2) { 
		printf("Forneca tamanho do vetor\n\n");
		return -1;
	}
	
	int i;
	int N = atoi(argv[1]);
	Rec* vr = (Rec *)malloc(sizeof(Rec)*N);
	for (i = 0; i < N; i++) {
		vr[i].key = rand()% (int)(N/2.0);
		vr[i].value1 = (float)i+1;
		vr[i].value2 = (char) rand()%(96-63)+64;
		printf("%d (%.2f, %c)\n", vr[i].key, vr[i].value1, vr[i].value2);
	}

	bucketsort(vr, N);

	printf("Bucketsort:\n");
	for (i = 0; i < N; i++) {
		printf("%d (%.2f, %c)\n", vr[i].key, vr[i].value1, vr[i].value2);
	}		
	printf("\n");

	free(vr);

	return 0;
}
