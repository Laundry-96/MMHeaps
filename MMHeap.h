#ifndef MMHEAP_H
#define MMHEAP_H

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
		 * Dump()
		 * 
		 * Spits out all of the information from the heap onto the console
		 *
		 * Preconditions : None
		 * Postconditions: None
		 */
		void Dump();

		/*
		 * Insert(DataType Obj)
		 * 
		 * Inserts the obj into the heap, and puts it into the proper place
		 *
		 * Preconditions : Obj is able to be compared to other objects of the same DataType
		 * Postconditions: If the heap isn't big enough, it will double the size of it
		 *				   The object is inserted to the proper position
		 */
		void Insert(DataType obj);

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
		 * deleteMax()
		 *
		 * Deletes the biggest element in the heap (One of the children from root, if not, then root itself)
		 *
		 * Preconditions : Root must have valid data
		 * Postconditions: The biggest element will be removed
		 */
		DataType deleteMax();

		/*
		 * deleteMin()
		 * 
		 * Deletes the smallest element in the heap (root)
		 *
		 * Preconditions : root must have valid data
		 * Postconditions: The smallest element will be removed
		 */
		DataType deleteMin();

	private:

		/*
		 * PeculateMaxUp(int index)
		 * 
		 * Moves the element we're currently at to "parent" element (two rows above), if possible
		 *
		 * Preconditions : Heap has data in it that can be worked with, and the item on index has an even height
		 * Postconditions: Item at index is swapped with the "parent" item. Returns the new index of the item we perculated
		 */
		int PerculateMaxUp(int index);

		/*
		 * PerculateMinUp(int index)
		 * 
		 * Moves the current element we're on to the "parent element" (two rows above, if possible)
		 *
		 * Preconditions : Heap has data in it, and the item on index has an odd height
		 * Postconditions: Item at index is swapped with the "parent" item. Returns the new index of the item we perculated
		 */
		int PerculateMinUp(int index);

		/*
		 * PerculateMaxDown(int index)
		 */

		/*
		 * PerculateMinDown(int index)
		 */

		/*
		 * isEmpty()
		 */

		/*
		 * resize()
		 *
		 * Resizes the array to something bigger
		 *
		 * Preconditions : The vector must be full
		 * Postconditions: The vector is now double the size it was
		 */

		/*
		 * switch(int index)
		 */


		 vector<DataType> heap;
		 int currentIndex;

};

#endif