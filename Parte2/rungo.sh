#!/bin/zsh

go build mandelbrot.c

for run in {1..10}; do
    time ./mandelbrot 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
done