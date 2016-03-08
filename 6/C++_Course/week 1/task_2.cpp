#include<iostream>

int main() {
	double a, i = 0, result = 0;
	while (true) {
		std::cin >> a;
		if (a == 0) break;

		++i;
		result = ((i - 1) * result / i) + a / i;
	}
	std::cout << result << std::endl;
	
	return 0;
}