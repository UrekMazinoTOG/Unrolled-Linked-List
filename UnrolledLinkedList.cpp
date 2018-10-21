#include"UnrolledLinkedList.h"
void UnrolledLinkedList::add(int val) {
	// - C1-- : Urolled Linked List is empty
	if(tail == NULL) {
		// Create new new node
		head = tail = new Node(nodeSize);
		numOfNodes = 1;
		// Insert the first element into the first node
		tail->add(val);
		size = 1;
		// End Method
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
			newNode->elements[i] = tail->elements[nodeSize - nodeSize/2 + i];
		tail->numElements = nodeSize - nodeSize/2; 
		// Add val into new node
		newNode->add(val);
		++size;
		// Adjust tail of Urolled Linked List 
		newNode->prev = tail;
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
		// Find value of Unrolled Linked List at position
		if(index - pNode->numElements < 0) 
			// Return value of List at position
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
		// Find element of Unrolled Linked List at position(pos)
		if(index - pNode->numElements < 0) {
			// Change value of this element
			pNode->elements[nodeSize + index] = val;
			// End method
			return;
		}
		index -= pNode->numElements; 
	}

}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	int index = pos;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Find element of Unrolled Linked List at position(pos)
		if(index - pNode->numElements < 0) {
			// C1__ : Node is not full
			if(!pNode->isFull()) {
				pNode->insertAt(nodeSize + index, val);
				++size;
			} else {
			// C2__ : Node is full
				// Create a new node
				Node *newNode = new Node(nodeSize);
				++numOfNodes;
				// Move final half of current node into new node
				for(int i = 0; i < nodeSize/2; ++i) 
					newNode->elements[i] = pNode->elements[nodeSize - nodeSize/2 + i];
				pNode->numElements = nodeSize - nodeSize/2;
				// Add val into new node
				newNode->add(val);
				++size;
				// Adjust tail of Urolled Linked List
				// - C2_1 : Current node is tail node OR
				//          Unrolled Linked List has one node
				if(pNode->next == NULL) {
					newNode->prev = tail;
					tail->next = newNode;
					tail = newNode;
				}
				// - C2_2 : Current node is not tail node
				else {
					newNode->next = pNode->next;
					newNode->prev = pNode;
					pNode->next = newNode;
					pNode->next->prev = newNode;
				}
			}
		}
		index -= pNode->numElements; 
	}

}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException";// check whether pos is valid or not
	int index = pos;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Find element of Unrolled Linked List at position(pos)
		if(index - pNode->numElements < 0) {
			// Delete element
			pNode->removeAt(nodeSize + index);
			--size;
			// Shift elements
			if(pNode->numElements < pNode->getHalfNodeSize()){
				if(pNode->next->numElements <= pNode->getHalfNodeSize) {
					for(int i = 0; i < pNode->next->numElements; ++i) {
						pNode->elements[pNode->numElements] = pNode->next->elements[i];
					}
				}
			}
		}
		index -= pNode->numElements; 
	}

}

int UnrolledLinkedList::firstIndexOf(int val) {
	int index = -1;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			// Find element of Unrolled Linked List have same value(val)
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
			// Find element of Unrolled Linked List have same value(val)
			if(pNode->elements[i] == val) return size - index + nodeSize - 1 - i;
			// size - 1 - (index + (nodeSize - 1 - i) + 1) 
			// Đm làm 1 hồi chắc rớt não ra ngoài má ơi !!! Anh khổ quá em à <3
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
// Hàm đối chỗ 2 Node in Tree
void swap(Node* &a, Node* &b) {
	Node* tmp = a;
	a = b;
	b = tmp;
}
void UnrolledLinkedList::reverse() {
	swap(head, tail);
	// Travels from the old head to the old tail of Unrolled Linked List
	for(Node *pNode = tail; pNode != NULL; pNode = pNode->prev) {
		// Reverse Linked List
		swap(pNode->next, pNode->prev);
		// Reverse elements
		pNode->reverse();
	}
}

int* UnrolledLinkedList::toArray() {
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// If Unrolled Linked List is empty ????
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int arr[size];
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
