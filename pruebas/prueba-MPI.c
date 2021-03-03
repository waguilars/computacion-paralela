/**
 * @author Wilson Aguilar
 * Ejercicio 9
 * Calcular union e interseccion de 2 vectores char maximo 10
 * 1 vector con union A y B
 * 1 vector con interseccion A y B
 *
 * this program uses 2 threads
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define n 10

int main(int argc, char *argv[])
{
  int rank, size, count = 0;
  char A[n], B[n], vinterseccion[n], vunion[n * 2];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    printf("Vector A:\n");
    for (size_t i = 0; i < n; i++)
    {
      A[i] = rand() % (122 - 97 + 1) + 97;
      printf("%c ", A[i]);
    }
    printf("\n");
  }

  if (rank == 1)
  {
    printf("Vector B:\n");
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
    {
      B[i] = rand() % (122 - 97 + 1) + 97;
      printf("%c ", B[i]);
    }
    printf("\n");
  }

  MPI_Bcast(&A, n, MPI_CHAR, 0, MPI_COMM_WORLD);
  MPI_Bcast(&B, n, MPI_CHAR, 1, MPI_COMM_WORLD);

  switch (rank)
  {
  case 0:

    for (size_t i = 0; i < n; i++)
    {
      vunion[i] = A[i];
      vunion[n + i] = B[i];
    }
    vunion[20] = '\0';
    printf("Union:\n");
    for (size_t i = 0; i < strlen(vunion); i++)
      printf("%c ", vunion[i]);

    printf("\n");
    break;

  case 1:
    for (size_t i = 0; i < n; i++)
    {
      for (size_t j = 0; j < n; j++)
      {
        if (A[i] == B[j])
        {
          vinterseccion[count] = A[i];
          count++;
          break;
        }
      }
    }

    printf("\nInterseccion: \n");
    if (strlen(vinterseccion) == 0)
      printf("No hay interseccion\n");
    for (size_t i = 0; i < count; i++)
      printf("%c ", vinterseccion[i]);

    break;
  }

  MPI_Finalize();
  return 0;
}
