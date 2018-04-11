#include <stdio.h>
#include <stdlib.h>

int busca_interpoladaRec(int* vet, int ini, int fim, int tam, int chave){
	if(ini > fim) return -1;

	int meio = ini + ((fim-ini) * (chave-vet[ini]))/(vet[fim] - vet[ini]);
	printf("meio = %d\n", meio);
	if(meio < 0 || meio >= tam) return -1;
	if(chave > vet[meio]) return busca_interpoladaRec(vet, meio+1, fim, tam, chave);
	if(chave < vet[meio]) return busca_interpoladaRec(vet, ini, meio-1, tam, chave);
	else return meio; //chave = vet[meio]
}

int busca_interpoladaIter(int* vet, int tam, int chave){
	int ini = 0;
	int fim = tam -1;
	while(ini <= fim){
		int meio = ini + ((fim-ini) * (chave-vet[ini]))/(vet[fim] - vet[ini]);
		if(chave > vet[meio]) ini = meio + 1;
		else if(chave < vet[meio]) fim = meio - 1;
		else return meio;
	}

	return -1;
}

int main(){
	int vec[21] = {1, 1, 2, 3, 5, 6, 8, 9, 12, 30, 15, 36, 89, 0, 7, 66, 10, 3, 3, 3, 3};
	int resp1 = busca_interpoladaRec(vec, 0, 9, 21, 30);
	//int resp2 = busca_interpoladaIter(vec, 10, 2);

	printf("%d\n", resp1);

	return 0;
}
