
#include <stdio.h>
#include <string.h>

int main()
{
  char str1[256], str2[256];

  printf("Ingrese la primera cadena: ");
  fgets(str1, sizeof(str1), stdin);
  str1[strlen(str1) - 1] = '\0';

  printf("Ingrese la segunda cadena: ");
  fgets(str2, sizeof(str2), stdin);
  str2[strlen(str2) - 1] = '\0';

  if (strstr(str1, str2) != NULL)
  {
    for (int i = 0; i < strlen(str1); i++)
    {
      if (str1[i] == str2[0])
      {
        char new_str[64];
        memcpy(new_str, &str1[i], strlen(str2));
        if (strcmp(new_str, str2) == 0)
        {
          printf("The first occurence is in the index: %d\n", i);
          for (size_t j = 0; j < strlen(str1); j++)
          {
            if (j >= i && j <= i + strlen(str2))
            {
              printf("");
            }
            else
            {
              printf("%c", str1[j]);
            }
          }

          break;
        }
      }
    }
  }
  else
  {
    printf("The second word does not match with the first one.\n");
  }

  return 0;
}
