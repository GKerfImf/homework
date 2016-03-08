#include <iostream>
#include <string>

class List{
private:
	struct Node{
		Node(int n): value(n) {}
		Node* node = NULL;
		int value;
	};

public:
	List(int n) : N(n) {
		top = new Node(n);
		Node* curr = top;
		for (int i = n - 1; i >= 0; --i) {
			(*curr).node = new Node(i);
			curr = (*curr).node;
		}
	}

	std::string ToString() {
		std::string result = "";
		Node* p = top;
		while ((*p).node != NULL) {
			result += "[" + std::to_string((*p).value) + "] --> ";
			p = (*p).node;
		}

		result += "[nil]";
		return result;
	}

private:
	Node* top;
	int N;
};

int main() {
	int n;
	std::cin >> n;
	List list(n);
	std::cout << list.ToString() << std::endl;
	return 0;
}