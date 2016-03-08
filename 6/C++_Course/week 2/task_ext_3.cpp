//3. Для данного массива из 10 чисел проверить, есть ли 
//в нем два числа, отличающихся ровно на 1, и напечатать "да" или "нет".

#include <iostream>

bool foo(int* a, int length) {
	for (int* p = a; p - a < length; p++) {
		for (int* q = p + 1; q - a < length; q++) {
			if (abs(*p - *q) == 1) {
				return true;
			}
		}
	}
	return false;
}

void printf(int* a, int length) {
	for (int i = 0; i < length; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main() {

	const int N = 10;
	int a[N] = { 0,10,20,30,40,81,50,60,70,80 };

	printf(a, N);

	if (foo(a, N)) std::cout << "yes" << std::endl;
	else std::cout << "no" << std::endl;

	return 0;
}