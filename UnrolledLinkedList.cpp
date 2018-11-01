#include"UnrolledLinkedList.h"
void UnrolledLinkedList::add(int val) {
	// - C1-- : Urolled Linked List is empty
	if(head == NULL) { // if(tail == NULL)
		// 1./ Create new new node
		head = tail = new Node(nodeSize);
		++numOfNodes;
		// 2./ Insert the first element into the first node
		head->add(val);
		++size;
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
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		// 5./ End C2_1
		return;
	}
	// + C2_2 : Unrolled Linked List is not full and not empty
	else { 
		// ? Thêm trường hợp
		// ? Nếu Tail->prev khác NULL
		// ? Có nên dời phần tử qua không
		// ? Tiết kiệm bộ nhớ hay tốc độ ?
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
				if(pNode->prev != NULL && !pNode->prev->isFull()) {
                    if(index == 0) {
                        pNode->prev->add(val);
                        return;
                    }
                    else {
                        int temp = pNode->elements[0];
                        pNode->prev->add(temp);
                        pNode->removeAt(0);
                        pNode->insertAt(index - 1, val);
                        return;
                    }
                }

                int temp = pNode->elements[pNode->numElements - 1];
                pNode->removeAt(pNode->numElements - 1);
                pNode->insertAt(index, val);

                Node* newNode = new Node(nodeSize);
                ++numOfNodes;
                for (int k = pNode->getHalfNodeSize(); k < pNode->numElements; k++) {
                    newNode->add(pNode->elements[k]);
                }
                newNode->add(temp);
                for (int k = pNode->numElements - 1; k >= pNode->getHalfNodeSize(); k--) {
                    pNode->removeAt(k);
                }
                newNode->next = pNode->next;
                pNode->next = newNode;
                newNode->prev = pNode;
                if(newNode->next != NULL)
                    newNode->next->prev = newNode;
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
	if (numOfNodes == 1)
	{
		if (size == 1) {
			head->removeAt(0);
			Node*temp = head;
			delete temp;
			head = tail = NULL;
			numOfNodes--;
			return;
		}
		else {
			head->removeAt(pos);
			return;
		}
	}
	int count = 0;
	for (Node*p = head; p != NULL; p = p->next) {
		for (int i = 0; i < p->numElements; i++) {
			if (count == pos) {
				if (p->numElements > p->getHalfNodeSize()) {
					p->removeAt(i);
					return;
				}
				else {
					if (p == head) {
						if (p->next->numElements > p->next->getHalfNodeSize()) {
							p->removeAt(i);
							p->add(p->next->elements[0]);
							p->next->removeAt(0);
							return;
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->next->getHalfNodeSize(); k++)
								p->add(p->next->elements[k]);
							// delete node p->next after Merger
							for (int k = p->next->getHalfNodeSize() - 1; k >= 0; k--)
								p->next->removeAt(k);
							Node* temp = p->next;
							// Change next only if node to be deleted is NOT the last node 
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							// Change prev only if node to be deleted is NOT the first node
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
					else if (p == tail) {
						if (p->prev->numElements > p->prev->getHalfNodeSize()) {
							p->removeAt(i);
							// l?y ph?n t? cu?i c?a p->prev luu vào x
							int x = p->prev->elements[p->prev->numElements - 1];
							p->insertAt(0, x);
							p->prev->removeAt(p->prev->numElements - 1);
							return;
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->numElements; k++) {
								p->prev->add(p->elements[k]);
							}

							// delete node p after Merger
							for (int k = p->numElements - 1; k >= 0; k--) {
								p->removeAt(k);
							}

							Node* temp = p;
							// Change next only if node to be deleted is NOT the last node
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							// Change prev only if node to be deleted is NOT the first node
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
					else {
						if (p->next->numElements > p->next->getHalfNodeSize()) {
							p->removeAt(i);
							if (p->prev->numElements == p->prev->getHalfNodeSize()) { /*   */
								for (int k = 0; k < p->numElements; k++)
									p->prev->add(p->elements[k]);
								for (int k = p->numElements - 1; k >= 0; k--)
									p->removeAt(k);
								Node* temp = p;

								/* Change next only if node to be deleted is NOT the last node */
								if (temp->next != NULL) {
									temp->next->prev = temp->prev;
								}
								else {
									tail = temp->prev;
								}

								/* Change prev only if node to be deleted is NOT the first node */
								if (temp->prev != NULL) {
									temp->prev->next = temp->next;
								}
								//temp->prev->next = temp->next;
								//temp->next->prev = temp->prev;
								delete temp;
								numOfNodes--;
								return;
							}
							else {
								p->add(p->next->elements[0]);
								p->next->removeAt(0);
								return;
							}
						}
						else {
							p->removeAt(i);
							for (int k = 0; k < p->next->getHalfNodeSize(); k++) {
								p->add(p->next->elements[k]);
							}
							// delete node p->next after Merger
							for (int k = p->next->getHalfNodeSize() - 1; k >= 0; k--) {
								p->next->removeAt(k);
							}
							Node* temp = p->next;
							/* Change next only if node to be deleted is NOT the last node */
							if (temp->next != NULL) {
								temp->next->prev = temp->prev;
							}
							else {
								tail = temp->prev;
							}

							/* Change prev only if node to be deleted is NOT the first node */
							if (temp->prev != NULL) {
								temp->prev->next = temp->next;
							}
							delete temp;
							numOfNodes--;
							return;
						}
					}
				}
			}
			count++;
		}
	}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	int index = 0;
	for (Node*p = head; p != NULL; p = p->next)
		for (int i = 0; i < p->numElements; i++) {
			if (p->elements[i] == val) return index;
			index++;
		}
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	int index = size-1;
	for (Node*p = tail; p != NULL; p = p->prev) 
		for (int i = p->numElements - 1; i >= 0; i--) {
			if (p->elements[i] == val)
				return index;
			index--;
		}
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

