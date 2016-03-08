//2. ѕусть у нас есть массив из 10 целых чисел, и точно известно, 
//что в нем максимальный элемент единственный.Ќайдите этот максимальный 
//элемент и замените его на 0.

#include <iostream>

void delmax(int* a, int length) {

	int* max = a;

	for (int* p = a; p - a < length; p++) {
		if (*max < *p) {
			max = p;
		}
	}
	*max = 0;
}

void printf(int* a, int length) {
	for (int i = 0; i < length; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main() {

	const int N = 10;
	int a[N] = { 9,8,7,6,5,100,3,2,1,0 };


	printf(a, N);
	delmax(a, N);
	printf(a, N);

	return 0;
}