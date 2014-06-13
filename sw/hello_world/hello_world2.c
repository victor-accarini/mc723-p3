#include <stdio.h>
#include <stdlib.h>

#define LOCK     5242884
#define FATORIAL 5242888U

volatile int* _lock = (int*)LOCK;

double fatorial(int impar){
  int i;
  double valor = 1;
  for (i = 1; i <= impar; i++){
    valor = valor*i;
  }
  return valor;
}

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
  int i, j, impar, inicio, fim;
  double valor_calc, aux;
  double extra = 0;
  static int global_cpuid = 0;
  static int barreira = 0, barreira2 = 0;
  static int global_potencia = 8;
  static double valor = 0.2;
  int local_cpuid;
  int tam_trabalho;
  static double *x = NULL;
  static double resultado_final = 0;

  //Obtendo o valor do core
  glock();
  local_cpuid = global_cpuid;
  global_cpuid++;
  printf("Core %d está funcionando!\n", local_cpuid);
  flock();

  while(global_cpuid != 8);//Barreira

  for (j = 0; j < 50; j++){
    //Divisão do trabalho
    tam_trabalho = global_potencia/global_cpuid;

    if (local_cpuid == 0){
      if (x == NULL) x = malloc(sizeof(double)*global_potencia);

      x[0] = valor;
      for(i = 1; i < global_potencia; i++){
  x[i] = x[i-1]*valor*valor;
  barreira2++;
      }
      barreira2++;
    }

    while(barreira2 != 8);

    impar = 2*local_cpuid + 1;
    valor_calc = fatorial(impar);
    aux = valor_calc;
    if (local_cpuid%2 == 0){
      extra = x[local_cpuid];
      extra = extra/valor_calc;
    } else {
      extra = x[local_cpuid];
      extra = extra/valor_calc*-1;
    }

  //  glock();
  //  printf("Extra: %.8f -- X[%d]: %.2f -- Fatorial: %.2f\n", extra, local_cpuid, x[local_cpuid], aux);
  //  flock();
    //Calcular o seno  de x
    glock();
      resultado_final += extra;
      barreira++;
    flock();

    while(barreira != 8);//Barreira

    if (local_cpuid == 0){
      printf("Resultado Final:\nSeno(%f) = %.4f\n", valor, resultado_final);
    }

    glock();
    if (local_cpuid == 0){
      barreira2 = 0;
      resultado_final = 0;
      valor += 0.05;
      barreira = 0;
    }
    flock();

    while(barreira != 0);//Barreira

  }
  for(i = 0; i < 50000; i++);
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

