/*******************************************************************************
*	AJ Regester
*	CS2320, Data Structures
*	Project 2 + Bonus
*
*	AVLTree.h
*******************************************************************************/


#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stdlib.h>
#include "Queue.h"
#include "Stack.h"

using namespace std;

class AVLTree{

	private:
		int treeArray[256];
		Queue nodeQueue;
		Stack pathStack;
	
		void insertWithoutCheck(int value);
		int leftChild(int index); 
		int rightChild(int index);
		int parent(int index); 
		void removeAndStoreSubtree(int index); 
		void restoreSubtrees();
		int getNodeHeight(int index);
		int checkForAVL(int index);
		void rebalanceTree(int index);
		bool isNull(int index);
		int getDeepestNode();
		
	public:
		AVLTree();
		void insert(int value); 
		void deleteNode(int value); 
		int search(int value, int startIndex, bool present); 
		int findMax(int rootNode);
		int findMin(int rootNode); 
		void printAVL();
		void printAVLBonus(int index, string indent); 
};
