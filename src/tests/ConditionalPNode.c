#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define main test_main
#include "../codeml.c"
#undef main
#include "shared.c"

#define N 61
#define POS0 0
#define POS1 190
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#define NMAX MAX(N, POS1)

// Reference implementation
static double
ref_ConditionalPNode_InternalNode(int n, int pos0, int pos1, double t, double *PMat,
  struct TREEN *nodes, int inode, int ison)
{
  int h, j, k;
  for (h = pos0; h < pos1; h++)
     for (j = 0; j < n; j++) {
        for (k = 0, t = 0; k < n; k++)
           t += PMat[j*n + k] * nodes[ison].conP[h*n + k];
        nodes[inode].conP[h*n + j] *= t;
     }
  return t;
}

// Initialize with pre-defined values
static void
init_ConditionalPNode_InternalNode(double *PMat, struct TREEN *node_actual)
{
  for (size_t h = POS0; h < POS1; h++)
    for (size_t j = 0; j < N; j++)
      for (size_t k = 0; k < N; k++) {
        PMat[j*N + k] = 0.5;
        node_actual->conP[h*N + k] = 1.1;
      }
}

static void
test_ConditionalPNode_InternalNode(void)
{
  double PMat[N * NMAX];
  struct TREEN node_actual, node_expected;
  size_t size = N * NMAX * sizeof(*(node_actual.conP));
  
  node_actual.conP = malloc(size);
  init_ConditionalPNode_InternalNode(PMat, &node_actual);
  
  node_expected.conP = malloc(size);
  memcpy(node_expected.conP, node_actual.conP, size);

  ref_ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, &node_expected, 0, 0);

  ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, &node_actual, 0, 0);

  for (size_t h = POS0; h < POS1; h++)
    for (size_t j = 0; j < N; j++)
      assert(double_equal(node_actual.conP[h*N + j], node_expected.conP[h*N + j], Small_Diff));

  free(node_actual.conP);
  free(node_expected.conP);
}

int
main()
{
  test_ConditionalPNode_InternalNode();
  return 0;
}
