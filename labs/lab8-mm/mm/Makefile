mm-1:	mm-1.o
	gcc -O3 -o mm-1 mm-1.c

mm-blas:	mm-blas.o
	gcc -O3 -o mm-blas mm-blas.c -lopenblas

clean:
	-rm -f *.o mm-1 mm-blas
