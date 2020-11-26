#include <stdio.h>
#include <string.h>
#include <omp.h>

int main()
{
  char *code = "7702004003508";
  int len = strlen(code);
  int total = 0;

  omp_set_num_threads(12);
#pragma omp parallel firstprivate(code) shared(total)
  {
    int tid = omp_get_thread_num();
    int val = code[tid] - '0';

    // printf("->%d - %d \n", tid, val);
#pragma omp critical
    {
      if ((tid + 1) % 2 == 0)
        total += val * 3;
      else
        total += val * 1;
    }

#pragma omp barrier
#pragma omp master
    {
      val = code[12] - '0';
      total += val;
      if (total % 10 == 0)
        printf("El codigo es correcto.\n");
      else
        printf("El codigo esta mal.\n");
    }
  }

  return 0;
}
