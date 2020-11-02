#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_temp(float arr[7][24], int rows, int cols)
{
  srand(time(NULL));

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {

      arr[i][j] = (float)rand() / ((float)RAND_MAX / 50);
      // printf("%.2f\t", arr[i][j]);
    }
    // printf("\n");
  }
}

int main()
{
  char *week_days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
  float temp[7][24];
  int rows = sizeof(temp) / sizeof(temp[0]);
  int cols = sizeof(temp[0]) / sizeof(temp[0][0]);

  fill_temp(temp, rows, cols);

  /* code */
  return 0;
}
