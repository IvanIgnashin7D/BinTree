#include <iostream>
#include "BinarySearchTree.h"


int main() {
	BinarySearchTree<int> tree;
	std::cout << (tree.searchItem(1) ? 1 : 0);
	tree.insertItem(1);
}