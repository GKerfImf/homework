#include<cmath>
#include<iostream>

long double sum(int n) {
	long double result = 0;
	for (int i = 0; i <= n; ++i) {
		result += 1.0 / pow(2 * i + 1, 3);
	}
	return result;
}

int main() {
	int n;
	std::cin >> n;
	std::cout << sum(n) << std::endl;
	return 0;
}