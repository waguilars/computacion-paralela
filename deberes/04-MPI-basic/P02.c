#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// Run with 4 threads
int main(int argc, char *argv[])
{
  int rank, size, n1, n2, mult, exp, div, rest;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    n1 = 5; //rand() % 10;
    n2 = 3;  //rand() % 10;

    for (size_t i = 1; i < 4; i++)
    {
      MPI_Send(&n1, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&n2, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    printf("tid %d -> %d : %d\t\n", rank, n1, n2);
  }
  else
  {
    MPI_Recv(&n1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&n2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  switch (rank)
  {
  case 0:
    mult = 0;
    for (size_t i = 0; i < n2; i++)
      mult += n1;
    printf("%d x %d = %d\n", n1, n2, mult);
    break;
  case 1:
    exp = n1;
    for (size_t i = 1; i < n2; i++)
      exp *= n1;
    printf("Potencia de %d elevado a %d es %d\n", n1, n2, exp);
    break;
  case 2:
    div = 0;
    rest = n1;

    while (rest >= n2)
    {
      div++;
      rest = rest - n2;
    }
    printf("%d / %d = %d y sobra %d\n",n1, n2, div, rest);
    break;
  case 3:
    div = 0;
    rest = n1;

    while (rest >= n2)
    {
      div++;
      rest = rest - n2;
    }
    printf("%d %% %d = %d\n",n1, n2, rest);
    break;
    break;
  }

  MPI_Finalize();
  return 0;
}
