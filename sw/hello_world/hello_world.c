#include <stdio.h>
#include <stdlib.h>

#define TAMMEM     5242884

volatile int* _lock = (int*)TAMMEM;

void glock()
{
     while (*_lock) ;
     return;
}

// free gloal lock
void flock()
{
     *_lock = 0;
     return;
}

int main(int argc, char *argv[]){
  int i;
  
  int *vetor;
  
  vetor = malloc(sizeof(int)*10);
  
  vetor[4] = 30;
  vetor[3] = 10;
  i = vetor[4];
  
  glock();
  puts("Estou aqui!");
  flock();

  for(i = 0; i < 50000; i++);
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

