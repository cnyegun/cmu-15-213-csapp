#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>


typedef int data_t;

typedef struct {
    int size;
    data_t *data;
} vec_ptr;

void vec_random_fill(vec_ptr v) {
    int length = v.size;
    for (int i = 0; i < length; i++) {
        v.data[i] = (data_t)random();
    }
}

void inner4(vec_ptr u, vec_ptr v, volatile data_t *dest) {
    long int i;
    int n = v.size;
    data_t *udata = u.data;
    data_t *vdata = v.data;
    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    for (i = 0; i < n; i += 4) {
        sum1 = sum1 + udata[i] * vdata[i];
        sum2 = sum2 + udata[i + 1] * vdata[i + 1];
        sum3 = sum3 + udata[i + 2] * vdata[i + 2];
        sum4 = sum4 + udata[i + 3] * vdata[i + 3];
    }
    int total = (sum1 + sum2) + (sum3 + sum4);

    for (; i < n; i++) {
        total += udata[i] * vdata[i];
    }
    *dest = total;
}

int main() {
    int n = 2000;
    vec_ptr u = {.size = n, .data = malloc(sizeof(data_t) * n)};

    vec_ptr v = {.size = n, .data = malloc(sizeof(data_t) * n)};

    vec_random_fill(u);
    vec_random_fill(v);

    volatile data_t tmp;
    double best = 1e18;
    for (int trial = 0; trial < 100000; trial++) {
        unsigned long long s = __rdtsc();
        inner4(u, v, &tmp);
        unsigned long long e = __rdtsc();
        double cpe = (double)(e - s) / n;
        if (cpe < best)
            best = cpe;
    }

    printf("CPE: %.2f\n", best);
}
