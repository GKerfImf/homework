#include <iostream>

void twice(int* n) {
	*n *= 2;
}

int main() {
	int i = 5;

	std::cout << i << std::endl;
	twice(&i);
	std::cout << i << std::endl;

	return 0;
}