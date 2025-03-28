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
	//static Node* staticroot_;

	void clear(Node* node) {
		if (node) {
			clear(node->left_);
			clear(node->right_);
			delete node;
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


	Node* searchItem(T key) {
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

	bool insertItem(T key) {
		if (root_ == nullptr) {
			root_ = new Node(key);
			return true;
		}
		
		if (searchItem(key)) 
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

	void deleteItem(T key) {
		Node* current = searchItem(key);
		if (current == nullptr)
			return;
		if (current->right_ == nullptr) {
			current = current->left_;
			return;
		}
		if (current->right_->left_ == nullptr) {
			current->right_->left_ = current->left_;
			current = current->right_;
			return;
		}
		if (current->right_->left_ != nullptr) {
			Node* curMin = current;
			while (curMin->left_ != nullptr) {
				curMin = curMin->left_;
			}
			current = curMin;
			deleteItem(curMin->key_);
			return;
		}
	}

	void print(Node* node, int space = 0, int step = 4) {
		if (node == nullptr) {
			return;
		}

		space += step;

		print(node->right_, space);

		std::cout << '\n';
		for (int i = step; i < space; i++) {
			std::cout << ' ';
		}
		std::cout << "--(" << node->key_ << ')' << '\n';

		print(node->left_, space);
	}

	void print() {
		print(root_);
	}


	int getNumberOfNodes(Node* node) {
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

	int getNumberOfNodes() {
		return getNumberOfNodes(root_);
	}


	int getHeight(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftHeight = getHeight(node->left_);
		int rightHeight = getHeight(node->right_);
		return std::max(leftHeight, rightHeight) + 1;
	}

	int getHeight() {
		return getHeight(root_);
	}

	void inorderWalkIterative() {
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

	void inorderWalkIterative(std::vector<T> &result) {
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

	void inorderWalk(Node* current) {
		if (current == nullptr) return;

		inorderWalk(current->left_);
		std::cout << current->key_ << ", ";
		inorderWalk(current->right_);
	}

	void inorderWalk() {
		inorderWalk(root_);
	}

	void walkByLevels() {
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
