PRGS = gradientB
CC = cc 
# Uncomment -DUSE_OMP -fopenmp and -lgomp for parallel execution using OpenMP
override CFLAGS += -O3 -Wall -Wno-unused-result -DUSE_OMP -fopenmp 
LIBS = -lm -lgomp

all : $(PRGS)

gradientB : 
	$(CC) $(CFLAGS) -o $@ gradientB.c $(LIBS)

clean :
	-rm -f *.o $(PRGS) 
