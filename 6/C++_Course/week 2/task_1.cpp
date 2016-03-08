#include <iostream>

void rev(int* a, int length) {

	//for (int i = 0; i < length / 2; ++i) {
	//	std::swap(a[i], a[length - i -1]);
	//}

	int* l = a;
	int* r = a + length - 1;

	while (l < r) {
		std::swap(*l, *r);
		l++;
		r--;
	}
}

int main() {

	const int N = 8;
	int a[N] = { 9,8,7,6,5,4,3,2 };
	rev(a, N);

	for (int i = 0; i < N; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}