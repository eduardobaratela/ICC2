#include <stdio.h>
#include <stdlib.h>


void Hanoi(int N, char orig, char dest, char inte) {

	printf("N = %d\n", N);
	if (N == 1) {
		printf("\tMova %c para %c\n", orig, dest);
	}
	else {
		Hanoi(N-1, orig, inte, dest);
		Hanoi(1  , orig, dest, inte);
		Hanoi(N-1, inte, dest, orig);
	}

}



int main(int argc, char* argv[]) {

	int N;
	printf("Numero de discos: ");
	scanf("%d", &N);

	Hanoi(N,'A','B','C');

	printf("\n");
	return 0;
}
