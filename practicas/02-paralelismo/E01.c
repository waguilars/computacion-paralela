#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

void fill_temp(float arr[7][24], int rows, int cols)
{
  srand48(time(NULL));

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      arr[i][j] = drand48() * (50.0 - 5.0) + 5.0;
    }
  }
}

int main()
{
  char *week_days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

  bool days_over30[7] = {false, false, false, false, false, false, false};

  float temp[7][24];
  int days = sizeof(temp) / sizeof(temp[0]);
  int hours = sizeof(temp[0]) / sizeof(temp[0][0]);

  fill_temp(temp, days, hours);

  // Variables for the excercise
  float min_week_temp = temp[0][0], max_week_temp = temp[0][0];
  float min_day_temp[days], max_day_temp[days];
  float mean_week_temp;
  float mean_day_temp[days];

  omp_set_num_threads(5);

#pragma omp parallel shared(temp)
  {
    int threads = omp_get_num_threads();
    int thread = omp_get_thread_num();

    for (size_t i = 0; i < days; i++)
    {
      for (size_t j = 0; j < hours; j++)
      {
        switch (thread)
        {
        case 1:
          /* Get Max and min temp week */
          if (temp[i][j] < min_week_temp)
            min_week_temp = temp[i][j];

          if (temp[i][j] > max_week_temp)
            max_week_temp = temp[i][j];

          break;
        case 2:
          /* Get max and min temp day */
          break;
        case 3:
          /* mean week temp */
          break;
        case 4:
          /* mean temp day */
          break;
        case 5:
          /* days when the temp is over 30 */
          break;
        }
      }
    }
  }

  printf("\n* All the week:\n\tmin: %.2f°c, max: %.2f°c, mean: %.2f°c\n", min_week_temp, max_week_temp, mean_week_temp);

  return 0;
}
