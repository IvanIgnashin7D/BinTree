#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "QueueVector.h"

template <class T>
class BinarySearchTree
{
private:
	struct Node {
		T key_;
		Node* left_;
		Node* right_;
		Node* p_;
		Node(const T& key, Node* left = nullptr, Node* right = nullptr,
			Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p) {
		}
	};

	Node* root_;

	void clear(Node* node) {
		if (node) {
			clear(node->left_);
			clear(node->right_);
			delete node;
		}
	}

	Node* searchIterative(const T& key) const {
		if (root_ == nullptr)
			return nullptr;
		Node* current = root_;
		while (true) {
			if (current->key_ == key)
				return current;
			if (current->left_ && current->left_->key_ < key)
				current = current->left_;
			if (current->right_ && current->right_->key_ > key)
				current = current->right_;
			else
				return nullptr;
		}
	}

public:
	BinarySearchTree() : root_(nullptr) {}

	BinarySearchTree(BinarySearchTree&& other) noexcept
		: root_(other.root_)
	{
		other.root_ = nullptr;
	}

	BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
		if (this != &other) {
			clear(root_);
			root_ = other.root_;
			other.root_ = nullptr;
		}
		return *this;
	}

	~BinarySearchTree() {
		clear(root_);
	}

	BinarySearchTree(const BinarySearchTree&) = delete;
	BinarySearchTree& operator=(const BinarySearchTree&) = delete;


	Node* searchIterative(const T& key) {
		if (root_ == nullptr)
			return nullptr;
		Node* current = root_;
		while (current) {
			if (current->key_ == key)
				return current;
			if (current->left_ && current->left_->key_ >= key)
				current = current->left_;
			if (current->right_ && current->right_->key_ <= key)
				current = current->right_;
			else
				break;
		}
		return nullptr;
	}

	bool insert(T key) {
		if (root_ == nullptr) {
			root_ = new Node(key);
			return true;
		}

		if (searchIterative(key))
			return false;

		Node* current = root_;
		while (true) {
			if (current->left_ == nullptr && key < current->key_) {
				Node* newNode = new Node(key);
				current->left_ = newNode;
				return true;
			}
			if (current->right_ == nullptr && key > current->key_) {
				Node* newNode = new Node(key);
				current->right_ = newNode;
				return true;
			}
			if (current->left_ && current->key_ > key) {
				current = current->left_;
				continue;
			}
			if (current->right_ && current->key_ < key) {
				current = current->right_;
				continue;
			}
		}
	}

	bool remove(T key) {
		Node** current_ptr = &root_;
		Node* current = root_;

		while (current != nullptr && current->key_ != key) {
			if (key < current->key_) {
				current_ptr = &current->left_;
				current = current->left_;
			}
			else {
				current_ptr = &current->right_;
				current = current->right_;
			}
		}

		if (current == nullptr) {
			return false;
		}

		if (current->right_ == nullptr) {
			*current_ptr = current->left_;
			delete current;
			return true;
		}

		if (current->right_->left_ == nullptr) {
			current->right_->left_ = current->left_;
			*current_ptr = current->right_;
			delete current;
			return true;
		}

		Node** min_ptr = &current->right_;
		Node* min_node = current->right_;
		while (min_node->left_ != nullptr) {
			min_ptr = &min_node->left_;
			min_node = min_node->left_;
		}

		*min_ptr = min_node->right_;
		min_node->left_ = current->left_;
		min_node->right_ = current->right_;
		*current_ptr = min_node;
		delete current;

		return true;
	}

	void output(Node* node, std::ostream& out) const {
		if (!node) return;

		out << node->key_;

		if (node->left_ || node->right_) {
			out << '(';
			output(node->left_, out);
			out << ')';

			if (node->right_) {
				out << '(';
				output(node->right_, out);
				out << ')';
			}
		}
	}

	void output(std::ostream& out) const {
		output(root_, out);
		out << '\n';
	}


	int getNumberOfNodes(Node* node) const {
		int res = 0;
		if (!node)
			return 0;
		if (node)
			res++;
		if (node->left_)
			res += getNumberOfNodes(node->left_);
		if (node->right_)
			res += getNumberOfNodes(node->right_);
		return res;
	}

	int getNumberOfNodes() const {
		return getNumberOfNodes(root_);
	}


	int getHeight(Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		int leftHeight = getHeight(node->left_);
		int rightHeight = getHeight(node->right_);
		return std::max(leftHeight, rightHeight) + 1;
	}

	int getHeight() const {
		return getHeight(root_);
	}

	void inorderWalkIterative() const {
		std::vector<T> result;
		std::stack<Node*> stack;
		Node* current = root_;

		while (current != nullptr || !stack.empty()) {
			while (current != nullptr) {
				stack.push(current);
				current = current->left_;
			}

			current = stack.top();
			stack.pop();
			result.push_back(current->key_);

			current = current->right_;
		}

		for (T i : result) std::cout << i << ", ";
		std::cout << '\n';
	}

	void inorderWalkIterative(std::vector<T> &result) const {
		std::stack<Node*> stack;
		Node* current = root_;

		while (current != nullptr || !stack.empty()) {
			while (current != nullptr) {
				stack.push(current);
				current = current->left_;
			}

			current = stack.top();
			stack.pop();
			result.push_back(current->key_);

			current = current->right_;
		}
		return;
	}

	void inorderWalk(Node* current) const {
		if (current == nullptr) return;

		inorderWalk(current->left_);
		std::cout << current->key_ << ", ";
		inorderWalk(current->right_);
	}

	void inorderWalk() const {
		inorderWalk(root_);
	}

	void walkByLevels() const {
		if (!root_) return;

		QueueVector<Node*> q(2);
		q.enQueue(root_);

		while (!q.isEmpty()) {
			Node* current = q.deQueue();
			std::cout << current->key_ << ", ";

			if (current->left_)
				q.enQueue(current->left_);
			if (current->right_)
				q.enQueue(current->right_);
		}
	}
};
