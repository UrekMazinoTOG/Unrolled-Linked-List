#include"UnrolledLinkedList.h"

void swap(Node* &a, Node* &b) {
	Node* tmp = a;
	a = b;
	b = tmp;
}
void UnrolledLinkedList::add(int val) {
	// - C1--  Urolled Linked List is empty
	if(tail == NULL) {
		// Insert the first element into the first node
		head = tail = new Node(nodeSize);
		tail->add(val);
		size = numOfNodes = 1;
		return;
	}
	// - C2-- : Urolled Linked List is NOT empty
	// + C2_1 : Unrolled Linked List is full
	if(tail->isFull()) {
		// Create a new node
		Node *newNode = new Node(nodeSize);
		++numOfNodes;
		// Move final half of tail into new node
		for(int i = 0; i < nodeSize/2; ++i) 
			newNode->elements[i] = tail->elements[nodeSize - nodeSize/2 + i]
		tail->numOfNodes = nodeSize - nodeSize/2; 
		// Add val into new node
		newNode->add(val);
		++size;
		// Adjust tail of Urolled Linked List 
		tail->next = newNode;
		tail = newNode;
	}
	// + C2_2 : Unrolled Linked List is not full and not empty
	else { 
		// Add val into tail node
		tail->add(val); 
		++size;
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	int index = pos;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		
		if(index - pNode->numElements < 0) 
			return pNode->elements[nodeSize + index];

		index -= pNode->numElements; 
	}

}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	int index = pos;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {

		if(index - pNode->numElements < 0) {
			elements[nodeSize + index] = val;
			return;
		}
		index -= pNode->numElements; 
	}

}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	int index = pos;
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		if(index - pNode->numElements < 0) 
			elements[nodeSize + index] = val;
	}

}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException" // check whether pos is valid or not
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			if(pNode->elements[i] == val) {

			}
		}
	}

}

int UnrolledLinkedList::firstIndexOf(int val) {
	int index = -1;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			if(pNode->elements[i] == val) return index + i + 1;
		}
		index += pNode->numElements;
	}
	// Not found
	return index;

}

int UnrolledLinkedList::lastIndexOf(int val) {
	int index = -1;
	// Travels from the tail to the head of Unrolled Linked List
	for(Node *pNode = tail; pNode != NULL; pNode = pNode->prev) {
		// Travels from the tail to the head of Array
		for(int i = numOfNodes - 1; i >= 0; --i) {
			if(pNode->elements[i] == val) return size - index + nodeSize - 1 - i;
			// size - (index + (nodeSize - 1 - i) + 1) - 1
		}
		index += pNode->numElements;
	}
	// Not found
	return index;
}

bool UnrolledLinkedList::contains(int val) {
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			if(pNode->elements[i] == val) return true;
		}
	}
	// Not found
	return false;
}

void UnrolledLinkedList::reverse() {
	swap(head, tail);
	// Travels from the old head to the old tail of Unrolled Linked List
	for(Node *pNode = tail; pNode != NULL; pNode = pNode->prev) {
		swap(pNode->next, pNode->prev);
		pNode->reverse();
	}
}

int* UnrolledLinkedList::toArray() {
	// Chưa làm trường hợp ULL rỗng
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int *arr = new int[size];
	int index = 0;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			arr[index++] = pNode->elements[i];
		}
	}
	return arr;
}
// nodeSize = 5
// 15   5
// 5
// 5
// 5
// index = -2
// SizeNode + index;

// [-]<->[-]<->
/* ahahaha */