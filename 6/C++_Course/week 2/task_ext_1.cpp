//1. Напишите две очень простые функции.Одна заполняет данный массив длины n нулями.
//Вторая копирует одни массив длины n в другой.Все нассивы передаются в параметрах, 
//результат у обеих функций должен быть void.Пример вызова м.б.таким:
//
//	int a[10];
//	clear(a, 10); // заполнить массив a длины 10 нулями
//	int b[10];
//	copy(b, a, 10); // Скопировать 10 чисел из массива a в массив b
//

#include <iostream>

void clear(int* a, int length) {
	for (int* p = a; p - a < length; p++) {
		*p = 0;
	}
}
void copy(int* b, int* a, int length) {
	int* a1 = a;
	int* b1 = b;

	for (int i = 0; i < length; ++i) {
		*a1 = *b1;
		a1++;
		b1++;
	}
}

void printf(int* a, int length) {
	for (int i = 0; i < length; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int main() {

	const int N = 10;
	int a[N] = { 9,8,7,6,5,4,3,2,1,0 };
	int b[N] = { 0,1,2,3,4,5,6,7,8,9 };

	printf(a,N);
	clear(a, 10);
	printf(a, N);
	copy(b, a, 10);
	printf(a, N);

	return 0;
}