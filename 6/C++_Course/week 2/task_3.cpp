#include <iostream>

void order(int& x, int& y, int& z) {
	if (x > y) std::swap(x, y);
	if (x > z) std::swap(x, z);
	if (y > z) std::swap(y, z);
}

int main() {
	int a = 5, b = 1, c = 3;

	std::cout << a << " " << b << " " << c << std::endl;
	order(a, b, c);
	std::cout << a << " " << b << " " << c << std::endl;

	return 0;
}