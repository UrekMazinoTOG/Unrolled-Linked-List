#include"UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	// C1-- : Urolled Linked List is empty
	if(tail == NULL) {
		head = tail = new Node(nodeSize);
		tail->add(val);
		size = numOfNodes = 1;
		return;
	}
	// C2-- : Urolled Linked List is NOT empty
	// // C2_1 : Unrolled Linked List is full
	if(tail->isFull()) {
		// Create a new node
		Node *newNode = new Node(nodeSize);
		// Move final half of tail into new node
		for(int i = 0; i < nodeSize/2; ++i) 
			newNode->elements[i] = tail->elements[nodeSize - nodeSize/2 + i]
		tail->numOfNodes = nodeSize - nodeSize/2; 
		// Add val into new node
		newNode->add(val);
		// Adjust tail of Urolled Linked List 
		tail->next = newNode;
		tail = newNode;
	}
	// // C2_2 : Unrolled Linked List is not full and not empty
	else tail->add(val);
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO

}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO

}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	// TODO

}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO

}

int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO

}

int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO

}

bool UnrolledLinkedList::contains(int val) {
	// TODO

}

void UnrolledLinkedList::reverse() {
	// TODO

}

int* UnrolledLinkedList::toArray() {
	// TODO

}