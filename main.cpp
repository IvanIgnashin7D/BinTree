#include <iostream>
#include "BinarySearchTree.h"


template <class T>
bool equalNodes(BinarySearchTree<T>& tree1, BinarySearchTree<T>& tree2);


int main() {
	BinarySearchTree<int> tree1;
	std::cout << (tree1.searchIterative(1) ? "Found" : "Not found") << '\n';
	tree1.insert(4);

	tree1.insert(2);
	tree1.insert(3);
	tree1.insert(1);
	
	tree1.insert(6);
	tree1.insert(5);
	tree1.insert(7);
	tree1.insert(8);

	tree1.output(std::cout);
	std::cout << "Tree1 number of nodes: " << tree1.getNumberOfNodes() << '\n';

	std::cout << "Tree1 height: " << tree1.getHeight() << '\n';

	std::cout << "Tree1 inorderWalkIterative: ";
	tree1.inorderWalkIterative();

	std::cout << "Tree1 inorderWalk: ";
	tree1.inorderWalk();
	std::cout << '\n';

	std::cout << "Tree1 walkByLevels: ";
	tree1.walkByLevels();
	std::cout << '\n';


	BinarySearchTree<int> tree2;
	tree2.insert(20);

	tree2.insert(10);
	//tree2.insert(3);
	tree2.insert(9);
	tree2.insert(11);

	tree2.insert(35);
	tree2.insert(32);
	tree2.insert(33);

	tree2.output(std::cout);

	std::cout << (equalNodes<int>(tree1, tree2) ? "There are some equal nodes" : "There are NO equal nodes") << '\n';
}


template <class T>
bool equalNodes(BinarySearchTree<T>& tree1, BinarySearchTree<T>& tree2) {
	std::vector<T> valuesTree1;
	std::vector<T> valuesTree2;
	tree1.inorderWalkIterative(valuesTree1);
	tree2.inorderWalkIterative(valuesTree2);

	int i1 = 0;
	int i2 = 0;
	while (i1 < valuesTree1.size() && i2 < valuesTree2.size()) {
		if (valuesTree1[i1] == valuesTree2[i2])
			return true;
		if (valuesTree1[i1] > valuesTree2[i2]) {
			i2++;
			continue;
		}
		if (valuesTree1[i1] < valuesTree2[i2]) {
			i1++;
			continue;
		}
	}
	return false;
}