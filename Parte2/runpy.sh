#!/bin/zsh

for run in {1..10}; do
  time python3.9 mandelbrot.py 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
done

for run in {1..10}; do
  time pypy3 mandelbrot.py 1600 1600 -1.5 -1.5 1.5 1.5 50 4 > img.pbm
done