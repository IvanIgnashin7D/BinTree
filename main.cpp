#include <iostream>
#include "BinarySearchTree.h"


int main() {
	BinarySearchTree<int> tree;
	std::cout << (tree.searchItem(1) ? 1 : 0);
	tree.insertItem(4);

	tree.insertItem(2);
	tree.insertItem(1);
	tree.insertItem(3);
	
	tree.insertItem(6);
	tree.insertItem(5);
	tree.insertItem(7);

	tree.print();
}