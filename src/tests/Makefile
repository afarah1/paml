PRGS = gradientB ConditionalPNode PMatUVRoot
CC = cc 
DBG = -O0 -ggdb
OPT = -O3
# Parallel implementation flags
#
# USE_OMP - Use OpenMP (at all)
# USE_OMP_CPNODE - Use OpenMP on ConditionalPNode
# USE_OMP_PMATUV - Use OpenMP on PMatUVRoot
#
override CFLAGS += $(DBG) -Wall -Wno-unused-result 
override CFLAGS += -DUSE_OMP -fopenmp
#override CFLAGS += -DUSE_OMP_CPNODE
#override CFLAGS += -DUSE_OMP_PMATUV
LIBS = -lm -lgomp

all : $(PRGS)

gradientB : 
	$(CC) $(CFLAGS) -o $@ gradientB.c $(LIBS)
ConditionalPNode : 
	$(CC) $(CFLAGS) -o $@ ../tools.c ConditionalPNode.c $(LIBS) 
PMatUVRoot :
	$(CC) $(CFLAGS) -o $@ PMatUVRoot.c $(LIBS)

clean :
	-rm -f *.o $(PRGS) 
