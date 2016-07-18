CC=gcc

all: strassens_mm

strassens_mm: strassens_mm.o
	$(CC) -o strassens_mm strassens_mm.o -lm

strassens_mm.o: strassens_mm.c
	$(CC) -c strassens_mm.c

clean:
	rm *.o strassens_mm
