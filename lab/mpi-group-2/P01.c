#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define n 5

int main(int argc, char *argv[])
{
  int rank, size;
  int mtx[n][n], vec[n], mtx_vec[n], test_vector[n] = {1, 1, 1, 1, 1};
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    printf("La matriz es:\n");
    for (size_t i = 0; i < n; i++)
      for (size_t j = 0; j < n; j++)
        mtx[i][j] = rand() % 5;

    // put test vector in 2 columns
    for (size_t i = 0; i < n; i++)
    {
      mtx[i][2] = test_vector[i];
      mtx[i][4] = test_vector[i];
    }

    // put test vector in 1 row
    for (size_t i = 0; i < n; i++)
      mtx[3][i] = test_vector[i];

    // print vector
    for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        printf("%d\t", mtx[i][j]);
      }
      printf("\n");
    }

  }

  if (rank == 1)
  {
    printf("el vector es:\n");
    for (size_t i = 0; i < n; i++)
    {
      vec[i] = rand() % 5;
      printf("%d\t", test_vector[i]);
    }
    printf("\n");
  }

  MPI_Bcast(&mtx, n * n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&vec, n, MPI_INT, 1, MPI_COMM_WORLD);

  // Check rows
  bool is_equal = true;
  for (size_t i = 0; i < n; i++)
  {
    if (mtx[rank][i] != test_vector[i])
    {
      is_equal = false;
      break;
    }
  }

  if (is_equal)
    printf("El vector aparece en la fila %d\n", rank);

  // check cols
  is_equal = true;
  for (size_t i = 0; i < n; i++)
  {
    if (mtx[i][rank] != test_vector[i])
    {
      is_equal = false;
      break;
    }
  }

  if (is_equal)
    printf("El vector aparece en la columna %d\n", rank);

  MPI_Finalize();
  return 0;
}
