#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define n 10

// Run with 5 threads
int main(int argc, char *argv[])
{
  int rank, size, max_age, min_age, younger = 0, retired = 0;
  int people[n];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {

    // Generate random years 1 - 90
    // srand(time(NULL));
    for (size_t i = 0; i < n; i++)
    {
      people[i] = (rand() + 1) % 90;
      printf("%d ", people[i]);
    }

    for (size_t i = 0; i < size; i++)
      MPI_Send(people, n, MPI_INT, i, 0, MPI_COMM_WORLD);

    // Compute mean
    int mean = 0;
    for (size_t i = 0; i < n; i++)
      mean += people[i];

    mean = round(mean / n);
    printf("\nLa edad media es: %d\n", mean);
  }
  else
  {
    MPI_Recv(people, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // printf("pid %d recibio %d\n", rank, people[1]);
    switch (rank)
    {
    case 1:
      // Compute min age
      min_age = people[0];
      for (size_t i = 0; i < n; i++)
      {
        if (people[i] < min_age)
          min_age = people[i];
      }
      printf("La edad mas baja es: %d\n", min_age);
      break;
    case 2:
      // Compute max age
      max_age = people[0];
      for (size_t i = 0; i < n; i++)
      {
        if (people[i] > max_age)
          max_age = people[i];
      }
      printf("La edad mas alta es: %d\n", max_age);
      break;
    case 3:
      // compute how many people are retired
      for (size_t i = 0; i < n; i++)
      {
        if (people[i] > 60)
          retired += 1;
      }
      printf("Las personas jubiladas son: %d\n", retired);
      break;
    case 4:
      // Compute how many people are under 18 years
      for (size_t i = 0; i < n; i++)
      {
        if (people[i] < 18)
          younger += 1;
      }
      printf("Las personas menores de edad son: %d\n", younger);
      break;
    }
  }

  MPI_Finalize();
  return 0;
}
