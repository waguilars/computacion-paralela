#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  int rank, size, days, months, year, weeks;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    days = rand() % 1000;
    for (size_t i = 1; i < size; i++)
      MPI_Send(&days, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  if (rank == 1)
  {
    MPI_Recv(&days, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    year = days / 360;
    printf("%d son %d años\n", days, year);
    MPI_Send(&year, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  }

  if (rank == 2)
  {
    MPI_Recv(&days, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    months = days / 30;
    printf("%d son %d meses\n", days, months);
    MPI_Send(&months, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  }

  if (rank == 3)
  {
    MPI_Recv(&days, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    weeks = days / 7;
    printf("%d son %d semanas\n", days, weeks);
    MPI_Send(&weeks, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
  }

  if (rank == 4)
  {
    MPI_Recv(&days, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&year, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&months, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&weeks, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("%d dias son %d meses, %d semanas, %d años\n", days, months, weeks, year);
  }

  MPI_Finalize();
  return 0;
}