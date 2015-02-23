#pragma once

template<class DataType> class NodePointer;
template<class DataType> class LinkedListPointer;


template <class DataType>
class NodePointer
{
	//We are giving "permissions" to the LinkedListPointer class to access to the private members of the NodePointer class. 
	//Thus, the Linked list methods are able to access to data and next attributes directly
	//In this case it has sense give LinkedListPointer "full" permissions because the NodePointer class has only sense for the LinkedListPointer class
	friend class LinkedListPointer<DataType>;	
	DataType data;
	NodePointer<DataType> * next;
public:

	NodePointer(DataType p) {
		this->data = p;
		this->next = 0;
	}

	NodePointer(const NodePointer & n) {
		this->data = n.data;
		this->next = n.next;
	}

	~NodePointer() {	
		delete data;
	}	
};


/*
* This class represents a linked list, which is a linear data structure characterized by its capabilities of adding and removing information in a fast way
*/
template <class DataType>
class LinkedListPointer {
	NodePointer<DataType> * head;
	NodePointer<DataType> * iterator;
	int numElements;	
public:	
	/*
	* Creates an empty LinkedListPointer
	* @param type is the type of the template. 0 means that is a pointer. Otherwise it is equal to 1
	*/
	LinkedListPointer() {
		head = 0;
		numElements = 0;	
		iterator = 0;
	}

	/*
	* Destructor. It goes through the linked list while it deletes each one of the nodes
	*/
	~LinkedListPointer() {
		//Destroy a LinkedListPointer means removing all its elements
		for (int i = 0; i < numElements; i++) {
			removeCharacter();
		}
	}

	int getSize(){
		return numElements;
	}

	/*
	* Add a person at the beginning of the LinkedListPointer. It throws an exception if system is not able to allocate memory
	* @param p is the person object to add
	*/
	void addCharacter(DataType p) {
		NodePointer<DataType> * n;
		//Create a new node that will contain the object to add
		n = new NodePointer<DataType>(p);
		if (n == 0) {
			throw exception("System is not able to allocate memory for the new node");
		}
		//The new node will point to the first element pointed by the head pointer through its n->next pointer. It head pointed to null, the next node of n will point to null which is ok
		n->next = head;
		//Finally, the head pointer points to the new element
		head = n;
		numElements++;
	}

	/*
	* Remove the first person from the LinkedListPointer
	* @throw an exception if the LinkedListPointer was empty
	*/
	void removeCharacter() {
		NodePointer<DataType> * currentElement;

		if (numElements == 0) {
			throw exception("System cannot delete the first position because the LinkedListPointer is empty");
		}

		//Head will point to the next element. It doesn't matter if there was only one element, head will point to null and numElements will be equal to 0. Thus, everything will be ok
		currentElement = head;
		head = currentElement->next;		

		delete currentElement;

		//Restart the iterator
		iterator = head;

		numElements--;
	}

	/*
	* Remove the person from the LinkedListPointer position
	* @throw an exception if the LinkedListPointer was empty
	* @param p is the position person object to remove
	*/
	void removeCharacterfromPosition(int position) {
		NodePointer<DataType> * currentElement;
		NodePointer<DataType> * deleteElement;
		if (numElements == 0) {
			throw exception("System cannot delete a position from an empty LinkedList");
		}

		if (position >= numElements) {
			position = 0;
		}

		if (position == 0) {
			//Head will point to the next element. It doesn't matter if there was only one element, head will point to null and numElements will be equal to 0. Thus, everything will be ok
			currentElement = head;
			head = currentElement->next;
			delete currentElement;
		}
		else {
			//We go through the data structure counting the elements-1 because we want to stop the search in previous element 
			currentElement = head;
			for (int i = 0; i < position - 1; i++) {
				currentElement = currentElement->next;

			}
			deleteElement = currentElement->next;
			currentElement->next = currentElement->next->next;
			delete deleteElement;
		}
		//Restart the iterator
		iterator = head;
		numElements--;
	}
	/*
	* Set the iterator in the first position
	*/
	void restartIterator() {
		iterator = head;
	}

	/*
	* Move forward to the next position
	* @return 1 if the iterator has arrived to the end. Otherwise, it returns 0
	*/
	int nextNode() {
		int end = 0;		

		if (iterator != 0) {
			iterator = iterator->next;
			if (iterator == 0) {
				end = 1;
			}
		}
		else {
			end = 1;
		}
		return end;
	}

	/*
	* Return the current object pointed by the iterator
	* @return the current object of the linked list
	*/
	DataType getCurrentElement() {
		return iterator->data;
	}

	/*
	* Get a specified Character from the LinkedListPointer
	* @param position is where the new object is stored
	* @return person is the specified person to return
	* @throw an exception if the specified position doesn't exist
	*/
	DataType LinkedListPointer::getCharacter(int position) {
		if (position >= numElements) {
			throw exception("The specified position doesn't exist");
		}

		NodePointer<DataType> * currentElement;
		//We go through the data structure counting the elements-1 because we want to stop the search in previous element 
		currentElement = head;
		for (int i = 0; i <= position - 1; i++) {
			currentElement = currentElement->next;

		}

		return currentElement->data;
	}

	 /**
	* Output operator is overloaded to allow you to use "cout<<l;"
	* @param os is the output operator
	* @param l is the object that will be used inside the function
	*/
	friend ostream& operator<<(ostream& os, LinkedListPointer & l)
	{
		for (int i = 0; i < l.numElements; i++) {		
				os << "Character " << i << ":" << *l.getCharacter(i) << endl;
		}
		return os;
	}
};

