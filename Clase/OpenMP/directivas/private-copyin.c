/*Manejo de la clausula private y copyin c*/
#include <stdio.h>
// #include <windows.h>
#include <unistd.h>
#include <omp.h>

int main()
{
  int x = 9999;
  int iam = 0, np = 1, i = 0, j = 0;
  omp_set_num_threads(4);
#pragma omp parallel private(iam, np, i) copyin(x) //sin el copyin, en cada thread salvo el master, el valor es x=0
  {
    np = omp_get_num_threads();
    iam = omp_get_thread_num();
    usleep(1);
    printf("Soy el thread %d, antes de actualizar, con x=%d \n", iam, x); // mensajito para que le de tiempo al master a poner x=9999
    x = iam * 1000;
    printf("\t\tSoy el thread %d, despues de actualizar, con x=%d \n", iam, x);

  } //parallel

  printf("\n Despues de pragma parallel x=%d \n\n", x);
} //main
