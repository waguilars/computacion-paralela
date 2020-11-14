#include <stdio.h>
#include <omp.h>
/* Escribir un programa que permita calcular el MCM y el MCD de 2 *Números enteros positivos. */

int mcd(int a, int b)
{
  if (a > b)
    return a % b;
  else
    return b % a;
}

int mcm(int a, int b)
{
  return a * b / mcd(a, b);
}

int main()
{
  
}
