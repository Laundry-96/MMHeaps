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
	theHeap.insert(6);
	theHeap.insert(7);
	theHeap.insert(8);
	theHeap.insert(10);
	theHeap.insert(0);
	theHeap.insert(45);
	theHeap.insert(222);
	theHeap.insert(24);
	theHeap.insert(7);
	theHeap.insert(7);
	/*theHeap.insert(9);
	theHeap.insert(10);
	theHeap.insert(11);
	theHeap.insert(12);
	theHeap.insert(13);
		theHeap.insert(14);	theHeap.insert(15);	theHeap.insert(16);	theHeap.insert(17);	
*/
	theHeap.dump();

		theHeap.deleteMin();

		theHeap.dump();
}

