char *substr(char *str, char *str2, int start, int end)
{
  int i = 0;
  while (i < end - start)
  {
    str2[i] = str[start + i];
    i++;
  }

  return str2;
}