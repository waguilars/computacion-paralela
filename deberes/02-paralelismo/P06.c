#include <stdio.h>
#include <omp.h>
#include <stdbool.h>

/**
 *  @author Wilson Aguilar
 * Elabore un programa que permita introducir un arreglo de 8 elementos de tipo carácter,
 * el programa mostrará un arreglo en donde muestre un:
 *  1 para las vocales
 *  2 para símbolos entre 0 y 9
 *  0 para el resto de caracteres
 */
int main()
{
  char characters[8];
  // char characters[8] = {'a', 'b', '5', 'y', 'c', 'i', '8', 'f'};

  int len = sizeof(characters) / sizeof(characters[0]);

  char values[len];

  for (size_t i = 0; i < len; i++)
  {
    printf("Ingrese el %ld elemento: \n", i);
    scanf(" %c", &characters[i]);
  }
  omp_set_num_threads(3);
#pragma omp parallel for firstprivate(characters) shared(values)
  for (size_t i = 0; i < len; i++)
  {
    char c = characters[i];
    bool vowels_upper = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    bool vowels_lower = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    bool numbers = (c >= 48 && c <= 57);

    /* Check vowels */
    if (vowels_lower || vowels_upper)
      values[i] = 1;
    else if (numbers)
      values[i] = 2;
    else
      values[i] = 0;
  }

  for (size_t i = 0; i < len; i++)
  {
    printf("%c\t", characters[i]);
  }
  printf("\n");
  for (size_t i = 0; i < len; i++)
  {
    printf("%d\t", values[i]);
  }

  return 0;
}
