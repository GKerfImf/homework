#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
	using Points = std::vector<std::pair<int,int>>;
	using Point = std::pair<int, int>;

	auto length_sq = [](Point p) { return pow(p.first, 2) + pow(p.second, 2); };

	Points points;

	int a, b; 
	std::cin >> a >> b;
	while (a != 0 || b != 0) {
		points.push_back(std::make_pair(a,b));
		std::cin >> a >> b;
	}

	std::sort(points.begin(), points.end(), 
		[length_sq](Point const& a, Point const& b) {
			return length_sq(a) < length_sq(b); }
	);

	double d = 0;
	if (!points.empty()) {
		d = length_sq(points[0]);
	}

	for (auto p : points) {
		if (length_sq(p) > d) break;
		std::cout << "(" << p.first << "," << p.second << ")" << std::endl;
	}

	return 0;
}