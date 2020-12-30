#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  int myrank, size, length;
  char name[15];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Get_processor_name(name, &length);

  printf("[PC-%s] Thread %d de %d\n", name, myrank, size);
  MPI_Finalize();

  return 0;
}
