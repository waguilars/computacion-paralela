#include <stdio.h>
#include <omp.h>
#include <string.h>
#include <ctype.h>

/**
 * @author Wilson Aguilar
 *
 * Ejercicio 24
 *
 * Escribir un programa donde dada una cadena y un carácter desde el teclado, realice lo siguiente:

a) Inserte el carácter entre cada letra de la cadena.
Ej: ’separar’ y ’,’ debería imprimir como resultado  ’s,e,p,a,r,a,r’

b) Reemplace todos los espacios por el carácter.
Ej: ’mi archivo de texto.txt’ y ’_’ debería imprimir la nueva cadena ’mi_archivo_de_texto.txt’

c) Reemplace todos los dígitos en la cadena por el carácter.
Ej: ’su clave es: 1540’ y ’X’ debería imprimir la nueva cadena ’su clave es: XXXX’

d) Inserte el carácter cada 3 dígitos en la cadena.
Ej. ’2552552550’ y ’.’ debería generar la nueva cadena e imprimir  ’255.255.255.0’
 *
 */

int main()
{
  char string[64] = "2552552550",
       symbol;

  // printf("Ingrese la cadena: \n");
  // fgets(string, 64, stdin);
  // string[strlen(string) - 1] = '\n';

  // printf("Ingrese un simbolo: \n");
  // scanf("%s", &symbol);

  symbol = '_';

  printf("Cadena: %s\n", string);
  printf("Simbolo: %c\n\n", symbol);

  omp_set_num_threads(4);
#pragma omp parallel sections firstprivate(string, symbol)
  {
#pragma omp section
    {
      int len = strlen(string) * 2;
      char new_string[len];
      // printf("%d\n", sizeof(new_string));
      for (size_t i = 0; i < sizeof(new_string); i++)
      {
        if (i % 2 == 0)
          new_string[i] = string[i / 2];
        else
          new_string[i] = symbol;

        // printf("%c", new_string[i]);
      }

      new_string[strlen(new_string) - 1] = '\0';
      printf("Literal a: %s\n", new_string);
    }

#pragma omp section
    {
      for (size_t i = 0; i < strlen(string); i++)
      {
        if (string[i] == ' ')
          string[i] = symbol;
      }

      printf("Literal b: %s\n", string);
    }

#pragma omp section
    {
      for (size_t i = 0; i < strlen(string); i++)
      {
        if (isdigit(string[i]))
          string[i] = symbol;
      }

      printf("Literal c: %s\n", string);
    }

#pragma omp section
    {
      int spaces = (int)strlen(string) / 3;
      int len = strlen(string) + spaces;
      int aux = 0, j = 0;

      char new_string[len];

      for (size_t i = 0; i < len; i++)
      {

        if (aux == 3)
        {
          new_string[i] = symbol;
          aux = 0;
        }
        else
        {
          new_string[i] = string[j];
          j++;
          aux++;
        }
      }

      new_string[len] = '\0';
      printf("Literal d: %s\n", new_string);
    }
  }

  return 0;
}
