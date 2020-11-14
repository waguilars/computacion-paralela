#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

int main()
{
  int numbers[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
  int len = sizeof(numbers) / sizeof(numbers[0]);

  omp_set_num_threads(len);

#pragma omp parallel firstprivate(numbers)
  {
    int tid = omp_get_thread_num();
    int value = numbers[tid], res;

    bool is_prime = true;
    for (size_t i = 2; i < value; i++)
    {
      if ((value % i) == 0)
      {
        is_prime = false;
        break;
      }
    }

    if (is_prime)
      printf("%d es primo\n", value);
  }

  return 0;
}
