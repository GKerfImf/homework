#include<iostream>
#include<string>
#include<cmath>

const double PI = 3.14159265;

struct Point
{
	double x;
	double y;
	std::string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	}
};

class Shape {
public:
	virtual double area() = 0;
	virtual double perim() = 0;
};

class Rhombus : public Shape {
private:
	Point up, left, down, right;

public:
	Rhombus(Point up, Point left, Point down, Point right) :
		up(up), left(left), down(down), right(right) {}

	double area() {
		return std::abs(up.y - down.y) * std::abs(right.x - left.x);
	}
	double perim() {
		return 4 * std::sqrt(std::pow(std::abs(up.x - right.x),2) + std::pow(std::abs(up.y - right.y), 2));
	}
};

class Circle : public Shape {
private:
	Point centre;
	double radius;
public:
	Circle(Point centre, double radius) : 
		centre(centre), radius(radius) {}

	double area() {
		return PI*std::pow(radius,2);
	}
	double perim() {
		return 2*PI*radius;
	}
};

int main() {
	std::cout << Circle(Point{ 0,0 }, 1).area() << std::endl;
	return 0;
}