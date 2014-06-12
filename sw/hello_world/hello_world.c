#include <stdio.h>
#include <stdlib.h>

#define LOCK     5242884
#define FATORIAL 5242888

volatile int* _lock = (int*)LOCK;
volatile int* _fatorial = (int*)FATORIAL;

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
  int i, valor_calc, impar;
  static int global_cpuid = 0;
  static int global_potencia = 12;
  static int valor = 2;
  int local_cpuid;
  int tam_trabalho;
  static int *x;
  
  //Obtendo o valor do core
  glock();
  local_cpuid = global_cpuid;
  global_cpuid++;
  printf("Core %d está funcionando!\n", local_cpuid);
  flock();

  while(global_cpuid != 8);//Barreira
  
  //Divisão do trabalho
  tam_trabalho = global_potencia/global_cpuid;
  
  if (local_cpuid == 0){
    x = malloc(sizeof(int)*global_potencia);
    
    x[0] = valor;
    for(i = 1; i < global_potencia; i++){
      x[i] = x[i-1]*valor*valor;
    }
  }

  if (local_cpuid < global_cpuid - 1){
    for (i = tam_trabalho*local_cpuid; i < tam_trabalho*(local_cpuid+1); i++){
      impar = 2*i + 1;
      valor_calc = *(_fatorial+impar);
    }
  } else {
    for (i = tam_trabalho*local_cpuid; i < tam_trabalho*(local_cpuid+1) + global_potencia%global_cpuid; i++){
      impar = 2*i + 1;
      valor_calc = *(_fatorial+impar);
    }
  }

  glock();
  printf("Core %d:\nValor:%d\n", local_cpuid, valor);
  flock();

  
  
  
  for(i = 0; i < 50000; i++);
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

