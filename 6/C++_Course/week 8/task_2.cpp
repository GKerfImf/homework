#include <iostream>
#include <functional>

double pow_x_3 (double x) {
	return x * x * x;
}

int main() {
	auto sin_x = [](double x) {return sin(x); };

	auto integral = [](std::function<double(double)> f, double a, double b) {
		double h = (b - a) / 1000;
		double result = (f(a) + f(b))/2;
		for (double x = a + h; x <= b - h; x += h) {
			result += f(x);
		}
		result *= h;
		return result;
	};

	std::cout << integral(pow_x_3, -1, 2) << std::endl;
	std::cout << integral(sin_x, -2, 2) << std::endl;
	std::cout << integral([](double x) { return 1 + x + x*x; }, -2, 2) << std::endl;

	return 0;
}