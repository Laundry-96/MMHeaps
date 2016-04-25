#ifndef MMHEAP_H
#define MMHEAP_H

#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

<typename DataType>
class MMHeap
{
	public:

		/*
		 * MMHeap()
		 *
		 * Constructor for MMHeap
		 */
		MMHeap();

		/*
		 * dump()
		 * 
		 * Spits out all of the information from the heap onto the console
		 *
		 * Preconditions : None
		 * Postconditions: None
		 */
		void dump();

		/*
		 * insert(DataType Obj)
		 * 
		 * Inserts the obj into the heap, and puts it into the proper place
		 *
		 * Preconditions : Obj is able to be compared to other objects of the same DataType
		 * Postconditions: If the heap isn't big enough, it will double the size of it
		 *				   The object is inserted to the proper position
		 */
		void insert(DataType obj);

		/*
		 * getMin()
		 *
		 * Returns the smallest element in the heap (root)
		 * 
		 * Preconditions : None
		 * Postconditions: None
		 */
		DataType getMin();

		 /*
		 * getMax()
		 *
		 * Returns the biggest element in the heap (One of the children from root, if not, then root itself)
		 *
		 * Preconditions : None
		 * Postconditions: None
		 */
		DataType getMax();

		/*
		 * deleteMin()
		 * 
		 * Deletes the smallest element in the heap (root)
		 *
		 * Preconditions : root must have valid data
		 * Postconditions: The smallest element will be removed
		 */
		DataType deleteMin();

		/*
		 * deleteMax()
		 *
		 * Deletes the biggest element in the heap (One of the children from root, if not, then root itself)
		 *
		 * Preconditions : Root must have valid data
		 * Postconditions: The biggest element will be removed
		 */
		DataType deleteMax();


	private:

		/*
		 * perculateUp(int index)
		 * 
		 * Depending on level, check wether the object at heap[index] should be moved up
		 *
		 * Preconditions : Heap has data in it that can be worked with, and the item on index has an even height
		 * Postconditions: Item at index is swapped with the "parent" item. Returns the new index of the item we perculated
		 */
		void perculateUp(int index);

		/*
		 * perculateDown(int index)
		 * 
		 * Moves the current element we're out down to the next "child element"
		 *
		 * Preconditions : Heap has data in it.
		 * Postconditions: Item at index is swapped with the "child" item.
		 */
		void perculateDown(int index);

		/*
		 * perculateMaxUp(int index)
		 * 
		 * If the current index obj is greater than parent obj, switch them
		 *
		 * Preconditions : Heap has data in it that can be worked with, and the item on index has an even height
		 * Postconditions: Item at index is swapped with the "parent" item. Returns the new index of the item we perculated
		 */
		//int perculateMaxUp(int index);

		/*
		 * perculateMinUp(int index)
		 * 
		 * Moves the current element we're on to the "parent element" (two rows above, if possible)
		 *
		 * Preconditions : Heap has data in it, and the item on index has an even height
		 * Postconditions: Item at index is swapped with the "parent" item. Returns the new index of the item we perculated
		 */
		//int perculateMinUp(int index);

		/*
		 * perculateMaxDown(int index)
		 *
		 * Moves the current element we're out down to the next "child element" (two rows down, if possible)
		 *
		 * Preconditions : Heap has data in it, and item on index has an odd height
		 * Postconditions: Item at index is swapped with the "child" item. Returns the new index of the item we perculated
		 */
		//int perculateMaxDown(int index);

		/*
		 * perculateMinDown(int index)
		 *
		 * Moves the current element we're on down to the next "child element" (two rows down, if possible)
		 *
		 * Preconditions : Heap has data in it, and the index has an even height
		 * Postconditions: Item at index is swapped with the "child" item. Returns the new index of the item we perculated
		 */
		 //int perculateMinDown(int index);

		/*
		 * isEmpty()
		 *
		 * If there the root is NULL, it's empty
		 */
		bool isEmpty();

		/*
		 * resize()
		 *
		 * Resizes the array to something bigger
		 *
		 * Preconditions : The vector must be full
		 * Postconditions: The vector is now double the size it was
		 */
		 //void resize();

		int MMHeap<DataType>::getMinTwoGen(int index);
		int MMHeap<DataType>::getMaxTwoGen(int index)
		/*
		 * swap(int indexOne, int indexTwo)
		 *
		 * Swaps the data of two data types
		 * 
		 * Preconditions : The data at the indexes is not NULL
		 * Postconditions: The data at the indexes are swapped
		 */
		void swap(int indexOne, int indexTwo);

		vector<DataType> heap;
		int currentIndex;

};

#endif