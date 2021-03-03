#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

int main(int argc, char *argv[])
{
  int rank, size;
  int mtx[N][N];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        mtx[i][j] = rand() % 20;

    for (size_t i = 0; i < N; i++)
    {
      for (size_t j = 0; j < N; j++)
        printf("%d\t", mtx[i][j]);
      printf("\n");
    }
  }

  MPI_Bcast(&mtx, N * N, MPI_INT, 0, MPI_COMM_WORLD);

  int sum = 0;
  switch (rank)
  {
  case 0:
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        if (i == j)
          sum += mtx[i][j];
    break;
  case 1:
    for (size_t i = 0; i < N; i++)
      sum += mtx[N - 1][i];
    break;
  case 2:
    for (size_t i = 0; i < N; i++)
      sum += mtx[i][N - 1];
    break;
  }

  int res[3];
  MPI_Gather(&sum, 1, MPI_INT, &res, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {
    printf("0 -> diagonal, 1 -> ultima fila, 2 -> ultima columna\n");
    for (size_t i = 0; i < 3; i++)
      printf("%d -> %d\n", i, res[i]);
  }

  MPI_Finalize();

  return 0;
}
