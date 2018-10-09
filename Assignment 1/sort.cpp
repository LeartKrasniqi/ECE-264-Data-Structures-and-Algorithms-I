// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// Spring 2018 DSA I Assignment # 2
// Leart Krasniqi
// This program takes in a list with 4 columns
// and sorts the list according to a user input.
// The sorts implemented include Insertion Sort,
// Radix Sort, Bin Sort, and Counting Sort.
// All sorting methods were compared to
// the built in sort() function.
void sortBy1(list<Data *> &l);
void sortBy2(list<Data *> &l);
void sortBy3(list<Data *> &l);
void sortBy4(list<Data *> &l);
bool compareV1(const Data*, const Data*);
bool compareV4(const Data*, const Data*);
Data output[1010000];  // Array for the binSort or countSort
Data array3[1010000];
list<Data *> newList;

// This function allows comparison based on Field 1
bool compareV1(const Data* A, const Data* B)
{
  return A->val1 < B->val1;
}

// This function allows comparison based on Field 4
bool compareV4(const Data* A, const Data* B)
{
  return A->val4 < B->val4;
}

// This function gets the max int in the second column (Sort 2)
unsigned long getMax2(vector<Data *> &v){
    int i = 0;
    unsigned long mx = (v[i])->val2;
    for (i = 0; i < v.size(); i++)
    {
      if ((v[i])->val2 > mx)
          mx = (v[i])->val2;
    }
    return mx;
}

// This function sorts the vector using a Bin Sort
void binSort2(vector<Data *> &v, int exp, int base)
{
  vector<Data *> v2(v.size());
  int count[500000] = {0};
  int z = 0;
  for (z = 0; z < v.size(); z++)
  {
    count[(((v[z])->val2)/exp) % base]++;
  }
  for (int i = 1; i < base; i++)
  {
    count[i] += count[i - 1];
  }
  int n = 1;
  z = v.size();
  z--;
  while (n)
  {
    v2[count[(((v[z])->val2)/exp) % base] - 1] = (v[z]);
    count[ (((v[z])->val2)/exp) % base ]--;
    if(z == 0)
      break;
    z--;
  }
  v.swap(v2);
}

void radixSort2(list<Data *> &l)
{
  int base = 500000;
  vector< Data *> v;
  v.reserve(l.size());
  copy(begin(l), end(l), back_inserter(v));
  unsigned long m  = getMax2(v);
  for (unsigned long exp = 1; m/exp > 0; exp *= base)
    binSort2(v, exp, base);
  list<Data *> newList2(v.begin(), v.end());
  l.swap(newList2);
}


// This function puts the linked list into an array (Sort 3)
void toArray(list<Data *> &l, Data arr[])
{
  int size = l.size();
  list<Data *>::iterator iter = l.begin();
  int n = 0;
  while (iter != l.end())
  {
    arr[n] = (**iter);
    iter++;
    n++;
  }
}
// This function utilizes a Counting Sort (Sort 3)
void countSort(list<Data *> &l, Data arr[])
{
  const int size = l.size();
  int count[95] = {0}, i;
 
  for(i = 0; i < size; i++)
    count[((arr[i].val3)-33) % 95]++;   // Subtract 33 so least significant is !
 
  for (i = 1; i <= 95; i++)
    count[i] += count[i-1];
 
  for (i = size -1; i >= 0; i--)
  {
     output[count[((arr[i].val3)-33) % 95]-1] = arr[i];
     count[((arr[i].val3)-33) % 95]--;
  }
 
  for (i = 0; i < size; ++i)
    arr[i] = output[i];
}


// This function gets the maximum string (Sort 4)
string getMax4(vector<Data *> &v)
{
  string max = v[0]->val4;
  for (int i = 1; i < v.size(); i++)
  {
    if (v[i]->val4 > max)
      max = v[i]->val4;
  }
  return max;
}


// This function uses a Bin Sort to partially sort strings (Sort 4)
void binSort4(vector<Data *> &v, unsigned long exp, int base)
{
  vector<Data *> v4(v.size());
  int count[1000] = {0};
  int z = 0;
  for (z = 0; z < v.size(); z++)
  {
    int temp = (v[z]->val4[0] * 1000000) + (v[z]->val4[1] * 1000) + (v[z]->val4[2] * 1);
    count[(temp/exp) % base]++;
  }
  for (int i = 1; i < base; i++)
    count[i] += count[i - 1];

  int n = 1;
  z = v.size() - 1;
  while (n)
  {
    int temp = (v[z]->val4[0] * 1000000) + (v[z]->val4[1] * 1000) + (v[z]->val4[2] * 1);
    v4[count[(temp/exp) % base] - 1] = (v[z]);
    count[(temp/exp) % base]--;
    if (z == 0)
      break;
    z--;
  }
  v.swap(v4);
}


// This function calls the appropriate sorting methods for each field 
void sortDataList(list<Data *> &l, int field) 
{

  if (field == 1) 
  {
    sortBy1(l);
    return;
  }

  else if (field == 2) 
  {
    sortBy2(l);
    return;
  }

  else if (field == 3) 
  {
    sortBy3(l);
    return;
  }
  else if (field == 4) 
  
  {
    sortBy4(l);
    return;
  }
}

// This function utilizes InsertionSort to sort by the first data field
void sortBy1(list<Data *> &l)
{
  for (list<Data *>::iterator iter = l.begin()++; iter != l.end(); iter++) 
  {
    list<Data *>::iterator tempit1 = iter;
    list<Data *>::iterator tempit2 = tempit1;
    tempit2--;
    for(tempit1 = iter; tempit1 != l.begin() && compareV1(*tempit1, *tempit2); tempit1--, tempit2--)
    {
      iter_swap(tempit1,tempit2);
    }
  }
}

// This function utilizes Radix Sort to sort by the second data field 
void sortBy2(list<Data *> &l)
{
  radixSort2(l);
}

// This function utilizes Counting Sort to sort by the third data field
void sortBy3(list<Data *> &l)
{
  toArray(l, array3);
  countSort(l, array3);
  for(register int z; z < l.size(); z++)
  {
    newList.push_back(&array3[z]);
  }
  l.swap(newList);
}

// This function utilizes both a Radix Sort and an Insertion Sort to sort by the fourth data field
void sortBy4(list<Data *> &l)
{
  int base = 1000;
  vector< Data *> v;
  v.reserve(l.size());
  copy(begin(l), end(l), back_inserter(v));
  string m = getMax4(v);
  unsigned int mx = (m[0] * 1000000) + (m[1] * 1000) + (m[2] * 1);
  for (unsigned long exp = 1; mx/exp > 0; exp *= 1000)
    binSort4(v, exp, base);
  list<Data *> newList4(v.begin() , v.end());
  l.swap(newList4);
  // The next part does the insertion sort
  for (list<Data *>::iterator iter = l.begin()++; iter != l.end(); iter++) 
  {
    list<Data *>::iterator tempit1 = iter;
    list<Data *>::iterator tempit2 = tempit1;
    tempit2--;
    for(tempit1 = iter; tempit1 != l.begin() && compareV4(*tempit1, *tempit2); tempit1--, tempit2--)
    {
      iter_swap(tempit1,tempit2);
    }
  }
}
