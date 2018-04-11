#include <stdio.h>
#include <stdlib.h>

int main(){
  int N;
  char c;

  while(1){
    scanf("%c", &c);
    if(c == 'f') break;
    getchar();
    if(c != 'p'){
      scanf("%d", &N);
      getchar();
    } 
    printf("c = %c N = %d\n", c, N);
  }
  
  return 0;
}