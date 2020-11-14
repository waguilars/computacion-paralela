#include <stdio.h>
#include <omp.h>

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
