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

int main()
{
  int n = 3,   // digits number
      x = 407, // number to eval
      sum = 0;
  int *digits = split_in_digits(x, n);

  omp_set_num_threads(n);

    // #pragma omp parallel for shared(digits, n) reduction(+ \
//                                                      : sum)
  // for (size_t i = 0; i < n; i++)
  // {
  //   int tid = omp_get_thread_num();
  //   int cube = pow(digits[i], 3);
  //   printf("Thread %d: %d^3 = %d\n", tid, digits[i], cube);
  //   sum += cube;
  // }

#pragma omp parallel firstprivate(digits) reduction(+ \
                                                    : sum)
  {
    int tid = omp_get_thread_num();
    // printf("d -> %d \n", digits[tid]);
    int cube = pow(digits[tid], 3);
    sum = cube;
  }

  printf("Suma: %d\n", sum);

  if (x == sum)
    printf("El valor %d es cubo perfecto!\n", x);
  else
    printf("El valor %d no es un cubo perfecto!! :(\n", x);

  return 0;
}
