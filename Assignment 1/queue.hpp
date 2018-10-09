#include <iostream>
#include <string>
using namespace std;

// Implementation of Queues using the SimpleList class template


// Inheriting stuff from SimpleList 
template <typename Object>
class Queue : public SimpleList<Object>
{
public:							// Because the functions were virtual in SimpleList, I can implement
	void push(Object data);					// them specifically for the Queue class in this class declaration
	Object pop();
	Queue(string l) : SimpleList<Object>(l){};		// Constructor (inherits from SimpleList)
};


// Push function
template <typename Object>
void Queue<Object> :: push(Object data)
{
	SimpleList<Object> :: insertEnd(data);			// Unlike stacks, queues have data added to the end
}


// Pop function
template <typename Object>
Object Queue<Object> :: pop()
{
	return SimpleList<Object> :: removeStart();			// Identical to the stack implementation of pop() but the 
}									// difference is that the "start" of the queue is actually the 
									// first element pushed onto the queue, so removing it is 
									// consistent with the FIFO nature 
