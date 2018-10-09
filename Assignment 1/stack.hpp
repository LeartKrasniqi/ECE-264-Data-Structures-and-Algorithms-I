#include <iostream>
#include <string>
using namespace std;

// Implementation of Stacks using the SimpleList class template


// Inheriting stuff from SimpleList
template <typename Object>
class Stack : public SimpleList<Object>
{
public:										        // Because the functions were virtual in SimpleList, I can implement
	void push(Object data);					// them specifically for the Stack class in this class declaration
	Object pop();
	Stack(string l) : SimpleList<Object>(l){};		// Constructor (Inherits from SimpleList)
};

// Push function
template <typename Object>
void Stack<Object> :: push(Object data)
{
	SimpleList<Object> :: insertStart(data);			// Calls insertStart function from the SimpleList class template
}


// Pop function
template <typename Object>
Object Stack<Object> :: pop()
{
	return SimpleList<Object> :: removeStart();			// Calls removeStart function since the "start" of the 
}														                      // stack is last element pushed onto it.  Therefore, removing 
														                      // from the start is consistent with the LIFO nature
