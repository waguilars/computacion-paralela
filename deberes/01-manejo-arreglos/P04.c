#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void fill_temp(float arr[7][24], int rows, int cols)
{
  srand48(time(NULL));

  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {

      arr[i][j] = drand48() * (50.0 - 5.0) + 5.0;
      // printf("%.2f\t", arr[i][j]);
    }
    // printf("\n");
  }
}

int main()
{
  char *week_days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

  bool days_over30[7] = {false, false, false, false, false, false, false};

  float temp[7][24];
  int rows = sizeof(temp) / sizeof(temp[0]);
  int cols = sizeof(temp[0]) / sizeof(temp[0][0]);

  fill_temp(temp, rows, cols);

  // Eval
  float min_week_temp, max_week_temp, min_day_temp[7], max_day_temp[7], mean_day_temp[7];
  double mean_week_temp;
  // int days_over30 = 0;

  min_week_temp = temp[0][0];
  max_week_temp = temp[0][0];

  for (size_t i = 0; i < rows; i++)
  {
    min_day_temp[i] = temp[i][0];
    max_day_temp[i] = temp[i][0];

    mean_day_temp[i] = 0;

    // Get max and min temp per day
    for (size_t j = 0; j < cols; j++)
    {
      // printf("%.2f   ", temp[i][j]);
      //Get min temp per day
      if (temp[i][j] < min_day_temp[i])
      {
        min_day_temp[i] = temp[i][j];
      }
      //Get max temp per day
      if (temp[i][j] > max_day_temp[i])
      {
        max_day_temp[i] = temp[i][j];
      }

      // sum of all temps per day
      mean_day_temp[i] += temp[i][j];

      //Get min temp for week
      if (temp[i][j] < min_week_temp)
      {
        min_week_temp = temp[i][j];
      }
      //Get max temp for week
      if (temp[i][j] > max_week_temp)
      {
        max_week_temp = temp[i][j];
      }
    }

    //get mean temp of the day
    mean_day_temp[i] = mean_day_temp[i] / cols;

    // Sum mean temps of all days
    mean_week_temp += mean_day_temp[i];

    // Cheack days when the mean temp is over 30°c
    if (mean_day_temp[i] > 30)
    {
      days_over30[i] = true;
    }

    // printf("\n");
  }

  //Get mean temp of the week
  mean_week_temp = mean_week_temp / rows;

  // Print result
  printf("Max and min temp per day:\n");
  for (size_t i = 0; i < rows; i++)
  {
    printf("* %s:\n\tmin: %.2f°c, max: %.2f°c, mean: %.2f°c\n", week_days[i], min_day_temp[i], max_day_temp[i], mean_day_temp[i]);
  }

  printf("\n* All the week:\n\tmin: %.2f°c, max: %.2f°c, mean: %.2f°c\n", min_week_temp, max_week_temp, mean_week_temp);

  printf("Days when the temp was over 30°c: \n");
  for (size_t i = 0; i < rows; i++)
  {
    if (days_over30[i])
    {
      printf("\t* %s\n", week_days[i]);
    }
  }

  return 0;
}
