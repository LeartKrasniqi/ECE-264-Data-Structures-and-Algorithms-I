#include <iostream>
#include <string>
using namespace std;


// SimpleList Class Template

template <typename Object>
class SimpleList
{
private:

	// private nested class: Node
	class Node
	{
	public:
		Object data;
		Node *next;								// Singly Linked List -- Pointer to next node only
		Node(Object d, Node *n)					// Node Constructor 
			: data(d), next(n) {}
	};

	string listname;
	int listsize;
	Node *head;				// Pointers to the head and tail of list
	Node *tail;

protected:

	// functions to insert and remove nodes
	void insertStart(Object data);
	void insertEnd(Object data);
	Object removeStart();					// This function should return what was removed

public:

	// push and pop functions (purely virtual)
	virtual void push(Object data) = 0;
	virtual Object pop() = 0;

	// functions that return name and size of list
	string myName()
	{
		return listname;
	}

	int mySize()
	{
		return listsize;
	}

	SimpleList(string l)				// SimpleList constructor that initializes name, size, and head/tail nodes
	{
		listname = l;
		listsize = 0;
		head = NULL;
		tail = NULL;
	}

};


// Implementation of insertStart which inserts node at the front of the list
template <typename Object>
void SimpleList<Object> :: insertStart(Object data)
{
	Node *temp = new Node(data, head);
	if (mySize() == 0)					// If list is empty, the inserted data is both the head and the tail
	{
		head = temp;
		tail = temp;
		listsize++;
	} 
	else 								// If list is not empty, the inserted data becomes the new head
	{													
		head = temp;					
		listsize++;
	}

};


// Implementation of insertEnd which inserts node at the end of the list
template <typename Object>
void SimpleList<Object> :: insertEnd(Object data)
{
	Node *temp = new Node(data, NULL);
	if (mySize() == 0)					// If list is empty, the inserted data is both the head and the tail
	{
		head = temp;
		tail = temp;
		listsize++;
	}
	else								// If list is not empty, the initial tail becomes the previous
	{									// element and the newly inserted data becomes the tail of the list
		tail->next = temp;	
		tail = temp;			
		listsize++;
	}
};

// Implementation of removeStart which removes a node from the beginning of the list
template <typename Object>
Object SimpleList<Object> :: removeStart()
{
	Node *temp = head->next;			// A temporary pointer points to the second element in the list
	Object data = head->data;			// and the variable 'data' stores the value of the head of the list.
	delete head;						// The head is deleted, the size is decreased, and the second element 
	listsize--;								// is now made the new head of the list.  The value in 'data' is returned.
	head =  temp;
	return data;
};
