#include "ordenacao.h"

int main(int argc, char* argv[]) {

	srand(time(NULL));
	int N=100000;
	int *vi, *vh, *vm, *vq1, *vq2, *vq3, *vq4, *vq5;
	clock_t c1, c2;
	
	gera_vetor_aleatorio(N, &vi);

	c1 = clock();
	insertionsort(vi, N);
	c2 = clock();
	double is_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Insertion  : %lf\n", is_running);

	clona_vetor(N, &vh, vi);
	c1 = clock();
	heapsort(vh, N);
	c2 = clock();
	double hs_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Heap       : %lf\n", hs_running);

	clona_vetor(N, &vm, vi);
	free(vh);
	c1 = clock();
	mergesort(vm, 0, N-1);
	c2 = clock();
	double ms_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Merge      : %lf\n", ms_running);

	clona_vetor(N, &vq1, vi);
	free(vm);
	c1 = clock();
	quicksort(vq1, 0, N-1, 0);
	c2 = clock();
	double qs1_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Quick (ini): %lf\n", qs1_running);

	clona_vetor(N, &vq2, vi);
	free(vq1);
	c1 = clock();
	quicksort(vq2, 0, N-1, 1);
	c2 = clock();
	double qs2_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Quick (fim): %lf\n", qs2_running);

	clona_vetor(N, &vq3, vi);
	free(vq2);
	c1 = clock();
	quicksort(vq3, 0, N-1, 2);
	c2 = clock();
	double qs3_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Quick (mid): %lf\n", qs3_running);

	clona_vetor(N, &vq4, vi);
	free(vq3);
	c1 = clock();
	quicksort(vq4, 0, N-1, 3);
	c2 = clock();
	double qs4_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Quick (med): %lf\n", qs4_running);

	clona_vetor(N, &vq5, vi);
	free(vq4);
	c1 = clock();
	quicksort(vq5, 0, N-1, 4);
	c2 = clock();
	double qs5_running = (c2-c1)/(double)CLOCKS_PER_SEC;
	printf("Quick (ale): %lf\n\n", qs5_running);

	free(vq5);
	free(vi);

	return 0;
}
