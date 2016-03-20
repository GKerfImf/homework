#include<iostream>
#include<string>

struct Point
{
	double x;
	double y;
	std::string toString() {
		return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
	}
};

class Rhombus {
private:
	Point up, left, down, right;
public:
	Rhombus(Point up, Point left, Point down, Point right): 
		up(up), left(left), down(down), right(right) {}

	void draw() {
		std::cout << up.toString() << " " << left.toString() << " " << down.toString() << " " << right.toString() << std::endl;
	};
};

class Rhombus_with_diagonals : public Rhombus {
public:
	Rhombus_with_diagonals(Point up, Point left, Point down, Point right) : Rhombus(up, left, down, right) {}
};

int main() {
	Rhombus(Point{ 0,1 }, Point{ -1,0 }, Point{ 0,-1 }, Point{ 1,0 }).draw();
	Rhombus_with_diagonals(Point{ 0,1 }, Point{ -1,0 }, Point{ 0,-1 }, Point{ 1,0 }).draw();
	return 0;
}