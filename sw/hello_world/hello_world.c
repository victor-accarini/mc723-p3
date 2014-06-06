#include <stdio.h>

int main(int argc, char *argv[]){
  int i;
  for(i=0;i<10;i++)
    printf("Hi from processor MIPS! %d \n", i);

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

