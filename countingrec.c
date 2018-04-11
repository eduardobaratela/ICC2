#include <stdio.h>
#include <stdlib.h>

typedef struct rec {
	int key;
	float value1;
	char value2[20];
} Rec;


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
	printf("\n");

	free(CA);
	free(vcopy);
}



void countingsort(int* v, int N) {

	int i, j; // indices

	// 1.o encontrar maior e menor chaves
	//     contagem = 'n'
	int max, min;
	max = min = v[0];
	for (i = 1; i < N; i++) {
		if (v[i] > max) max = v[i];
		if (v[i] < min) min = v[i];
	}

	// 2.o cria vetor auxiliar de contagem
	//     contagem = sizevec = 'k'
	int sizevec = (max-min)+1;
	int *C = (int *) calloc(sizevec, sizeof(int));	

	// 3.o - conta a frequencia de cada chave em 'v'
	for (i = 0; i < N; i++) {
		int pos = v[i]-min;		
		C[ pos ]++;
	}

	/* 4.o - percorre o vetor de contagem copiando os
		 valores de volta ao vetor original
		o indice 'j' percorre o vetor de contagem
		o indice 'i' percorre o vetor de saida
	*/
	i = 0;
	// para cada elemento do vetor de contagem
	printf("Vetor de contagem: \n");
	for (j = 0; j <= (max-min); j++) {
		printf("%d ", C[j]);
		// enquanto houver contagem positiva
		while (C[j] > 0) {
			v[i] = j +min; // ajusta para a chave minima
			C[j]--;
			i++;
		}
	}
	printf("\n");

	free(C);
}


int main(int argc, char* argv[]) {

	//int* v = malloc(sizeof(int)*atoi(argv[1]));
	
	int v[10] = {9, 13, 2, 13, 3, 3, -5, 2, 3, 8};

	int N = 10;
	countingsort(v, N);	

	int i;
	for (i = 0; i < N; i++) {
		printf("%d ", v[i]);
	}	
	printf("\n");

	Rec* vr = (Rec *)malloc(sizeof(Rec)*N);
	for (i = 0; i < N; i++) {
		vr[i].key = rand()% (int)(N/2.0);
		vr[i].value1 = (float)i+1;
		printf("%d (%.2f)\n", vr[i].key, vr[i].value1);
	}

	countingsort_rec(vr, N);

	printf("Counting sort com registros:\n");
	for (i = 0; i < N; i++) {
		printf("%d (%.2f)\n", vr[i].key, vr[i].value1);
	}	
	printf("\n");

	free(vr);

	return 0;
}
