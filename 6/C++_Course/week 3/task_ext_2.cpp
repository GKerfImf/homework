#include <iostream>
#include <string>

bool compare(const char* s1, const char* s2) {
	int i = 0, j = 0;

	while (i < 100 && j < 100) {
		if (s1[i] == ' ') {
			i++;
			continue;
		}
		if (s2[j] == ' ') {
			j++;
			continue;
		}

		if (s1[i] != s2[j]) {
			return false;
		}
		else if (s1[i] == '\0') {
			return true;
		}

		i++; j++;
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