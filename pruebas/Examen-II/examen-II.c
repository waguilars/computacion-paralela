#include <mpi.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/**
 * @author Wilson Aguilar
 * Ejercicio 18
 * 4 Hilos
 */ 

int main(int argc, char *argv[])
{
  int rank, size;
  char str[64], symb;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0)
  {
    // init values
    strcpy(str, "Hola mundo 11445");
    symb = ';';
  }

  MPI_Bcast(&str, 64, MPI_CHAR, 0, MPI_COMM_WORLD);
  MPI_Bcast(&symb, 1, MPI_CHAR, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {
    int len = strlen(str) * 2;
    char new_str[len];

    for (size_t i = 0; i < len; i++)
    {
      if (i % 2 == 0)
        new_str[i] = str[i / 2];
      else
        new_str[i] = symb;
    }
    new_str[len] = '\0';
    printf("a) %s\n", new_str);
  }

  if (rank == 1)
  {
    for (size_t i = 0; i < strlen(str); i++)
    {
      if (str[i] == ' ')
        str[i] = symb;
    }

    MPI_Send(&str, strlen(str), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  if (rank == 2)
  {
    for (size_t i = 0; i < strlen(str); i++)
    {
      if (isdigit(str[i]))
        str[i] = symb;
    }
    MPI_Send(&str, strlen(str), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  if (rank == 3)
  {
    int spaces = (int)strlen(str) / 3;
    int len = strlen(str) + spaces;
    int aux = 0, j = 0;

    char new_str[len];

    for (size_t i = 0; i < len; i++)
    {

      if (aux == 3)
      {
        new_str[i] = symb;
        aux = 0;
      }
      else
      {
        new_str[i] = str[j];
        j++;
        aux++;
      }
    }

    new_str[len] = '\0';
    MPI_Send(&new_str, len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  char str_b[64], str_c[64], str_d[64];
  if (rank == 0)
  {
    /* code */
    MPI_Recv(&str_b, strlen(str), MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("b) %s\n", str_b);

    MPI_Recv(&str_c, strlen(str), MPI_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("c) %s\n", str_c);

    MPI_Recv(&str_d, 64, MPI_CHAR, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("d) %s\n", str_d);
  }

  MPI_Finalize();

  return 0;
}
