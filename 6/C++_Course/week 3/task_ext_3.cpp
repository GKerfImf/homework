#include <iostream>
#include <string>

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, a % b);
}

bool isSplit(int* a, const int n) {
	int* b = new int[n] {0};
	int t = 0;

	for (int i = 0; i < n; ++i) {
		if (a[i] == a[i + 1] && i < n - 1) {
			b[t]++;
		}
		else {
			b[t]++;
			t++;
		}
	}

	int result = b[0];
	for (int i = 0; i < t; ++i) {
		result = gcd(result, b[i]);
	}

	return result > 1;
}

int main() {
	int n;
	std::cin >> n;
	int* a = new int[n] {0};

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::cout << (isSplit(a, n) ? "Yes" : "No") << std::endl;

	return 0;
}