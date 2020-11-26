#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{
  int day, month, year;
  // printf("Ingrese el año: \n");
  // scanf("%d", &year);

  // printf("Ingrese el mes: \n");
  // scanf("%d", &month);

  // printf("Ingrese el dia: \n");
  // scanf("%d", &day);

  year = 1998;
  month = 3;
  day = 25;

  int sum = year + month + day;
  int magic_number = 0;
  omp_set_num_threads(4);
#pragma omp parallel firstprivate(sum) shared(magic_number)
  {
    char digits[4];
    sprintf(digits, "%d", sum);
    int tid = omp_get_thread_num();
#pragma omp critical
    magic_number += digits[tid] - '0';

#pragma omp barrier
#pragma omp single
    {
      // printf("%d\n", magic_number);
      if (magic_number > 9)
      {
        sprintf(digits, "%d", magic_number);
        magic_number = digits[0] - '0';
        magic_number += digits[1] - '0';
      }
    }
  }

  printf("El número mágico es: %d\n", magic_number);

  return 0;
}
