#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void psum1(float dst[], float src[], size_t n) {
    dst[0] = src[0];
    for (size_t i = 1; i < n; i++) {
        dst[i] = dst[i - 1] + src[i];
    }
}

void psum2(float dst[], float src[], size_t n) {
    dst[0] = src[0];
    for (size_t i = 1; i < n; i += 2) {
        float base = dst[i - 1] + src[i];
        dst[i] = base;
        dst[i + 1] = base + src[i + 1];
    }
}

int main() {
    // Init a float array
    float *dst = malloc(sizeof(float) * 10000000);
    float *src = malloc(sizeof(float) * 10000000);
    int n = 10000000;
    srandom(1337);

    for (int i = 0; i < 10000000; ++i) {
        src[i] = (float) random() / (float) RAND_MAX;
    }

    printf("psum2: ");
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 100; i++)
        psum2(dst, src, (size_t)n);
    end = clock();
    printf(" %lf\n", (double) (end - start) / CLOCKS_PER_SEC);

    printf("psum1: ");
    start = clock();
    for (int i = 0; i < 100; i++)
        psum1(dst, src, (size_t)n);
    end = clock();
    printf(" %lf\n", (double) (end - start) / CLOCKS_PER_SEC);
}
