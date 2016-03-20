#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <class T>
std::vector<T> filter(std::function<bool(T)> pred, const std::vector<T> vec)
{
	std::vector<T> result;
	for (auto it : vec) {
		if (pred(it)) result.push_back(it);
	}
	return result;
}

template <class T>
int sum(const std::vector<T> vec)
{
	T result = 0;
	for (auto it : vec) {
		result += it;
	}
	return result;
}

int main()
{
	std::vector< int > nums;

	int in; std::cin >> in;
	while (in != 0) {
		nums.push_back(in);
		std::cin >> in;
	} 

	double average = sum(nums) / (double)nums.size();
	std::cout << "average = " << average << std::endl;

	//greater_than :: double -> int -> bool
	auto greater_than =
		[](double av) {
		return
			[av](int i) { return i >= av; };
		};

	auto result = filter<int>(greater_than(average), nums);
	for_each(result.begin(), result.end(), [](int n) {std::cout << n << " "; });
	std::cout << std::endl;

	return 0;
}