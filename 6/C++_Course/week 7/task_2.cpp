#include <cassert>
#include <iostream>

struct tree {
	int val;
	tree* left;
	tree* right;
	tree(int v) :
		val(v), left(nullptr),
		right(nullptr)
	{}
};
void print(const tree* p)
{
	if (p !=nullptr) {
		print(p->left);
		std::cout << p->val << " ";
		print(p->right);
	}
}

void add(tree* & p, int v)
{
	if (p == nullptr) {
		p = new tree(v);
	}
	else if (v < p->val) {
		add(p->left, v);
	}
	else {
		add(p->right, v);
	}
}

bool find_even_helper(const tree* p) {
	if (p == nullptr) {
		return false;
	}
	else if (p->val % 2 == 0) {
		throw true;
	}
	else {
		return find_even_helper(p->left) || find_even_helper(p->right);
	}
}

bool find_even(const tree* p) {
	try
	{
		return find_even_helper(p);
	}
	catch (bool result)
	{
		return result;
	}
}


int main() {
	tree* t = nullptr;

	add(t, 1); add(t, 3); add(t, 2); add(t, 7); add(t, 9); add(t, 11);
	print(t);
	std::cout << std::endl << (find_even(t) ? "true" : "false") << std::endl;
	return 0;
}

