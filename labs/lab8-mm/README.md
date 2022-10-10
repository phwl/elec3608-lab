# Lab 8 - Matrix Multiplication


Marks can be awarded for any parts of the 2 questions below. While it is intended that one question be answered each week, marks can be awarded over the 2 week period. Marking will be based on the report (you do not need to do a demo for this lab).

The goals of this lab are:

 *  Gain deeper understanding of how caches affect program performance.
 *  Try your hand at software performance optimisation.
 *  Gain experience in reading research papers on computer architecture.

If you have previously downloaded all the labs using git clone https://github.com/phwl/elec3608-lab.git, you should first type ```git pull``` to download any recent changes. Please note that we are using a different docker image (elec3608-riscv:latest) for this lab, executed as:

```
docker run --platform linux/amd64 -it -e DISPLAY=host.docker.internal:0 -v `pwd`:/config phwl/elec3608-riscv:latest
```

Type:
```bash
$ cd mm
$ make
cc    -c -o mm-1.o mm-1.c
gcc -O3 -o mm-1 mm-1.c
```

to compile the program mm-1. This program is an unoptimised implementation of matrix multiplication. It generates two random 1000x1000 matrices, multiples them and sums all of the elements of the result. Execute (on the local x86 machine under Linux and not on RISC-V) using

The output should be similar to:
```bash
$ ./mm-1
Block size = 50, N = 1000
--- fn = mmul0, MFLOPS = 2710.56, elapsed time = 0.737856s, sum = 2555.77
```
This means that using the function in index 0 of the mtab array (mmult0), the program used took 6.40s to execute, the sum of the result was 2555.77 and 313 million floating point instructions per second was achieved.

## Week 1

* (30%) Looking at the mmul0() function, it should be apparent that the three nested loops are not organized to best utilize the cache. You can add a new mmul1() function to the program by writing the function and changing the declaration of mtab to be

     ```c
     void (*mtab[])(int b, double C[N][N], double A[N][N], double B[N][N]) =
        { mmul0, mmul1 };
     ```

    This should be all you have to do so that the program will run mmul0() and then mmul1() since there is a loop in mmul() which calls each of the entries in mtab. Making sure that your modifications still give the correct answer, change the i, j and k loops and record the execution time for all possible orderings (there are 6: ijk, ikj, jik, jki, kij, kji). Which ordering gives the highest performance? Why?

* (50%) A key optimisation for matrix multiplication is blocking. Read Section 1 of lam91.pdf (included in the mm directory for this lab) and implement a blocked matrix multiplication, calling it mmulb(). The program is written so that ```./mm-1 –b 66``` will set the b argument of the call to the mmulb() routine to be 66. Determine a good choice for the parameter b.

* (20%) What should happen to the speedup of the blocked version over the unblocked on as you increase the size of the matrices (N)? Show this experimentally and plot a graph of the speedup for different b.

## Week 2

* (30%) Install openblas using

    ```bash
    $ sudo apt-get install libopenblas-base libopenblas-dev # use "elec3608" as the password
    ```

    Compare the performance of your blocked version with that linked to the OpenBLAS library by typing

    ```bash
    $ make mm-blas
    $ ./mm-blas
    Block size = 50, N = 1000
    --- fn = mmul0, MFLOPS = 1623.47, elapsed time = 1.23193s, sum = 2555.77
    --- fn = mmul1, MFLOPS = 12492.7, elapsed time = 0.160093s, sum = 2555.77
    ```

    Depending on your machine, it might have a large improvement or none at all. The output above was from an x86 machine whereas my M1 Macbook was about the same speed as ```mm-1```. This is because the M1 Macbook is emulating an x86 machine. If you have the choice between x86 and M1, x86 will have much higher performance on this experiment. Note the speedup in your lab book.

* (10%) Complete the course evaluation survey for ELEC3608 (yes we will give you a mark for this).


