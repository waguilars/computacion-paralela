#include <mpi.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int rank, size;
  char str1[64], str2[64];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    strcpy(str1, "Hola mundo");
    strcpy(str2, "Bue buye");
  }

  MPI_Bcast();

  MPI_Finalize();
  /* code */
  return 0;
}
