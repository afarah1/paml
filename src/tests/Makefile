PRGS = gradientB
CC = cc 
override CFLAGS += -O3 -Wall -Wno-unused-result
LIBS = -lm 

all : $(PRGS)

gradientB : 
	$(CC) $(CFLAGS) -o $@ gradientB.c $(LIBS)

clean :
	-rm -f *.o $(PRGS) 
