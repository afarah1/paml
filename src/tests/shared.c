#include <math.h>
#include <stdbool.h>

static bool
double_equal(double a, double b, double epsilon)
{
  return fabs(a - b) < epsilon; 
}
