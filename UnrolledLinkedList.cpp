#include"UnrolledLinkedList.h"
void UnrolledLinkedList::add(int val) {
	// - C1-- : Urolled Linked List is empty
	if(head == NULL) { // if(tail == NULL) // if(numOfNodes == 0)
		// 1./ Create new new node
		head = tail = new Node(nodeSize);
		++numOfNodes;
		// 2./ Insert the first element into the first node
		head->add(val);
		++size;
		// 3./ End C1
		return;
	}
	// - C2-- : Urolled Linked List is NOT empty
	// + C2_1 : Unrolled Linked List is full
	if(tail->isFull()) {
		// 1./ Create a new node
		Node *newNode = new Node(nodeSize);
		++numOfNodes;
		// 2./ Move final half of tail into new node
		for(int i = tail->getHalfNodeSize(); i < nodeSize; ++i) 
			newNode->add(tail->elements[i]);
		tail->numElements = tail->getHalfNodeSize();
		// 3./ Add val into new node
		newNode->add(val);
		++size;
		// 4./ Adjust tail of Urolled Linked List 
		tail->next = newNode;
		newNode->prev = tail;
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
            int index = pNode->numElements + pos;
			// C1__ : Node is not full
			if(!pNode->isFull()) {
				// 1./ Add val into current node
				pNode->insertAt(index, val);
				++size;
				// 2./ End C1
				return;
			} else {
                ++size;
			// C2__ : Node is full
				// 1/. Keep the last element of array (x)
                int temp = pNode->elements[pNode->numElements - 1];
				// 2/. Remove the last element of array
                pNode->removeAt(pNode->numElements - 1);
				// 3/. Insert val
                pNode->insertAt(index, val);
                // 4/. Create new node
                Node* newNode = new Node(nodeSize);
                ++numOfNodes;
				// 5/. Move final half of tail into new node
                for (int k = pNode->getHalfNodeSize(); k < nodeSize; ++k)
                    newNode->add(pNode->elements[k]);
				for (int k = pNode->numElements - 1; k >= pNode->getHalfNodeSize(); --k) 
                    pNode->removeAt(k);
				// 6/. Insert x to new Node
                newNode->add(temp);
				// 7/. Adjust pointer
                newNode->next = pNode->next;
                pNode->next = newNode;
                newNode->prev = pNode;
                if(newNode->next != NULL) newNode->next->prev = newNode;
                if(pNode == tail) tail = newNode;
                return;
			}
		}
	}
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	size--;
	// C1__ : List has one node
	if (numOfNodes == 1)
	{
		head->removeAt(pos);
		if(head->numElements == 0) {
			delete head;
			head = tail = NULL;
			--numOfNodes;
		}
		return;
	}
	// C2__ : List has many node
	int index = 0;
	for (Node *pNode = head;  pNode != NULL;  pNode =  pNode->next) {
	for (int i = 0; i <  pNode->numElements; i++) {
	if (index == pos) {
		if ( pNode->numElements >  pNode->getHalfNodeSize()) {
			pNode->removeAt(i);
			return;
		}
		else {
			// Head
			if ( pNode == head) {
				if ( head->next->numElements >  head->getHalfNodeSize()) {
					head->removeAt(i);
					head->add( head->next->elements[0]);
					head->next->removeAt(0);
					return;
				}
				else {
					head->removeAt(i);
					for (int k = 0; k <  head->next->getHalfNodeSize(); k++)
						head->add( head->next->elements[k]);
					Node* dltNode =  head->next;
					if (dltNode->next != NULL) dltNode->next->prev = head;
					else tail = head;
					head->next = dltNode->next;
					delete dltNode;
					numOfNodes--;
					return;
				}
			}
			// Tail
			else if (pNode == tail) {
				if ( tail->prev->numElements >  tail->getHalfNodeSize()) {
					tail->removeAt(i);
					tail->insertAt(0, tail->prev->elements[ tail->prev->numElements - 1]);
					tail->prev->removeAt( tail->prev->numElements - 1);
					return;
				}
				else {
                    tail->removeAt(i);
		 			for (int k = 0; k <  tail->numElements; k++) 
						tail->prev->add( tail->elements[k]);
					Node* dltNode =  tail;
					tail = tail->prev;
					tail->next = NULL;
					delete dltNode;
					numOfNodes--;
					return;
				}
			}
			//Mid node
			else {
				if ( pNode->next->numElements >  pNode->next->getHalfNodeSize()) {
					pNode->removeAt(i);
					if ( pNode->prev->numElements ==  pNode->prev->getHalfNodeSize()) {
						for (int k = 0; k <  pNode->numElements; k++)
								pNode->prev->add( pNode->elements[k]);
						Node* dltNode =  pNode;
						if (dltNode->next != NULL) dltNode->next->prev = dltNode->prev;
						else tail = dltNode->prev;
						if (dltNode->prev != NULL) dltNode->prev->next = dltNode->next;
						delete dltNode;
						numOfNodes--;
						return;
					}
					else {
						pNode->add( pNode->next->elements[0]);
						pNode->next->removeAt(0);
						return;
					}
				}
				else {
					pNode->removeAt(i);
					for (int k = 0; k <  pNode->next->getHalfNodeSize(); k++)
						pNode->add( pNode->next->elements[k]);
                    Node* temp =  pNode->next;
					if (temp->next != NULL) temp->next->prev = temp->prev;
					else tail = temp->prev;
					if (temp->prev != NULL) temp->prev->next = temp->next;
					delete temp;
					numOfNodes--;
					return;
				}
			}
		}
	}
	index++;
}
}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	// C1 : Found
	int index = 0;
	// 1./ Travels from the head to the tail of Unrolled Linked List
	for (Node* pNode = head; pNode != NULL; pNode = pNode->next)
	    // 1./ Travels from the head to the tail of Array
		for (int i = 0; i < pNode->numElements; i++) {
			if (pNode->elements[i] == val) return index;
			index++;
		}
	// C2 : Not found
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	// C1 : Found
	int index = size-1;
	// 1./ Travels from the tail to the head of Unrolled Linked List
	for (Node* pNode = tail; pNode != NULL; pNode = pNode->prev) {
	    // 1./ Travels from the tail to the head of Array
		for (int i = pNode->numElements - 1; i >= 0; i--) {
			if (pNode->elements[i] == val) return index;
			index--;
		}
	}
	// C2 : Not found
	return -1;
}

bool UnrolledLinkedList::contains(int val) {
	// C1 : Found
	// 1./ Travels from the head to the tail of Unrolled Linked List
	for(Node *pNode = head; pNode != NULL; pNode = pNode->next) {
		// 1./ Travels from the head to the tail of Array
		for(int i = 0; i < pNode->numElements; i++) {
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
	if(head == NULL) return;
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
	if(head == NULL) return NULL;
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
