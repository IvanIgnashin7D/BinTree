#pragma once
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
			key_(key), left_(left), right_(right), p_(p) {}
	};

	Node* root_;
	BinarySearchTree(Node* root = Node{}) : root_(root) {}
};
