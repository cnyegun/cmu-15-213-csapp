#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>   // __rdtsc, _mm_lfence
#include <stdint.h>


void copy_array(int *src, int *dst, int n) {
    int i;
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

void copy_array_optimized(int *src, int *dst, int n) {
    int i;
    for (i = 0; i < n - 8; i += 8) {
        dst[i]     = src[i]; 
        dst[i + 1] = src[i + 1]; 
        dst[i + 2] = src[i + 2]; 
        dst[i + 3] = src[i + 3]; 
        dst[i + 4] = src[i + 4]; 
        dst[i + 5] = src[i + 5]; 
        dst[i + 6] = src[i + 6]; 
        dst[i + 7] = src[i + 7]; 
    }
    for (; i < n; i++) {
        dst[i]     = src[i]; 
    }
}

static inline uint64_t cycles_now(void) {
    _mm_lfence();
    uint64_t t = __rdtsc();
    _mm_lfence();
    return t;
}

int main() {
    clock_t start, end;
    long c1, c2;
    srandom(07122007);
    int n = 4000;
    int *xs = (int *)malloc(sizeof(int) * n); 

    for (int i = 0; i < n; i++) {
        xs[i] = (int)random();
    }
    
    int *ys = (int *)malloc(sizeof(int) * n); 

    copy_array(xs, ys, n);
    start = cycles_now();
    copy_array(xs, ys, n);
    end = cycles_now();
    c1 = end - start;

    volatile int xxx = ys[123];

    copy_array_optimized(xs, ys, n);
    start = cycles_now();
    copy_array_optimized(xs, ys, n);
    end = cycles_now();
    c2 = end - start;

    xxx = ys[321];

    printf("naive: %ld cycles\n", c1);
    printf("unrolled: %ld cycles\n", c2);
    printf(" -- ratio %.2lfx --\n", (double) c1/c2);

    return 0;
}
