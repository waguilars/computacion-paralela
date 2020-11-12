/*Manejo de la clausula private y reduction(+:x) c*/
#include <stdio.h>
// #include <windows.h>
#include <omp.h>
int main()
{
  int x = 1000;
  int iam = 0, np = 1, i = 0, j = 0;
  omp_set_num_threads(4);

  printf("\n Antes de pragma parallel x=%d \n\n", x);

#pragma omp parallel private(iam, np, i) reduction(+: x)
  {
    np = omp_get_num_threads();
    iam = omp_get_thread_num();

    printf("Soy el thread %d, antes de actualizar, con x=%d \n", iam, x); // mensajito para que le de tiempo al master a poner x=999
    x = iam * 10;
    printf("\t\tSoy el thread %d, despues de actualizar, con x=%d \n", iam, x); //todos se quedan con el valor que ponga el thread que haga la iteracion i=10

  } //parallel

  printf("\n Despues de pragma parallel x=%d \n\n", x);
} //main