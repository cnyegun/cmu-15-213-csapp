int fn(int x, int y) {
	int arr[6] = {1,2,3,4,5,6};
	return arr[x] + arr[y];
}

int main() {
	int a = 5;
	int b = 3;
	int r = fn(a, b);
	return r;
}
