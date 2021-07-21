#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../tools.c"
#include "shared.c"

#define NVARS 8
#define TEST_SIZE 100

// \sum{x_i^2}_{i=0..n-1}
static double
x_sqrsum(double x[], int n)
{
  double ans = 0;
  for (int i = 0; i < n; i++)
    ans = ans + x[i] * x[i];
  return ans;
}

// 2 * x[i] (partial derivative of x_sqrsum in respect to x_i)
static double
x_2(double x[], int n, int i)
{
  return 2 * x[i];
}

/*
 * Test gradientB using a simple N-variable function and a mixture of
 * forward, backward, and central derivatives.
 */
static int 
test_gradientB(void)
{
  double eh, f0;
  int i, j;
  int n = NVARS;
  double x[NVARS];
  double g[NVARS];
  double expected[NVARS];
  double space[NVARS * 2];
  int xmark[NVARS] = { -1, 0, 1, 0, -1, 1, 0, 1 };

  for (i = 0; i < TEST_SIZE; i++) {
    eh = Small_Diff * (i + 1);
    for (j = 0; j < n; j++) {
      x[j] = i;
      expected[j] = x_2(x, n, j);
    }
    f0 = x_sqrsum(x, n);

    gradientB(n, x, f0, g, x_sqrsum, space, xmark);

    for (j = 0; j < n; j++) {
      assert(double_equal(expected[j], g[j], 2 * eh));
    }
  }

  return(0);
}

int
main()
{
  noisy = 9;
  test_gradientB();
  return 0;
}

