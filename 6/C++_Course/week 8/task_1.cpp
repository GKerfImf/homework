#include <iostream>
#include <functional>

class abc {
public:
	abc() { ++n; }
	~abc() { --n; }

	static int num(){
		return n;
	}

private:
	static int n;
};

int abc::n = 0;

int main() {
	abc x; abc y;
	std::cout << abc::num() << std::endl;

	abc z;
	std::cout << abc::num() << std::endl;

	x.~abc();
	std::cout << abc::num() << std::endl;
	return 0;
}