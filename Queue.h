#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;

class Queue{
	private:
	
		int queue[25][2], queueFront, queueBack, size;
		vector<int> availableIndeces;
	
	public:
	
		Queue();
		int dequeue();
		void enqueue(int);
		int front();
		bool empty();
		bool full();
		void display();
		int nextAvailableIndex();
		
};

Queue::Queue(){
	for(int i = 0; i<25; i++){
		availableIndeces.push_back(i);
	}
	
	for(int i = 0; i<25; i++){
		for (int j = 0; j<2; j++){
			queue[i][j] = -2;
		}
	}
	
	srand(time(0));
	
	queueFront = nextAvailableIndex();
	queueBack = queueFront;
	size = 0;
}

int Queue::dequeue(){
	if (!empty()){
		// create temporary variable to hold the current front of queue index
		int old_front_index = queueFront;
		// change front of queue to the "next" node
		queueFront = queue[old_front_index][1];
		// add index value of old front back to the list of available indeces
		availableIndeces.push_back(old_front_index);
		// decrease size by one
		size--;
		return queue[old_front_index][0];
	}
	else{
		cout << "Queue empty!" << endl;
	}
}

void Queue::enqueue(int value){
	if(!full()){	
		// store the passed value in the new node
		queue[queueBack][0] = value;	
		// generate new empty back node
		int nextIndex = nextAvailableIndex();
		// change old back of queue "next" to the new empty back node
		queue[queueBack][1] = nextIndex;
		// reassign the back of queue pointer to the newly generated empty node
		queueBack = nextIndex;	
		// increase the size variable		
		size++;
	}
	else{
		cout << "Queue full!" << endl;
	}
}

int Queue::front(){
		if (!empty()){
		return queue[queueFront][0];
	}
	else{
		cout << "Queue empty!" << endl;
	}
}

bool Queue::empty(){
	if (size==0){
		return true;
	}
	else{
		return false;	
	}
}

bool Queue::full(){
	if (size==24){
		return true;
	}
	else{
		return false;	
	}
}

void Queue::display(){

	int currIndex = queueFront;
	cout << endl;
	cout << "Front --> ";
	for(int i=0; i<size; i++){
		cout << queue[currIndex][0] << " ";
		currIndex = queue[currIndex][1];
	}
	cout << endl;
}

int Queue::nextAvailableIndex(){
	if(!full()){
		// generate new random index location for the new node
		int queueIndex, vectorIndex;
		vectorIndex = rand()%availableIndeces.size();
		queueIndex = availableIndeces.at(vectorIndex);
		// erase the randomly chosen index from the available indeces list
		availableIndeces.erase(availableIndeces.begin()+vectorIndex);
		return queueIndex;
	}
	else{
		return -1;
	}
}

#endif
