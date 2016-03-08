//4. (����� ������� ������).
//����� � ��� ���� ��������� ������ int a[10][10].��������� ������ 
//���������� int* b[10]; ���, ����� ��������� b[0] �������� �� 
//������� � ������� a, � ������� ����� ����� ������������, b[1] - �� ������.
//� ������� ����� ����� ������ �� ��������, b[2] - �� ������� � ������� �� �������� ������ � �.�.

#include <iostream>

int main() {

	const int N = 10;
	int a[N][N] = { 
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 4,4,4,4,4,4,4,4,4,4 },
		{ 7,7,7,7,7,7,7,7,7,7 },
		{ 9,9,9,9,9,9,9,9,9,9 },
		{ 2,2,2,2,2,2,2,2,2,2 },
		{ 8,8,8,8,8,8,8,8,8,8 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 3,3,3,3,3,3,3,3,3,3 },
		{ 6,6,6,6,6,6,6,6,6,6 },
		{ 5,5,5,5,5,5,5,5,5,5 },
	};

	int* b[N];
	for (int i = 0; i < N; i++) {
		b[i] = a[i];
	}

	int s[N] = {0};
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			s[i] += a[i][j];
		}
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			if (s[j] < s[j + 1]) {
				std::swap(s[j], s[j + 1]);
				std::swap(b[j], b[j + 1]);
			}
		}
	}

	return 0;
}