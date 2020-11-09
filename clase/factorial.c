#include <stdio.h>
#include <omp.h>

int main()
{
  int n[] = {5, 6, 7, 20, 50};

  omp_set_num_threads(5);

#pragma omp parallel firstprivate(n)
  {
    int tid = omp_get_thread_num();
    long long unsigned fact = 1;
    int value = n[tid];

    // factorial
    for (int i = 1; i <= value; i++)
    {
      fact = fact * i;
    }

    printf("%d -> %llu\n", value, fact);
  }
  return 0;
}
