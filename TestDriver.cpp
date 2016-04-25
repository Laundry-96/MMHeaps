#include "MMheap.cpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	MMheap<int> theHeap;

	cout << "Insert 1, 2, 3, 4, 5" << endl;

	theHeap.insert(1);
	theHeap.insert(2);
	theHeap.insert(3);
	theHeap.insert(4);
	theHeap.insert(5);
	theHeap.insert(99);

	theHeap.dump();
}

