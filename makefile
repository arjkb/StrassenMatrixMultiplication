all: strassens_mm

strassens_mm: strassens_mm.o
	gcc -o strassens_mm strassens_mm.o

strassens_mm.o: strassens_mm.c
	gcc -c strassens_mm.c

clean:
	rm *.o strassens_mm
