#include <iostream>
#include <string>

int gcd(int a, int b) {
	return (b == 0) ? a : gcd(b, a % b);
}

int lcd(int a, int b) {
	return a*b / gcd(a, b);
}

int main() {
	int a, b;
	std::cin >> a >> b;
	std::cout << lcd(a, b) << std::endl;
	return 0;
}