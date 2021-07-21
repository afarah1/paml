PRGS = gradientB ConditionalPNode
CC = cc 
# Uncomment -DUSE_OMP -fopenmp and -lgomp for parallel execution using OpenMP
DBG = -O0 -ggdb
OPT = -O3
override CFLAGS += $(DBG) -Wall -Wno-unused-result #-DUSE_OMP -fopenmp 
LIBS = -lm #-lgomp

all : $(PRGS)

gradientB : 
	$(CC) $(CFLAGS) -o $@ gradientB.c $(LIBS)
ConditionalPNode : 
	$(CC) $(CFLAGS) -o $@ ../tools.c ConditionalPNode.c $(LIBS) 

clean :
	-rm -f *.o $(PRGS) 
