#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * for a degree 0, this poly perform 0 addition/multiplication
 * for a degree 1, this poly perform 1 addition + 2 multiplication
 * for a degree 2, this poly perform 2 addition + 4 multiplication
 * for a degree n, this poly perform n addition + 2n multiplication
*/

/* n add, 2n mul  */
double poly(const double *coeffs, double x, int degree) {
    double ret = coeffs[0];
    double xpwr = x;
    for (int i = 1; i <= degree; i++) {
        ret += coeffs[i] * xpwr;
        xpwr *= x;
    }
    return ret;
}

/* n add, n mul */
double horner(const double *coeffs, double x, int degree) {
    double acc1 = 0, acc2 = 0, acc3 = 0, acc4 =0;
    double xp4 = x * x * x * x;
    for (int i = degree; i >= 3; i -= 4) {
        acc4 = acc4*xp4 + coeffs[i];
        acc3 = acc3*xp4 + coeffs[i - 1];
        acc2 = acc2*xp4 + coeffs[i - 2];
        acc1 = acc1*xp4 + coeffs[i - 3];
    }
    double combined = acc1 + acc2*x + acc3*x*x + acc4*x*x*x;
    for (int i = (degree + 1) % 4 - 1; i >= 0; --i) {
        combined = combined*x + coeffs[i];
    }
    return combined;
}



int main() {
    srandom(1337);
    int n = 100000000;
    double *coeffs = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++) {
        coeffs[i] = (double) random() / (double) RAND_MAX;
    }
    volatile double tmp = poly(coeffs, 0.45, n);
    clock_t start, end;
    start = clock();
    volatile double result1 = poly(coeffs, 0.45, n);
    end = clock();
    long elapsed1 = end - start;
    printf("poly: %lf\n", result1); 

    tmp = horner(coeffs, 0.45, n);
    start = clock();
    volatile double result2 = horner(coeffs, 0.45, n);
    end = clock();
    long elapsed2 = end - start;
    printf("horner: %lf\n", result2); 

    printf(" -- ratio: %.2lf -- \n", (double)elapsed1/(double)elapsed2);
    return 0;
}
