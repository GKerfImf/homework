#include<string>
#include<iostream>

struct List {
	int val;
	List *next;

	std::string toString() {
		if (next == nullptr) {
			return "|nil|\n";
		}
		else {
			return "|" + std::to_string(val) + "| -->" + (next->toString());
		}
	}
};

void add_to_nth(List *lst, int n, int x) {

	if (n < 0) {
		return;
	}

	List *ptr = lst;
	for (int i = 0; i < n && ptr != nullptr; i++) {
		ptr = ptr->next;
	}

	if (ptr == nullptr)
		return;

	List *new_node = new List;

	new_node->val = x;
	new_node->next = ptr->next;
	ptr->next = new_node;

	std::swap(new_node->val, ptr->val); //??
}

List* last_elem(List *lst) {
	List *ptr = lst;

	while (ptr->next->next != nullptr) {
		ptr = ptr->next;
	}
	return ptr;
}

List* reverse(List *lst) {
	List *ptr = lst;

	List *newHead = new List;
	newHead->next = nullptr;

	while (ptr->next != nullptr) {
		List *ptr2 = new List;
		ptr2->next = ptr->next;
		ptr2->val = ptr->val;

		ptr = ptr->next;

		std::swap(newHead->val, ptr2->val);
		ptr2->next = newHead->next;
		newHead->next = ptr2;
	}
	return newHead;
}


int main() {
	List *head = new List;
	head->next = nullptr;

	for (int i = 8; i >= 0; i--) {
		List *node = new List;
		node->next = head->next;
		node->val = head->val;

		head->next = node;
		head->val = i;
	}

	std::cout << head->toString() << std::endl;

	add_to_nth(head, 5, 100);
	std::cout << head->toString();

	last_elem(head)->val++;
	last_elem(head)->val = last_elem(head)->val * last_elem(head)->val;
	std::cout << head->toString();

	std::cout << reverse(head)->toString();
	std::cout << head->toString();

	return 0;
}