#include <stdio.h>

int incr(long *p, long val) {
	long x = *p;
	long y = x + val;
	*p = y;
	return x;
}

int main() {
	long x = 5;
	long y = 3;
	long z = incr(&x, 3);
	printf("%d\n", x + y + z);
	return 0;
}
