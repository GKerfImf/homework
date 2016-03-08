#include<iostream>
#include <tuple>
#include <list>  
#include <vector>  


bool isPrime(int n) {
	if (n < 2) return false;

	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}
bool isSemiprime(int n) {
	if (n < 2) return false;

	for (int i = 2; i <= n; ++i) {
		if (n % i == 0 && isPrime(i) && isPrime(n/i)) {
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	bool flag = false;
	std::cin >> n;

	for (int i = 2; 2*i < n; ++i) {
		if (isSemiprime(n - i) && isSemiprime(i)) {
			std::cout << n << " = " << i << " + " << n - i << std::endl;
			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "nope\n";

	return 0;
}