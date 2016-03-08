#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
	std::string str;
	std::getline(std::cin, str);

	std::istringstream iss(str);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

	std::for_each(tokens.rbegin(), tokens.rend(), [](std::string n) {std::cout << n << " "; });
	std::cout << std::endl;

	return 0;
}