#include<iostream>
#include<stdexcept>
#include<string>


class Time {
	int hour = 12;
	int min = 0;
public:
	Time(){}
	Time(int h, int m) 
		: hour(h), min(m) {
		if(h < 0 || h > 23 || m < 0 || m > 59)
			throw std::exception("incorrect data");
	}
};

int main() {

	Time time1(10, 20); //Ok.

	try {
		Time time2(59, 20);
	}
	catch (std::exception s) {
		std::cout << s.what() << "\n";
	}
	
	return 0;
}