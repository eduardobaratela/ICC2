#include <stdio.h>
#include <stdlib.h>


int stdev(int** A, int ra, int rb, int ca, int cb, int N, int T) {

	int i,j;
	double mean = 0.0, std = 0.0;
	for (i = ra; i <= rb; i++) {
		for (j = ca; j <= cb; j++) {
			mean += A[i][j];
		}
	}
	mean = mean/(N*N);
		
	for (i = ra; i <= rb; i++) {
		for (j = ca; j <= cb; j++) {
			std += (A[i][j] - mean) *(A[i][j] - mean);
		}
	}
	std = std/(N*N);
	return (std < T);
}


void imgseg(int** A, int** S, int ra, int rb, int ca, int cb, int N) {

	if (N == 1) return; // caso base

	int rm = (int) ((ra+rb)/2.0); // ponto medio da linha
	int cm = (int) ((ca+cb)/2.0); // ponto medio da linha

	// Q1 - (ra - rm), (ca - cm)
	imgseg(A, S, ra, rm, ca, cm, N/2);
	// Q2 - (ra - rm), (cm+1 - cb)
	imgseg(A, S, ra, rm, cm+1, cb, N/2);
	// Q3 - (rm+1 - rb), (ca - cm)
	imgseg(A, S, rm+1, rb, ca, cm, N/2);
	// Q4 - (rm+1 - rb), (cm+1, cb)
	imgseg(A, S, rm+1, rb, cm+1, cb, N/2);

	int i,j;

	printf("(%d, %d), (%d, %d)\n", ra,rb, ca,cb);
	int label = S[ra][rb];
	int T = 15;
	if (stdev(A, ra, rb, ca, cb, N, T)) {
		for (i = ra; i <= rb; i++) {
			for (j = ca; j <= cb; j++) {
				S[i][j] = label;
				//printf("%d ", S[i][j]);
			}
			//printf("\n");
		}
		//printf("\n");
	}
	

}




int main(int argc, char* argv[]) {

	int N = 8;

	int i,j,k;

	int** A; // imagem
	int** S; // rotulos das regioes

	A = malloc(sizeof(int*) * N);
	S = malloc(sizeof(int*) * N);

	for (k = 1, i = 0; i < N; i++) {
		A[i] = malloc(sizeof(int)*N); 
		S[i] = malloc(sizeof(int)*N); 
		for (j = 0; j < N; j++, k++) {
			A[i][j] = rand()%16;	
			S[i][j] = k;	
		}
	}

	imgseg(A, S, 0, N-1, 0, N-1, N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++, k++) {
			printf("%03d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++, k++) {
			printf("%03d ", S[i][j]);
		}
		printf("\n");
	}

	return 0;
}
