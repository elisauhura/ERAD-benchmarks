// mandelbrot.c
// written by Elisa Uhura.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define set(x, y) x.y = y

int w, h, max_iters, workers;
char *bitmap;
double xr, xi, yr, yi;
struct timespec mono0, monoF, proc0, procF;

struct thread {
    struct timespec clock0, clockF;
    double line0, lineF, w, h, max_iters, xr, xi, yr, yi;;
    char *bitmap;
    int id;
    pthread_t pdata;
} *threads;

void parse_args(char **);
void init_clock(void);
void close_clock(void);
void write(char *, struct timespec*, struct timespec*, int *);
void *thread(void *);
void write_img(void);

int main(int argc, char **argv) {
    init_clock();

    // read params
    if(argc < 9) {
        puts("./program w h xr xi yr yi max_iters workers");
        return EXIT_FAILURE;
    }

    parse_args(argv+1);

    // alloc data
    threads = malloc(sizeof(struct thread) * workers);
    bitmap = malloc(sizeof(char)*(w*h+1));
    bitmap[w*h] = 0;

    // init threads data
    for(int i = 0; i < workers; i++) {
        threads[i].line0 = (double)(i * h/workers);
        threads[i].lineF = (double)((i + 1) * h/workers);
        threads[i].w = (double)(w);
        threads[i].h = (double)(h);
        threads[i].max_iters = (double)max_iters;

        set(threads[i], xr);
        set(threads[i], xi);
        set(threads[i], yr);
        set(threads[i], yi);
        set(threads[i], bitmap);
    }
    threads[workers - 1].lineF += (double)(h % workers);

    // init threads
    for(int i = 0; i < workers; i++) {
        threads[i].id = pthread_create(&(threads[i].pdata), NULL, thread, threads+i);
    }

    // merge threads
    for(int i = 0; i < workers; i++) {
        pthread_join(threads[i].pdata, NULL);
    }

    // write image
    write_img();

    close_clock();
    return 0;
}

void parse_args(char **argv) {
    w = atoi(argv[0]);
    h = atoi(argv[1]);
    xr = atof(argv[2]);
    xi = atof(argv[3]);
    yr = atof(argv[4]);
    yi = atof(argv[5]);
    max_iters = atoi(argv[6]);
    workers = atoi(argv[7]);
}

void init_clock(void) {
    clock_gettime(CLOCK_MONOTONIC, &mono0);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc0);
}

void close_clock(void) {
    clock_gettime(CLOCK_MONOTONIC, &monoF);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &procF);

    write("mono", &mono0, &monoF, NULL);
    write("proc", &proc0, &procF, NULL);
}

void write(char *name, struct timespec*a, struct timespec*b, int *n) {
    double t0 = (double)a->tv_sec + ((double)a->tv_nsec / 1000000000);
    double tf = (double)b->tv_sec + ((double)b->tv_nsec / 1000000000);
    fprintf(stderr, "%s, %.6lf, %d\n", name, tf-t0, n == NULL ? 0 : *n);
}

void write_img(void) {
    printf("P1\n%d %d\n", w, h);
    int len = w*h;
    puts(bitmap);
}

void *thread(void *_data) {
    struct thread *data = _data;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &data->clock0);
    int width = data->w;
    int divs = 0;

    for(int i = data->line0; i < data->lineF; i++) {
        for(int j = 0; j < data->w; j++) {
            double a = (double)j/data->w * (data->yr - data->xr) + data->xr;
            double b = (double)i/data->h * (data->xi - data->yi) + data->yi;
            double za = 0.0, zb = 0.0, ta, tb;
            int divergent = 0;

            for(int k = 0; k < data->max_iters && !divergent; k++) {
                ta = za*za - zb*zb + a;
                tb = 2*za*zb + b;
                za = ta;
                zb = tb;
                divergent = za*za + zb*zb > 4.0;
            }

            data->bitmap[i*width+j] = divergent ? '1' : '0';
            if(!divergent) divs += 1;
        }
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &data->clockF);
    write("thread", &data->clock0, &data->clockF, &divs);
    return NULL;
}
