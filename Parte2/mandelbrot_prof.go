// mandelbrot.go
// written by Elisa Uhura.
package main

import (
	"fmt"
	"os"
	"strings"
	"sync"
)

var w, h, max_iters, workers int
var bitmap []byte
var xr, xi, yr, yi float64
var wg sync.WaitGroup

var one byte = []byte("1")[0]
var zero byte = []byte("0")[0]

func main() {
	if len(os.Args) < 9 {
		fmt.Println("./program w h xr xi yr yi max_iters workers")
		os.Exit(1)
	}
	parseArgs()

	bitmap = make([]byte, w*h)

	wg.Add(workers)
	for i := 1; i < workers; i++ {
		go work((i-1)*h/workers, i*h/workers)
	}
	go work((workers-1)*h/workers, h)

	wg.Wait()

	writeImage()
}

func parseArgs() {
	str := strings.Join(os.Args[1:], " ")
	fmt.Sscan(str, &w, &h, &xr, &xi, &yr, &yi, &max_iters, &workers)
}

func writeImage() {
	fmt.Printf("P1\n%d %d\n", w, h)
	fmt.Println(string(bitmap))
}

func work(line0, lineF int) {
	dw := float64(w)
	dh := float64(h)

	for i := line0; i < lineF; i++ {
		for j := 0; j < w; j++ {
			a := float64(j)/dw*(yr-xr) + xr
			b := float64(i)/dh*(xi-yi) + yi
			var za, zb, ta, tb float64
			div := false

			for k := 0; k < max_iters && !div; k++ {
				ta = za*za - zb*zb + a
				tb = 2*za*zb + b
				za = ta
				zb = tb
				div = za*za+zb*zb > 4.0
			}

			if div {
				bitmap[i*w+j] = one
			} else {
				bitmap[i*w+j] = zero
			}

		}
	}

	wg.Done()
}
