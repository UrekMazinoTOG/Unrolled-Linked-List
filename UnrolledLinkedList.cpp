#include"UnrolledLinkedList.h"

using namespace std;
void UnrolledLinkedList::add(int val) {
	// - C1-- : Urolled Linked List is empty
	if(tail == NULL) { // if(head == NULL)
		// 1./ Create new new node
		head = tail = new Node(nodeSize);
		numOfNodes = 1;
		// 2./ Insert the first element into the first node
		tail->add(val);
		size = 1;
		// 5./ End C1
		return;
	}
	// - C2-- : Urolled Linked List is NOT empty
	// + C2_1 : Unrolled Linked List is full
	if(tail->isFull()) {
		// 1./ Create a new node
		Node *newNode = new Node(nodeSize);
		++numOfNodes;
		// 2./ Move final half of tail into new node
		for(int i = 0; i < nodeSize/2; ++i) 
			newNode->add(tail->elements[tail->getHalfNodeSize() + i]);
		tail->numElements = tail->getHalfNodeSize();
		// 3./ Add val into new node
		newNode->add(val);
		++size;
		// 4./ Adjust tail of Urolled Linked List 
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		// 5./ End C2_1
		return;
	}
	// + C2_2 : Unrolled Linked List is not full and not empty
	else { 
		// 1./ Add val into tail node
		tail->add(val); 
		++size;
		// 2./ End C2_1
		return;
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// 1./ Find value of Unrolled Linked List at position
		pos -= pNode->numElements; 
		if(pos < 0) 
			// 1./ Return value of List at position
			return pNode->elements[pNode->numElements + pos];
	}
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not

	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) { 
		// 1./ Find element of Unrolled Linked List at position(pos)
		pos -= pNode->numElements;
		if(pos < 0) {
			// 1./ Change value of this element
			pNode->elements[pNode->numElements + pos] = val;
			// 2./ End method
			return;
		}
	}

}

void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// * Special case * : Inserted at the end of the list
	if(pos == size) {this->add(val); return;}
	
	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		pos -= pNode->numElements;
		// 1./ Find element of Unrolled Linked List at position(pos)
		if(pos < 0) {
			// C1__ : Node is not full
			if(!pNode->isFull()) {
				// 1./ Add val into current node
				pNode->insertAt(pNode->numElements + pos, val);
				++size;
				// 2./ End C1
				return;
			} else {
			// C2__ : Node is full
				// 1./ Create a new node
				Node *newNode = new Node(nodeSize);
				++numOfNodes;
				// 2./ Move final half of current node into new node
				for(int i = 0; i < nodeSize/2; ++i) 
					newNode->elements[i] = pNode->elements[pNode->getHalfNodeSize() + i];
				pNode->numElements = pNode->getHalfNodeSize();
				// 3./ Add val into new node
				newNode->add(val);
				++size;
				// 4./ Adjust tail of Urolled Linked List
				// - C2_1 : + Current node is tail node
				//          + Unrolled Linked List has one node
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
				// 2./ End C2
				return;
			}
		}
	}
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException";// check whether pos is valid or not

	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		pos -= pNode->numElements; 
		// 1./ Find element of Unrolled Linked List at position(pos)
		if(pos < 0) {
			// 1./ Delete element
			pNode->removeAt(pNode->numElements + pos);
			--size;
			// 2./ Shift elements
			// - C1__ : Number of Elements in Node great than or equal half node size
			if(pNode->numElements >= pNode->getHalfNodeSize()) return; // Don't do anything
			// - C2__ : Number of Elements in Node less than half node size
			// - C2_1 : Node left != NULL
			if(pNode->next != NULL) {
				// 1./ Move first element of next node into current node
				while(pNode->numElements < pNode->getHalfNodeSize()) {
					pNode->add(pNode->next->elements[0]);
					pNode->next->removeAt(0);
				}
				// 2./ Merge node 
				if(pNode->next->numElements < pNode->getHalfNodeSize()) {
					while(!pNode->next->isEmpty()){
						pNode->add(pNode->next->elements[0]);
						pNode->next->removeAt(0);
					}
					Node *dltNode = pNode->next;
					pNode->next = dltNode->next;
					if(dltNode->next != NULL) dltNode->next->prev = pNode;
					--numOfNodes;
				}
				// 3./ End C2_1
				return;
			}
			// - C2_2 : Node left == NULL, Node right != NULL
			else if(pNode->prev != NULL) {
				// 1./ Move last element of previous node into current node
				while(pNode->numElements < pNode->getHalfNodeSize()) {
					pNode->insertAt(0, pNode->prev->elements[pNode->numElements - 1]);
					--pNode->prev->numElements;
				}
				// 2./ Merge node
				if(pNode->prev->numElements < pNode->getHalfNodeSize()) {
					while(!pNode->prev->isEmpty()){
						pNode->insertAt(0, pNode->prev->elements[pNode->numElements - 1]);
						--pNode->prev->numElements;
					}
					Node *dltNode = pNode->prev;
					pNode->prev = dltNode->prev;
					if(dltNode->prev != NULL) dltNode->prev->next = pNode;
					--numOfNodes;
				}
				// 3./ End C2_2
				return;
			}
			// - C2_3 : Node left == NULL, Node right == NULL
			// Don't do anything
			// End C2
			return;
		}
	}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	int index = -1;
	// C1 : Found
	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// 1./ Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			// 1./ Find element of Unrolled Linked List have same value(val)
			if(pNode->elements[i] == val) return index + i + 1;
		}
		index += pNode->numElements;
	}
	// C2 : Not found
	return -1;

}

int UnrolledLinkedList::lastIndexOf(int val) {
	int index = -1;
	// C1 : Found
	// Travels from the tail to the head of Unrolled Linked List
	for(Node *pNode = tail; pNode != NULL; pNode = pNode->prev) {
		// Travels from the tail to the head of Array
		for(int i = pNode->numElements - 1; i >= 0; --i) {
			// Find element of Unrolled Linked List have same value(val)
			if(pNode->elements[i] == val) return size - index - pNode->numElements + i - 1;
			// size - 1 - (index + (pNode->numOfElemnt - 1 - i) + 1) 
		}
		index += pNode->numElements;
	}
	// C2 : Not found
	return -1;
}

bool UnrolledLinkedList::contains(int val) {
	// C1 : Found
	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// 1./ Travels from the head to the tail of Array
		for(int i = 0; i < numOfNodes; i++) {
			if(pNode->elements[i] == val) return true;
		}
	}
	// C2 : Not found
	return false;
}
// Swap 2 Node in Tree
void swap(Node* &a, Node* &b) {
	Node* tmp = a;
	a = b;
	b = tmp;
}

void UnrolledLinkedList::reverse() {
	// ? List is empty
	if(head == NULL) return;
	// ! 
	swap(head, tail);
	// 1./ Travels from the old head to the old tail of Unrolled Linked List
	for(Node *pNode = tail; pNode != NULL; pNode = pNode->prev) {
		// 1./ Reverse List
		swap(pNode->next, pNode->prev);
		// 2./ Reverse Array
		pNode->reverse();
	}
}

int* UnrolledLinkedList::toArray() {
	// C1 : Unrolled linked list is empty
	return NULL;
	// C2 : Unrolled linked list is NOT empty
	int *arr = new int[size];
	int index = 0;
	// Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// Travels from the head to the tail of Array
		for(int i = 0; i < pNode->numElements; i++) {
			arr[index++] = pNode->elements[i];
		}
	}
	return arr;
}
