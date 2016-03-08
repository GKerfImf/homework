#include<iostream>

int main() {
	int i = 0;
	int a[10]{0,0,7,9,2,2,2,2,2,0};

	while (i < 10 && *(a + i) != 0) {
		++i;
	}

	std::cout << i << std::endl;

	return 0;
}