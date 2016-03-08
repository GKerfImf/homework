#include <iostream>
#include <string>

bool compare(const char* s1, const char* s2) {
	for (int i = 0; i < 100; ++i) {
		if (s1[i] != s2[i]) {
			return false;
		}
		else if (s1[i] == '\0') {
			return true;
		}
	}
	return false;
}

int main() {
	char s1[100];
	char s2[100];

	std::cin.getline(s1, 100);
	std::cin.getline(s2, 100);

	std::cout << (compare(s1,s2) ? "Yes" : "No") << std::endl;

	return 0;
}