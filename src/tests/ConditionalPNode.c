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
#define NODELEN (N * POS1 + N)

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
init_ConditionalPNode_InternalNode(double *PMat, struct TREEN *ison, struct TREEN *inode_expected, struct TREEN *inode_actual)
{
  for (size_t h = POS0; h < POS1; h++) {
    for (size_t j = 0; j < N; j++) {
      for (size_t k = 0; k < N; k++) {
        PMat[j*N + k] = 0.5;
        ison->conP[h*N + k] = 1.1;
      }
      inode_actual->conP[h*N + j] = 1.1;
      inode_expected->conP[h*N + j] = 1.1;
    }
  }
}

static void
test_ConditionalPNode_InternalNode(void)
{
  double PMat[N * N];
  struct TREEN ison, inode_actual, inode_expected;
  ison.conP = malloc(NODELEN * sizeof(*(ison.conP)));
  inode_actual.conP = malloc(NODELEN * sizeof(*(inode_actual.conP)));
  inode_expected.conP = malloc(NODELEN * sizeof(*(inode_expected.conP)));
  struct TREEN nodes[3] = { ison, inode_actual, inode_expected };
  
  init_ConditionalPNode_InternalNode(PMat, &ison, &inode_expected, &inode_actual);

  ref_ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, nodes, 0, 1);
  //ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, nodes, 1, 1);

  ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, nodes, 0, 2);
  //ref_ConditionalPNode_InternalNode(N, POS0, POS1, 0, PMat, nodes, 2, 2);

  for (size_t h = POS0; h < POS1; h++)
    for (size_t j = 0; j < N; j++)
      //fprintf(stderr, "%f, %f\n", inode_actual.conP[h*N + j], inode_expected.conP[h*N + j]);
      assert(double_equal(inode_actual.conP[h*N + j], inode_expected.conP[h*N + j], Small_Diff));

  free(ison.conP);
  free(inode_actual.conP);
  free(inode_expected.conP);
}

int
main()
{
  test_ConditionalPNode_InternalNode();
  return 0;
}
