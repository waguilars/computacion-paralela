#include <mpi.h>
#include <stdio.h>
#include <math.h>

int fact(int a)
{
  if (a == 0)
    return 1;
  return a * fact(a - 1);
}

int main(int argc, char *argv[])
{
  int rank, size, n, rank_sum = 0, total = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  n = rank + 1;
  for (size_t i = 1; i <= n; i++)
    rank_sum += pow(n, fact(i));

  printf("th -> %d: %d\n", rank, rank_sum);
  MPI_Reduce(&rank_sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0)
    printf("El total es: %d\n", total);

  MPI_Finalize();
  return 0;
}
