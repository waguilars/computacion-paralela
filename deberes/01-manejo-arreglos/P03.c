#include <stdio.h>

int sum_diff(int *list, int size)
{

  int sum = 0;
  printf("| Sum\t|  Exp\t\t|  Total\t|\n");
  for (size_t i = 0; i < size - 1; i++)
  {
    printf("|%d\t|  %d - %d\t|  %d\t\t|\n", sum, list[i + 1], list[i], list[i + 1] - list[i]);
    sum += list[i + 1] - list[i];
  }

  return sum;
}

int main()
{
  int num_list[] = {1, 3, 6, 10};
  size_t length = sizeof(num_list) / sizeof(*num_list);

  int sum = sum_diff(num_list, length);

  printf("Total: %d\n", sum);

  return 0;
}
