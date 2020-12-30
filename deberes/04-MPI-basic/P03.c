#include <mpi.h>
#include <stdio.h>
#include <unistd.h> // Library for linux
//#include <windows.h> // Library for windows

// To generate the square use de threads quantity
int main(int argc, char *argv[])
{
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Sleep thread to print in order
  usleep(rank*100); // For linux

  for (size_t i = 0; i < size; i++)
  {
    if (i == rank)
      printf("- ");

    if (i > rank)
      printf("+ ");

    if (i < rank)
      printf("* ");
  }
  printf("\n");

  MPI_Finalize();

  return 0;
}
