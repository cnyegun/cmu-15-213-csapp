int incr(long *p, long val) {
	long x = *p;
	long y = x + val;
	*p = y;
	return x;
}

int main() {
	long x = 5;
	long y = incr(&x, 3);
	y = incr(&x, 3);
	y = incr(&x, 3);
	y = incr(&x, 3);
	y = incr(&x, 3);
	y = incr(&x, 3);
	return y;
}
