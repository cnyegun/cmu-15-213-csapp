void cond(short a, short *p) {
	if (!a) goto END;
	if (*p <= a) goto END;
	*p = a;
END:
	return;
}

int absdiff_se(int a, int b) {
	int result;
	int t = a > b;
	if (t)
		goto TRUE;
	result = b - a;
	goto DONE;
TRUE:
	result = a - b;
DONE:
	return result;
}

short test(short x, short y, short z) {
	short val = z + y - x;
	if (val > 5) {
		if (y > 2)
			val = x / z;
		else
			val = x / y;
	} else if (y < 3) {
		val = z / y;
	}
	return val;
}
