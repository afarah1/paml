#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../tools.c"

#define NVARS 3
#define TEST_SIZE 10

// x^2 + y^2
static double
xyz_square(double x[], int n)
{
 return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
}

// 2x (partial derivative of xyz_square in respect to x)
static double
x_2(double x[], int n)
{
  return 2 * x[0];
}

// 2y (partial derivative of xyz_square in respect to y)
static double
y_2(double x[], int n)
{
  return 2 * x[1];
}

// 2z (partial derivative of xyz_square in respect to y)
static double
z_2(double x[], int n)
{
  return 2 * x[2];
}

static bool
double_equal(double a, double b, double epsilon)
{
  return fabs(a - b) < epsilon; 
}

/*
 * Test gradientB using a simple three-variable function and backward
 * differences for the first variable, central for the second and forward for
 * the third.
 */
static int 
test_gradientB(void)
{
  int n = NVARS;
  double x[NVARS];
  double g[NVARS];
  double expected[NVARS];
  double space[NVARS * 2];
  int xmark[NVARS] = { -1, 0, 1 };

  for (int i = 0; i < TEST_SIZE; i++) {
    double eh = Small_Diff * (i + 1);
    x[0] = i;
    x[1] = i;
    x[2] = i;
    expected[0] = x_2(x, n);
    expected[1] = y_2(x, n);
    expected[2] = z_2(x, n);
    double f0 = xyz_square(x, n);

    gradientB(n, x, f0, g, xyz_square, space, xmark);

    //printf("x=%lf, y=%lf, z=%lf\nexpected_dx=%lf, expected_dy=%lf, "
    //                "expected_dz=%lf\nactual_dx=%lf, actual_dy=%lf, actual_dz=%lf\nepsilon=%lf\n", x[0],
    //                x[1], x[2], expected[0], expected[1], expected[2], g[0], g[1], g[2], 2 * eh);

    assert(double_equal(expected[0], g[0], 2 * eh));
    assert(double_equal(expected[1], g[1], 2 * eh));
    assert(double_equal(expected[2], g[2], 2 * eh));
  }
}

int
main()
{
  test_gradientB();
  return 0;
}

