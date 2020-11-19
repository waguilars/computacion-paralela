#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int *split_in_digits(int number, int digits)
{
  //Get number of digits

  int *digits_array = (int *)malloc(sizeof(int) * digits);

  for (size_t i = 0; i < digits; i++)
  {
    *(digits_array + i) = number % 10;
    number = number / 10;
  }

  return digits_array;
}

int find_primes(int x, int n)
{
  int sum = 0;
  int *digits = split_in_digits(x, n);

  omp_set_num_threads(n);
#pragma omp parallel for shared(digits, n) reduction(+ \
                                                     : sum)
  for (size_t i = 0; i < n; i++)
  {
    int tid = omp_get_thread_num();
    int cube = pow(digits[i], 3);
    // printf("Thread %d: %d^3 = %d\n", tid, digits[tid], cube);
    sum += cube;
  }

  // printf("Suma: %d\n", sum);

  return sum;
}

int main()
{

  for (size_t i = 1000; i <= 9999; i++)
  {
    int sum = find_primes(i, 4);
    if (i == sum)
      printf("El valor %ld es cubo perfecto!\n", i);

    // printf("El valor %ld no es un cubo perfecto!! :(\n", i);
  }
  return 0;
}
