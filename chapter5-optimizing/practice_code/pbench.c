// Clean driver for `perf`: NO rdtsc, NO lfence, NO warm-up spin.
// Just loop the function so it dominates; perf measures from outside.
#include <stdlib.h>

void copy_array(int *src, int *dst, int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}
void copy_array_optimized(int *src, int *dst, int n) {
    int i;
    for (i = 0; i < n - 8; i += 8) {
        dst[i]=src[i]; dst[i+1]=src[i+1]; dst[i+2]=src[i+2]; dst[i+3]=src[i+3];
        dst[i+4]=src[i+4]; dst[i+5]=src[i+5]; dst[i+6]=src[i+6]; dst[i+7]=src[i+7];
    }
    for (; i < n; i++) dst[i] = src[i];
}

int main(int argc, char **argv) {
    int which = atoi(argv[1]);     // 0 = naive, 1 = unrolled
    int n = 4000, R = 300000;      // R*n = 1.2e9 elements copied
    int *xs = malloc(sizeof(int)*n), *ys = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) xs[i] = random();

    for (int r = 0; r < R; r++) {
        if (which) copy_array_optimized(xs, ys, n);
        else       copy_array(xs, ys, n);
        asm volatile("" : : "r"(ys) : "memory");  // barrier: "ys was used" -> can't delete
    }
    return 0;
}
