# mandelbrot.py
# written by Elisa Uhura.

import sys

def main():
    if len(sys.argv) < 9:
        exit(1)
    w = int(sys.argv[1])
    h = int(sys.argv[2])
    xr = float(sys.argv[3])
    xi = float(sys.argv[4])
    yr = float(sys.argv[5])
    yi = float(sys.argv[6])
    max_iters = int(sys.argv[7])

    bitmap = []
    
    for i in range(h):
        for j in range(w):
            a = j/w*(yr-xr) + xr
            b = i/h*(xi-yi) + yi
            za = 0
            zb = 0
            ta = 0
            tb = 0
            div = False

            for k in range(max_iters):
                ta = za*za - zb*zb + a
                tb = 2*za*zb + b
                za = ta
                zb = tb
                if (za*za+zb*zb) > 4.0:
                    div = True
                    break
            bitmap.append("1" if div else "0")

    print("P1")
    print(w, h)
    print("".join(bitmap))

main()
