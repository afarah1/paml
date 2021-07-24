#include <stdio.h>
#include <assert.h>
#include "../tools.c"
#include "shared.c"

#define N 61

// Reference implementation
static int
ref_PMatUVRoot(double P[], double t, int n, double U[], double V[], double Root[])
{
   int i, j, k;
   double exptm1, uexpt, *pP;

   NPMatUVRoot++;
   memset(P, 0, n*n * sizeof(double));
   for (k = 0; k < n; k++) {
      for (i = 0, pP = P, exptm1 = expm1(t*Root[k]); i < n; i++)
         for (j = 0, uexpt = U[i*n + k] * exptm1; j < n; j++)
            *pP++ += uexpt*V[k*n + j];
   }
   for (i = 0; i < n; i++)  P[i*n+i] ++;

   return (0);
}

// Initialize with pre-defined values
static void
init_UVRoot(int n, double *U, double *V, double *Root)
{
  for (size_t i = 0; i < n; i++) {
    U[i] = 1.1;
    V[i] = 0.5;
    Root[i] = 0.99;
  }
}

static void
test_PMatUVRoot(void)
{
  double actual[N * N], expected[N * N], U[N * N], V[N * N], Root[N * N];
  double t = 0.75;
  init_UVRoot(N * N, U, V, Root);

  ref_PMatUVRoot(expected, t, N, U, V, Root);
  PMatUVRoot(actual, t, N, U, V, Root);

  for (size_t i = 0; i < N * N; i++)
    assert(double_equal(
      expected[i],
      actual[i],
      1e-9
    ));
}

int
main()
{
  test_PMatUVRoot();
  return 0;
}
