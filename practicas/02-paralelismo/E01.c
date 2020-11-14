#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

void fill_temp(double arr[7][24], int rows, int cols)
{
  srand48(time(NULL));

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      arr[i][j] = (double)drand48() * (50.0 - 5.0) + 5.0;
    }
  }
}

int main()
{
  char *week_days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

  bool days_over30[7] = {false, false, false, false, false, false, false};

  double temp[7][24];
  int days = sizeof(temp) / sizeof(temp[0]);
  int hours = sizeof(temp[0]) / sizeof(temp[0][0]);

  fill_temp(temp, days, hours);

  // Variables for the excercise
  double min_week_temp = temp[0][0], max_week_temp = temp[0][0];
  double min_day_temp[days], max_day_temp[days];
  double mean_week_temp = 0;
  double mean_day_temp[days];

  omp_set_num_threads(4);

#pragma omp parallel shared(temp, min_day_temp, max_day_temp, mean_week_temp, mean_day_temp)
  {
    int threads = omp_get_num_threads();
    int thread = omp_get_thread_num();

    for (size_t i = 0; i < days; i++)
    {
      double aux_min_temp = temp[i][0];
      double aux_max_temp = temp[i][0];
      double aux_mean_temp = 0;

      for (size_t j = 0; j < hours; j++)
      {
        switch (thread)
        {
        case 0:
          /* Get Max and min temp week */
          if (temp[i][j] < min_week_temp)
            min_week_temp = temp[i][j];

          if (temp[i][j] > max_week_temp)
            max_week_temp = temp[i][j];

          break;
        case 1:
          /* Get max and min temp day */
          if (temp[i][j] < aux_min_temp)
          {
            aux_min_temp = temp[i][j];
            min_day_temp[i] = aux_min_temp;
          }

          if (temp[i][j] > aux_max_temp)
          {
            aux_max_temp = temp[i][j];
            max_day_temp[i] = aux_max_temp;
          }

          break;
        case 2:
          /* mean week temp */
          mean_week_temp += temp[i][j];

          break;
        case 3:
          /* mean temp day */
          mean_day_temp[i] += temp[i][j];
          break;
        }
      }
    }
  }

  mean_week_temp /= days * hours;

  for (size_t i = 0; i < days; i++)
  {
    if ((mean_day_temp[i] /= hours) > 30)
      days_over30[i] = true;
  }

  printf("Max and min temp per day:\n");
  for (size_t i = 0; i < days; i++)
  {
    printf("* %s:\n\tmin: %.2f°c, max: %.2f°c, mean: %.2f°c\n", week_days[i], min_day_temp[i], max_day_temp[i], mean_day_temp[i]);
  }

  printf("\n* All the week:\n\tmin: %.2f°c, max: %.2f°c, mean: %.2f°c\n", min_week_temp, max_week_temp, mean_week_temp);

  printf("\nDays when the temp was over 30°c: \n");
  for (size_t i = 0; i < days; i++)
  {
    if (days_over30[i])
    {
      printf("\t* %s\n", week_days[i]);
    }
  }

  return 0;
}
