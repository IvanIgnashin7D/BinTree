#include <iostream>
#include "BinarySearchTree.h"


int main() {
	BinarySearchTree<int> tree;
	std::cout << (tree.searchItem(1) ? 1 : 0) << '\n';
	tree.insertItem(4);

	tree.insertItem(2);
	tree.insertItem(3);
	tree.insertItem(1);
	
	tree.insertItem(6);
	tree.insertItem(5);
	tree.insertItem(7);
	tree.insertItem(8);

	tree.print();
	std::cout << tree.howManyNodes() << '\n';
	std::cout << tree.getHeight() << '\n';
	tree.inorderWalkIterative();
	tree.inorderWalk();
}