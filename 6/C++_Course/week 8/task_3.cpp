#include <iostream>
#include <vector>
#include <iterator>
int main() {
	int n;
	std::cin >> n;

	std::vector<int> vect;
	while(n != 0) {
		vect.push_back(n);
		std::cin >> n;
	}

	for (auto i = vect.rbegin(); i != vect.rend(); i++) {
		std::cout << *i << " ";
	}
	return 0;
}