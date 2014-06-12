#include <stdio.h>
#include <stdlib.h>

double fatorial(int impar){
  int i;
  double valor = 1;
  for (i = 1; i <= impar; i++){
    valor = valor*i;
  }
  return valor;
}

int main(int argc, char *argv[]){
  int i, j, impar;
  double valor_calc;
  double extra;
  double valor = 0;
  int global_potencia = 8;
  double *x;
  double resultado_final;
  
  x = malloc(sizeof(double)*global_potencia);
  
  for (j = 0; j < 10; j++){    
  
    valor += 0.2;
    x[0] = valor;
    for(i = 1; i < global_potencia; i++){
      x[i] = x[i-1]*valor*valor;
    }
    
    for (i = 0; i < global_potencia; i++){
      impar = 2*i + 1;
      valor_calc = fatorial(impar);
      if (i%2 == 0){
	extra = x[i]/valor_calc;
      } else {
	extra = x[i]/valor_calc*-1;
      }
      printf("Extra: %.8f -- X[i]: %.2f -- Fatorial: %.2f\n", extra, x[i], valor_calc);
      resultado_final += extra;
    }

    printf("Resultado Final:\nSeno(%.0f) = %.4f\n", valor, resultado_final);
    resultado_final = 0;
  }
  for(i = 0; i < 50000; i++);
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

