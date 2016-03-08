#include <iostream>

int main() {
	const int N = 10;
	int* a[N];
	for (int i = 0; i < N; ++i) {
		a[i] = new int [i+1] {};
		a[i][i] = 1;
	}

	for (int i = 0; i < N; ++i) {
		int j = 0;
		while (true) {
			std::cout << a[i][j] << " ";
			if (a[i][j] == 1) break;
			j++;
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < N; ++i) {
		delete[] a[i];
	}

	return 0;
}