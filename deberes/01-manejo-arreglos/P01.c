
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char str1[256], str2[256];
  int idx;

  printf("Ingrese la primera cadena: ");
  fgets(str1, sizeof(str1), stdin);
  str1[strlen(str1) - 1] = '\0';

  printf("Ingrese la segunda cadena: ");
  fgets(str2, sizeof(str2), stdin);
  str2[strlen(str2) - 1] = '\0';

  if (strstr(str1, str2) != NULL)
  {
    idx = strcspn(str1, str2);
    printf("The index is: %d\n", idx);
  }
  else
  {
    printf("The second word does not match with the first one.\n");
  }

  return 0;
}
