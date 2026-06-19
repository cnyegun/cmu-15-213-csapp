#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void accmul_float_naive(const double *ds, size_t n, volatile double *dest) {
    double total;
    for (size_t i = 0; i < n; i++) {
        total *= ds[i];
    }
    *dest = total;
}

void accmul_float(const double *ds, size_t n, volatile double *dest) {
    double sum1, sum2, sum3, sum4;
    for (size_t i = 0; i < n; i += 4) {
        sum1 *= ds[i];
        sum2 *= ds[i + 1];
        sum3 *= ds[i + 2];
        sum4 *= ds[i + 3];
    }
    *dest = sum1 * sum2 * sum3 * sum4;
}

void accmul_long_naive(const long *ds, size_t n, volatile long *dest) {
    long total;
    for (size_t i = 0; i < n; i++) {
        total *= ds[i];
    }
    *dest = total;
}

void accmul_long(const long *ds, size_t n, volatile long *dest) {
    long sum1, sum2, sum3, sum4;
    for (size_t i = 0; i < n; i += 4) {
        sum1 *= ds[i];
        sum2 *= ds[i + 1];
        sum3 *= ds[i + 2];
        sum4 *= ds[i + 3];
    }
    *dest = sum1 * sum2 * sum3 * sum4;
}

int main() {
    srandom(1337);
    size_t n = 10000000;

    double *ds = (double *)malloc(sizeof(double) * n);
    for (size_t i = 0; i < n; i++) {
        ds[i] = (double) random() / (double) RAND_MAX;
    }
    
    long *ls = (long *)malloc(sizeof(long) * n);
    for (size_t i = 0; i < n; i++) {
        ls[i] = (long) random();
    }

    printf("Measuring float64 perf:\n");
    clock_t start, end;
    start = clock();
    volatile double r1;
    accmul_float_naive(ds, n, &r1);
    end = clock();
    long t1 = end - start;
    printf("    accmul_float_naive: %lds\n", t1);

    start = clock();
    volatile double r2;
    accmul_float(ds, n, &r2);
    end = clock();
    long t2 = end - start;
    printf("    accmul_float:       %lds\n", t2);

    printf("    -- ratio: %.2lfx --\n\n", (double)t1/t2);

    printf("Measuring int64 perf:\n");
    start = clock();
    volatile long r3;
    accmul_long_naive(ls, n, &r3);
    end = clock();
    long t3 = end - start;
    printf("    accmul_long_naive: %lds\n", t3);

    start = clock();
    volatile long r4;
    accmul_long(ls, n, &r4);
    end = clock();
    long t4 = end - start;
    printf("    accmul_long:       %lds\n", t4);

    printf("    -- ratio: %.2lfx --\n\n", (double)t3/t4);
}
