#include <iostream>
#include <string>

class Stack {
public:
	Stack() : N(5), n(0) {
		stack = new int[N]{0};
	}
	void push(int x) {
		stack[n] = x;
		n++;
		expand();
	}
	int pop() {
		if (n < 1) return 0;
		int temp = stack[n-1];
		n--;
		contract();
		return temp;
	}
	int& max() {
		int index = 0;
		for (int i = 0; i < n; ++i) {
			if (stack[index] < stack[i]) {
				index = i;
			}
		}
		return stack[index];
	}

	std::string ToString() {
		std::string result = "{";
		// N or n ?
		for (int i = 0; i < n; ++i) {
			result += std::to_string(stack[i]) + ",";
		}
		result += "}";
		return result;
	}

private:
	void expand() {
		if ((n +0.0) / (N + 0.0) > 0.7) {
			N *= 2;
			int* temp = new int[N]{0};
			for (int i = 0; i < n; ++i) {
				temp[i] = stack[i];
			}
			delete[] stack;
			stack = temp;
		}
	}
	void contract() {
		if ((n + 0.0) / (N + 0.0) < 0.6) {
			N *= 3.0/4.0;
			int* temp = new int[N]{ 0 };
			for (int i = 0; i < n; ++i) {
				temp[i] = stack[i];
			}
			delete[] stack;
			stack = temp;
		}
	}

	int n = 0;
	int N = 0;
	int* stack;
};

int main() {
	Stack stack;

	for (int i = 1; i <= 10; ++i) {
		stack.push(i*i % 100);
		std::cout << stack.ToString() << std::endl;
	}

	std::cout << "max --> -10 \n";
	stack.max() = -10;
	std::cout << stack.ToString() << std::endl;
	std::cout << "max --> ++ \n";
	stack.max()++;
	std::cout << stack.ToString() << std::endl;

	for (int i = 1; i <= 10; ++i) {
		stack.pop();
		std::cout << stack.ToString() << std::endl;
	}
	for (int i = 1; i <= 10; ++i) {
		stack.push(i*i % 100);
		std::cout << stack.ToString() << std::endl;
	}

	return 0;
}