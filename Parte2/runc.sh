#!/bin/zsh
time gcc -O0 mandelbrot.c
time ./a.out 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
time gcc -O1 mandelbrot.c
time ./a.out 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
time gcc -O2 mandelbrot.c
time ./a.out 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
time gcc -O3 mandelbrot.c
time ./a.out 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
