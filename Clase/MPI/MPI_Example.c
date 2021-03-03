#include <mpi.h>
#include <stdio.h>

#define TAG 0

int main(int argc, char *argv[])
{
  int rank, size, length, n;
  char name[15];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    n = 10;
    // for (size_t thread = 1; thread < size; thread++)
      MPI_Send(&n, 1, MPI_INT, 1, TAG, MPI_COMM_WORLD);
  }



  if (rank != 0)
  {
    MPI_Recv(&n, 1, MPI_INT, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // TODO sacar media
  }
  


  printf("%d -> %d\n", rank, n);


  MPI_Finalize();

  return 0;
}
