#include<iostream>
#include<string>
#include<tuple>

void firstLastSpace1(std::string str, int& first, int& last) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			first = i;
			break;
		}
	}
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			last = i;
			break;
		}
	}
}

std::tuple<int, int> firstLastSpace2(std::string str){
	int first = 0, last = 0;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ' ') {
			first = i;
			break;
		}
	}
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == ' ') {
			last = i;
			break;
		}
	}

	return std::make_tuple(first, last);
}

int main()
{
	int first1, last1;
	std::string str1 = "123456 654321 123456 654321";
	firstLastSpace1(str1, first1, last1);

	std::string str2 = "123456 654321 123456 654321";
	std::tuple<int, int> firstlast = firstLastSpace2(str2);
	int first2 = std::get<0>(firstlast);
	int last2 = std::get<1>(firstlast);

	std::cout << first1 << " " << last1 << " | " << first2 << " " << last2 << std::endl;
	return 0;
}