#include <stdio.h>
#include <stdlib.h>

int countrec;
int countite;

int FibRecursivo(int n) {
	countrec++;
	if (n == 1 || n == 2) {
		return 1;
	} else {
		return FibRecursivo(n-1) + FibRecursivo(n-2);
	}
}

int FibIterativo(int n) {
	int i;
	int soma = 1;
	int n1 = 1; // 1.o numero
	int n2 = 1; // 2.o numero
	countite++;
	for (i = 2; i < n; i++) {
		soma = n1 + n2; // proximo numero
		n1 = n2; // 1.o vira o segundo
		n2 = soma; // 2.o vira o terceiro
		countite++;
	}
	return soma;
}


int main(int argc, char*argv[]) {

	int N;
	printf("Sequencia de Fibonacci: ");
	scanf("%d", &N);

	int j;
	printf("Metodo iterativo:\n");
	for (j = 1; j <= N; j++) {
		//countite = 0;
		printf("%d (%d)\t", FibIterativo(j), countite);
	}

	printf("\n");
	printf("Metodo recursivo:\n");
	for (j = 1; j <= N; j++) {
		//countrec = 0;
		printf("%d (%d)\t", FibRecursivo(j), countrec);
	}

	printf("\n\n");

	return 0;
}
