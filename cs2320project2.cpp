/*******************************************************************************
*	AJ Regester
*	CS2320, Data Structures
*	Project 2 + Bonus
*
*	project2.cpp
*******************************************************************************/

#include "AVLTree.h"
#include <iostream>

using namespace std;

main(){
	AVLTree avlTree;
	
	avlTree.insert(5);
	avlTree.insert(8);
	avlTree.insert(3);
	avlTree.insert(1);
	avlTree.insert(4);
	avlTree.insert(9);
	avlTree.insert(18);
	avlTree.insert(20);
	avlTree.insert(19);
	avlTree.insert(2);
	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
	
	cout << "The maximum value in the tree is: " << avlTree.findMax(0) << endl;
	cout << "The minimum value in the tree is: " << avlTree.findMin(0) << endl;
	cout << "The value of 3 is at index: " << avlTree.search(3, 0, true) << endl;
	cout << "The value of 18 is at index: " << avlTree.search(18, 0, true) << endl;
	cout << "The value of 19 is at index: " << avlTree.search(19, 0, true) << endl;
	
	
	avlTree.deleteNode(19);	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
	
	
	avlTree.deleteNode(2);	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
	
	avlTree.deleteNode(8);	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
	
	avlTree.deleteNode(3);	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
	
	avlTree.deleteNode(5);	
	avlTree.printAVL();
	avlTree.printAVLBonus(0, "");
}
