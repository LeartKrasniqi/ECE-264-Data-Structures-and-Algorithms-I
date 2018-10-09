// Leart Krasniqi
// Data Structure and Algorithms I -- Spring 2018
// Prof. Sable
// Programming Assingmnet # 1

/* 
This program is designed to implement stacks and queues using a class template names SimpleList.
The SimpleList template models a singly linked list with push() and pop() capabilities.  The user 
is asked for the name of a text file to be parsed and the desired name of an output file to which 
the program will send its output.  The output of the program describes all of the operations 
carried out, in a very specific manner.
*/


#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>

// My own header files that contain templates and functions
#include "SimpleList.hpp"				
#include "Stack.hpp"
#include "Queue.hpp"

using namespace std;


list<SimpleList<int> *> listSLi;		// All integer stacks and queues
list<SimpleList<double> *> listSLd;		// All double stacks and queues
list<SimpleList<string> *> listSLs;		// All string stacks and queues


// Function to search through the list of SimpleLists.  If the name we are searching for exists, we return the name.
// If not, we return NULL.  This allows us to issue warnings if the user wants to create something that already exists.
template<typename Object>
SimpleList<Object> * search(list<SimpleList<Object> *> & theList , string listname)
{
	// Use an iterator to access the different SimpleLists 
	for (typename list<SimpleList<Object> * >::iterator itr = theList.begin(); itr != theList.end(); ++itr)
	{
		if ((*itr)->myName() == listname)		// Checks if current SimpleList matches name of list we are trying to find
		{
			return *itr;
		}
	}

	return NULL;
}

// Function that goes through each line and performs certain tasks, depending on the input.
// Outputs to a file
void processLine(string word1, string word2, string word3, ofstream & file)
{
	if (word1 == "create")
	{
		if (word2.substr(0,1) == "i")		// Checks if first letter of word2 is i (integer)
		{
			if (search(listSLi, word2) != NULL) 	// Checks if name of list already exists
			{
				file << "ERROR: This name already exists!" << endl;
			}
			else if (word3 == "stack")		// Want to create a stack
			{
				SimpleList<int> *pSLi;				// Implementation taken from notes
				pSLi = new Stack<int>(word2);
				listSLi.push_front(pSLi);
			}
			else if (word3 == "queue")		// Want to create a queue
			{
				SimpleList<int> *pSLi;
				pSLi = new Queue<int>(word2);
				listSLi.push_front(pSLi);
			}
		}
		else if (word2.substr(0,1) == "d")		// Checks if first letter of word2 is d (double)
		{
			if (search(listSLd, word2) != NULL)		// Once again, checks if name of list already exists
			{
				file << "ERROR: This name already exists!" << endl;
			}
			else if (word3 == "stack")
			{
				SimpleList<double> *pSLd;
				pSLd = new Stack<double>(word2);
				listSLd.push_front(pSLd);
			}
			else if (word3 == "queue")
			{
				SimpleList<double> *pSLd;
				pSLd = new Queue<double>(word2);
				listSLd.push_front(pSLd);
			}
		}
		else if (word2.substr(0,1) == "s")
		{
			if (search(listSLs, word2) != NULL)		
			{
				file << "ERROR: This name already exists!" << endl;
			}
			else if (word3 == "stack")
			{
				SimpleList<string> *pSLs;
				pSLs = new Stack<string>(word2);
				listSLs.push_front(pSLs);
			}
			else if (word3 == "queue")
			{
				SimpleList<string> *pSLs;
				pSLs = new Queue<string>(word2);
				listSLs.push_front(pSLs);
			}
		}
	}
	else if (word1 == "push")
	{
		if (word2.substr(0,1) == "i")
		{
			if (search(listSLi, word2) == NULL)				// Checks if name exists. If it does not, returns error
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else
			{
				search(listSLi, word2) -> push(stoi(word3));	// The int value of word3 is pushed onto the stack/queue
			}
		}
		else if (word2.substr(0,1) == "d")
		{
			if (search(listSLd, word2) == NULL)
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else
			{
				search(listSLd, word2) -> push(stod(word3));
			}
		}
		else if (word2.substr(0,1) == "s")
		{
			if (search(listSLs, word2) == NULL)
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else
			{
				search(listSLs, word2) -> push(word3);
			}
		}
	}
	else if (word1 == "pop")			// Need to make sure the element exists and that the stack/queue isn't empty
	{
		if (word2.substr(0,1) == "i")
		{
			if (search(listSLi, word2) == NULL)		// Checks to see if there exists a SimpleList with that name
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else if (search(listSLi, word2) -> mySize() == 0)	// Checks to see if the SimpleList has any elements
			{
				file << "ERROR: This list is empty!" << endl;
			}
			else 	// If the SimpleList exists and is nonempty, we pop an int from the list and print it to the file
			{
				file << "Value popped: " << search(listSLi, word2) -> pop() << endl;
			}
		}
		else if (word2.substr(0,1) == "d")
		{
			if (search(listSLd, word2) == NULL)		
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else if (search(listSLd, word2) -> mySize() == 0)	
			{
				file << "ERROR: This list is empty!" << endl;
			}
			else 	// If the SimpleList exists and is nonempty, we pop a double from the list and print it to the file
			{
				file << "Value popped: " << search(listSLd, word2) -> pop() << endl;
			}
		}
		else if (word2.substr(0,1) == "s")
		{
			if (search(listSLs, word2) == NULL)		
			{
				file << "ERROR: This name does not exist!" << endl;
			}
			else if (search(listSLs, word2) -> mySize() == 0)	
			{
				file << "ERROR: This list is empty!" << endl;
			}
			else 	// If the SimpleList exists and is nonempty, we pop a string from the list and print it to the file
			{
				file << "Value popped: " << search(listSLs, word2) -> pop() << endl;
			}
		}
	}
}


int main()
{
	string fin, fout, line, w1, w2, w3;			// Parameters for functions as well as file I/O

	cout << "Enter input file name: ";
	cin >> fin;

	cout << "Enter output file name: ";
	cin >> fout;

	ifstream input(fin.c_str());			// Reading from txtfile, implementation taken from notes
	ofstream output(fout.c_str());			// Writing to txtfile, implementation taken from notes

	if (input.is_open())		// Checks to see if file is open
	{
		while (getline(input, line))	// Loop through file line by line, stored info in variable "line"
		{
			istringstream iss(line);	// istringstream reads up until whitespace -- allows to split up command
			iss >> w1 >> w2 >> w3;
			output << "PROCESSING COMMAND: " << line << endl;
			processLine(w1, w2, w3, output);	// Sends the three words to the processLine function defined above 
		}
	}
}
