/******************************************************************************
*	AJ Regester
*	CS2320, Data Structures
*	Project 2 + Bonus
*
*	AVLTree.cpp
******************************************************************************/

#include "AVLTree.h"
#include <iostream>

using namespace std;

//******************************************************************************
//	Constructs a new AVL tree object
//******************************************************************************
AVLTree::AVLTree(){
	// assign all tree values to null
	for(int i = 0; i<256; i++)
		treeArray[i] = -1;
}

//******************************************************************************
//	Inserts a value into the AVL tree while maintaining the AVL properties
//  
// **PARAMETERS
//
// 	value 	- the value to be added to the tree
//******************************************************************************
void AVLTree::insert(int value){
	// search for the value to be added
	treeArray[search(value, 0, false)] = value;
	// clear the stack that will store the path from the new node to the root
	pathStack.clearStack();
	// ensure the AVL properties are maintained 
	checkForAVL(getDeepestNode());
}

//******************************************************************************
//	Inserts a value into the tree without checking if the AVL property is 
//	maintained.  This is only used to rebuild the tree after a rotation has 
//  been made.
//  
// **PARAMETERS
//
// 	value 	- the value to be added to the tree
//******************************************************************************
void AVLTree::insertWithoutCheck(int value){
	treeArray[search(value, 0, false)] = value;
}

//******************************************************************************
//	Deletes a value from the tree
//  
// **PARAMETERS
//
// 	value 	- the value to be deleted from the tree
//******************************************************************************
void AVLTree::deleteNode(int value){
	int indexToDelete = search(value, 0, true);
	
	// if the value to delete exists within the AVL tree...
	if(indexToDelete != -1){
		// node to delete has no children
		if(isNull(leftChild(indexToDelete))	&& isNull(rightChild(indexToDelete))){
			treeArray[indexToDelete] = -1;
		}
		// node to delete has at least one child
		else{
			// remove the subtree beginning with indexToDelete and store
			// the values in a nodeQueue
			removeAndStoreSubtree(indexToDelete);
			// first value is the node to be deleted, so dequeue()
			nodeQueue.dequeue();
			// restore the subtree by inserting the values back into the
			// tree
			restoreSubtrees();
		}
		// check that AVL properties are maintained; if not, repair
		checkForAVL(getDeepestNode());
	}
	// else the value does not exist within the BST
	else
		cout << value << " is not in this BST." <<  endl;
}

//******************************************************************************
//	Searches the tree and returns the index at which the value is located.
//  
// **PARAMETERS
//
// 	value 	- the value that is being searched for
//	index 	- the index at which to start the search
//	present - boolean value, specifies whether the function returns null
//			  or the index value at which the value parameter would be
//		  	  placed if inserted. 
// **RETURNS
//
//	int - If the value is not located within the BST, search will return -1 if 
// 	 	  the "present" parameter is passed as true; if the "present" parameter
// 		  is passed as false, the index of the location where the new value 
//		  would be located at, if inserted, will be returned.
//******************************************************************************
int AVLTree::search(int value, int index, bool present){
	// if current node value is the value searched for, return current node
	if (treeArray[index] == value)
		return index;
	// else if node not found and current node is null, return null or index of
	// null node depending on the value of the "present" parameter
	else if (treeArray[index] == -1){
		if(present)
			return -1;
		else
			return index;
	}
	// continue searching for the node further down the tree
	else{
		if(value < treeArray[index])
			return search(value, leftChild(index), present);
		else
			return search(value, rightChild(index), present);
	}
}

//******************************************************************************
//	Returns the maximum value located in the tree
//  
// **RETURNS
//
//	int - The maximum value that is present in the tree.
//******************************************************************************
int AVLTree::findMax(int rootNode){
	int currentIndex = rootNode;
	while(!isNull(rightChild(currentIndex)))
		currentIndex = rightChild(currentIndex);
	return treeArray[currentIndex];
}

//******************************************************************************
//	Returns the minimum value located in the tree
//  
// **RETURNS
//
//	int - The minimum value that is present in the tree.
//******************************************************************************
int AVLTree::findMin(int rootNode){
	int currentIndex = rootNode;
	while(!isNull(leftChild(currentIndex)))
		currentIndex = leftChild(currentIndex);
	return treeArray[currentIndex];
}

//******************************************************************************
//	Prints the AVL tree in an array format
//******************************************************************************
void AVLTree::printAVL(){
	for (int i = 0; i < 256; i++)
		if(treeArray[i] != -1)
			cout << "Index "<< i << ": " << treeArray[i] << " | ";
	cout << endl;
}

//******************************************************************************
//	Prints the AVL tree in a visual ASCII format
//  
// **PARAMETERS
//
//	index 	- the index at which to start printing (typically the root)
//	indent  - a value is not passed when this function is called, but it is 
//			  present in order to format the tree correctly as the method is 
//			  called recursively.
//******************************************************************************
void AVLTree::printAVLBonus(int index, string indent){
	string indentStep =  "     ";
	string indentStep2 = "  ";
		if (!isNull(index)) {

			printAVLBonus(rightChild(index), indent + indentStep);

			if (!isNull(rightChild(index))) {
				cout << indent + indentStep2 + "/" << endl;
			}

			cout << indent << treeArray[index] << endl;

			if (!isNull(leftChild(index))) {
				cout << indent + indentStep2 + "\\" << endl;
			}

			printAVLBonus(leftChild(index), indent + indentStep);
		}
} 
    		
//******************************************************************************
//	Tests whether the node located at parameter "index" is null
//  
// **PARAMETERS
//
//	index 	- the index value being tested 
// 
// **RETURNS
//
//	bool - returns True if the node is null, false otherwise
//******************************************************************************
bool AVLTree::isNull(int index){
	if(treeArray[index] == -1)
		return true;
	else
		return false;
}

//******************************************************************************
//	Tests whether the node located at parameter "index" is null
//  
// **PARAMETERS
//
//	index 	- the index value being tested 
// 
// **RETURNS
//
//	bool - returns True if the node is null, false otherwise
//******************************************************************************
int AVLTree::leftChild(int index){
	if (index * 2 + 1 < 256)
		return index * 2 + 1;
	else
		return -1;
}

//******************************************************************************
//	Returns the index of the right child of the node indicated by the "index" 
//  parameter while ensuring the node is in bounds of the tree array.
//  
// **PARAMETERS
//
//	index 	- the index value of the parent node 
// 
// **RETURNS
//
//	int  - returns a number >= 0 if the right child exists and is not null, 
//		   otherwise it returns -1
//******************************************************************************
int AVLTree::rightChild(int index){
	if (index * 2 + 2 < 256)
		return index * 2 + 2;
	else
		return -1;
}

//******************************************************************************
//	Returns the index of the parent node to the index that is passed
//  
// **PARAMETERS
//
//	index 	- the index value of the child node 
// 
// **RETURNS
//
//	int  - returns a number >= 0 if the parent exists, otherwise it returns -1 
//		   if the root node is passed
//******************************************************************************
int AVLTree::parent(int index){
	if(index % 2 == 0){
		return ((index-2)/2);
	}
	else{
		return ((index-1)/2);
	}
}

//******************************************************************************
//	Provided the index of a subtree root node, the root node and all nodes below 
//	it are removed and stored in the global queue by preorder traversal.  This 
//	is mainly used for deletion of nodes with children or to reattach subtrees
//	after rotations done to maintain AVL properties.
//  
// **PARAMETERS
//
//	index 	- the root node of the subtree to be removed 
// 
//******************************************************************************
void AVLTree::removeAndStoreSubtree(int index){
	// enqueue current node if not null
	if(!isNull(index)){
		nodeQueue.enqueue(treeArray[index]);
		treeArray[index] = -1;
	}
	// left child
	if (!isNull(leftChild(index)))
		removeAndStoreSubtree(leftChild(index));
	// right child
	if (!isNull(rightChild(index)))
		removeAndStoreSubtree(rightChild(index));
}

//******************************************************************************
//	Restores all nodes that are stored in the global queue.  Used to reattach
//	nodes and subtrees after calling removeAndStoreSubtree method.
//******************************************************************************
void AVLTree::restoreSubtrees(){
	while(!nodeQueue.empty())
		insert(nodeQueue.dequeue());
}

//******************************************************************************
//	Provided the index of a node, this method returns the height of that node
//  
// **PARAMETERS
//
//	index 	- the node of which the height is to be determind
//
// **RETURNS
//
//	int	  - the height of the node
// 
//******************************************************************************
int AVLTree::getNodeHeight(int index){
	int left, right;
	if (isNull(index))
		return 0;
	left = getNodeHeight(leftChild(index));
	right = getNodeHeight(rightChild(index));
	return 1 + max(left, right);
	
}

//******************************************************************************
//	Provided the index of a node, this method returns the height of that node
//  
// **PARAMETERS
//
//	index 	- the node of which the height is to be determind
//
// **RETURNS
//
//	int	  - the height of the node
//******************************************************************************
int AVLTree::checkForAVL(int index){
	// Ensure current index is within the tree	
	if(index >= 0){
		// Store index as a node on the path from the current node to the root
		pathStack.push(index);
		// get the difference in height between the left and right subtree
		int balance = getNodeHeight(leftChild(index)) - getNodeHeight(rightChild(index));
		// if current node is balanced, move to parent node and check for balance
		if(balance <= 1 && balance >= -1){
			return checkForAVL(parent(index));
		}
		// tree balance is off
		else
			// send index of subtree whose root is unbalanced and its balance 
			// to rebalanceTree();
			rebalanceTree(index);
	}
	return -1;
}

//******************************************************************************
//	This method executes the appropriate shift needed to maintain the AVL 
//	property after an insertion or deletions
//  
// **PARAMETERS
//
//	index 	- the first node that is not currently maintaining the AVL property
//******************************************************************************
void AVLTree::rebalanceTree(int index){
			// save value of first node, pop first node index from stack
			int first = treeArray[pathStack.top()];
			int firstNodeIndex = pathStack.top();
			treeArray[pathStack.pop()] = -1;
			// enqueue the value of the second node and then pop from stack
			nodeQueue.enqueue(treeArray[pathStack.top()]);
			int secondNodeIndex = pathStack.top();
			treeArray[pathStack.pop()] = -1; 
			// enqueue value of third node, pop third index from stack
			nodeQueue.enqueue(treeArray[pathStack.top()]);
			int thirdNodeIndex = pathStack.top();
			treeArray[pathStack.pop()] = -1;
			// enqueue value of the first node
			nodeQueue.enqueue(first);
			
			// storeAndSaveSubtrees of nodes that are being shifted
			removeAndStoreSubtree(firstNodeIndex);
			removeAndStoreSubtree(secondNodeIndex);
			removeAndStoreSubtree(thirdNodeIndex);
			// reinsert values into tree
			restoreSubtrees();
}

//******************************************************************************
//	This method returns the index of the deepest node in the tree, which is 
//	used to check the AVL properties
//  
// **RETURNS
//	int - the index of the deepest node of the tree
//******************************************************************************
int AVLTree::getDeepestNode(){
	int deepestNodeIndex = -1;
	for(int i = 0; i<256; i++){
		if(treeArray[i]!=-1)
			deepestNodeIndex = i;
	}
	return deepestNodeIndex;
}

#endif
