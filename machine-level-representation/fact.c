#include <stdio.h>
#include <limits.h>

int main() {
	int i = 1;
	int sum = 1;
BEGIN:
	if (i > 14) goto END;

	if (i != 0 && sum > INT_MAX / i) printf("OVERFLOW!");
	sum *= i;
	i++;

	goto BEGIN;
END:
	printf("%d\n", sum);
	return sum;
}
