#pragma once
template<class T>
class StackList
{
private:
	struct Node {
		T value_;
		Node* next_;
		Node(T value, Node* next) : value_(value), next_(next) {};
	};
	Node* first_;

public:
	StackList() : first_(nullptr) {};

	void push(const T& e) {
		if (first_) {
			first_ = new Node(e, first_);
			return;
		}
		first_ = new Node(e, nullptr);
	}

	T top() {
		return first_->value_;
	}

	T pop() {
		T value = first_->value_;
		Node* first = first_;
		first_ = first_->next_;
		delete first;
		return value;
	}

	bool empty() {
		return (first_) ? false : true;
	}
};
