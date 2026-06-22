#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>

void copy_array(int *src, int *dst, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
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
    for (; i < n; i++)
        dst[i] = src[i];
}

static inline uint64_t rd(void) {
    _mm_lfence();
    uint64_t t = __rdtsc();
    _mm_lfence();
    return t;
}

// take the MINIMUM over many reps -> filters interrupts/noise
static uint64_t best(void (*f)(int*,int*,int), int *xs, int *ys, int n, int reps) {
    uint64_t b = ~0ull;
    for (int r = 0; r < reps; r++) {
        uint64_t s = rd();
        f(xs, ys, n);
        uint64_t e = rd();
        if (e - s < b) b = e - s;
    }
    return b;
}

int main(int argc, char **argv) {
    int which = (argc > 1) ? atoi(argv[1]) : -1;  // for perf: 0=naive 1=unrolled
    int n = 4000;
    int *xs = malloc(sizeof(int) * n);
    int *ys = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) xs[i] = (int)random();

    // --- frequency warm-up: spin ~0.3s so the core boosts to full clock ---
    volatile uint64_t spin = 0;
    uint64_t t0 = rd();
    while (rd() - t0 < 800000000ull) spin++;

    if (which == 0) { for (int r = 0; r < 200000; r++) copy_array(xs, ys, n); return 0; }
    if (which == 1) { for (int r = 0; r < 200000; r++) copy_array_optimized(xs, ys, n); return 0; }

    uint64_t a = best(copy_array,           xs, ys, n, 5000);
    uint64_t b = best(copy_array_optimized, xs, ys, n, 5000);
    // order doesn't matter now, but prove it by also doing reverse:
    uint64_t b2 = best(copy_array_optimized, xs, ys, n, 5000);
    uint64_t a2 = best(copy_array,           xs, ys, n, 5000);

    printf("naive    : %5lu cyc  (%.2f cyc/elem)\n", a,  (double)a  / n);
    printf("unrolled : %5lu cyc  (%.2f cyc/elem)\n", b,  (double)b  / n);
    printf("ratio (naive/unrolled) = %.2fx\n", (double)a / b);
    printf("[reverse order] naive %lu  unrolled %lu  ratio %.2fx\n", a2, b2, (double)a2 / b2);
    return 0;
}
