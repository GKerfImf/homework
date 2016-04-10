#include <cassert>
#include <iostream>

class rational {
	int numerator;
	int denominator;

public:
	explicit rational(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
		if (denominator <= 0) throw "denominator must be > 0";
	}

	operator double() const
	{
		return (double)numerator/ denominator;
	}
};

int main() {
	rational pi(22, 7);
	double p = pi;
	std::cout << p << std::endl;
	return 0;
}