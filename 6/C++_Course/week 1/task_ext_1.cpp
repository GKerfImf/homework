#include<iostream>

int main() {
	int a[1000]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,0};

	int l = 0, r = 999;

	while (l <= r) {
		if (* (a + (l + r) / 2) == 0){
			r = (l + r) / 2 - 1;
		}
		else {
			l = (l + r) / 2 + 1;
		}
	}

	std::cout << l << std::endl;

	return 0;
}