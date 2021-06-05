#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;

class Stack{
	private:
	
		int stack[25][2], stackTop, size;
		vector<int> availableIndeces;
	
	public:
	
		Stack();
		int pop();
		void push(int);
		int top();
		bool empty();
		bool full();
		void display();
		void clearStack();
		
};

Stack::Stack(){
	stackTop = -1;
	size = 0;
	
	for(int i = 0; i<25; i++){
		availableIndeces.push_back(i);
	}
	
	for(int i = 0; i<25; i++){
		for (int j = 0; j<2; j++){
			stack[i][j] = -2;
		}
	}
	
	srand(time(0));
}

int Stack::pop(){
	if (!empty()){
		// create temporary variable to hold the current top of stack index
		int old_top_index = stackTop;
		// change top of stack to the "next" node
		stackTop = stack[old_top_index][1];
		// add index value of old top back to the list of available indeces
		availableIndeces.push_back(old_top_index);\
		// decrease size by one
		size--;
		return stack[old_top_index][0];
	}
	else{
		cout << "Stack empty!" << endl;
	}
}

void Stack::push(int value){
	if(!full()){
		// generate new random index location for the new node
		int stackIndex, vectorIndex;
		vectorIndex = rand()%availableIndeces.size();
		stackIndex = availableIndeces.at(vectorIndex);
		// erase the randomly chosen index from the list
		availableIndeces.erase(availableIndeces.begin()+vectorIndex);
		// store the passed value in the new node
		stack[stackIndex][0] = value;
		// change top of stack to the "next" value of current top node
		stack[stackIndex][1] = stackTop;
		// change the new top to the current node
		stackTop = stackIndex;
		// increase the size variable		
		size++;
	}
	else{
		cout << "Stack full!" << endl;
	}
}

int Stack::top(){
		if (!empty()){
		return stack[stackTop][0];
	}
	else{
		cout << "Stack empty!" << endl;
	}
}

bool Stack::empty(){
	if (size==0){
		return true;
	}
	else{
		return false;	
	}
}

bool Stack::full(){
	if (size==25){
		return true;
	}
	else{
		return false;	
	}
}

void Stack::display(){

	int currIndex = stackTop;
	cout << endl;
	cout << "Top --> ";
	for(int i=0; i<size; i++){
		cout << stack[currIndex][0] << " ";
		
		currIndex = stack[currIndex][1];
	}
	cout << endl;
}

void Stack::clearStack(){
	while(!empty()){
		pop();
	}
}

#endif
