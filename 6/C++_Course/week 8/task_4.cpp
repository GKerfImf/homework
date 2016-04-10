#include <iostream>
#include <vector>
#include <iterator>

template<typename T>
void swap(T &a, T &b)
{
	T c = a;
	a = b;
	b = c;
}

int main() {
	int a = 0;
	int b = 1;

	std::cout << a << " " << b << std::endl;
	swap(a, b);
	std::cout << a << " " << b << std::endl;
	return 0;
}