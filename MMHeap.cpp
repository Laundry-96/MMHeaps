#include "MMHeap.h"

template <typename DataType>
MMHeap<DataType>::MMHeap()
{
	currentIndex = 0;
}

template <typename DataType>
DataType MMHeap<DataType>::getMin()
{
	if(currentIndex != 0)
	{
		return heap[0];
	}

	return NULL;
}

template <typename DataType>
DataType MMHeap<DataType>::getMax()
{
	if(currentIndex == 1)
	{
		return heap[0];
	}

	else if(currentIndex == 2)
	{
		return heap[1];
	}

	else if(currentIndex == 3)
	{
		return max(heap[1], heap[2]);
	}

	return NULL;
}

template <typename DataType>
MMHeap<DataType>::insert(DataType obj)
{
	//If we're at root
	if(currentIndex == 0)
	{
		//We only need to set root, and that's it
		heap.push_back(obj);
	}

	else
	{
		//Insert the object
		heap.push_back(obj);

		//Now perculate the object up
		perculateUp(currentIndex);
	}

	currentIndex++;
}

template <typename DataType>
void MMHeap<DataType>::perculateUp(int index)
{
	//If we are at root (because we don't want to do anything)
	if(index == 0)
		return;

	int height = log(index) / log(2);
	int parent = index >> 1;

	//If height is even
	if(height % 2 == 0)
	{
		//Check if we can perculate up
		if(heap[parent] < heap[index])
		{
			//Swap them
			swap(parent, index);

			//Our index is now parent
			index = parent;

			//See if we can perculate up again
			perculateUp(index);
		}

		//Else: We can't perculateUp so continue this method to exit
	}

	//Height is odd
	else
	{
		//Check if we perculate up
		if(heap[index] < heap[parent])
		{
			//Swap them
			swap(parent, index);

			//Our index is now parent
			index = parent;

			//See if we can perculate up again
			perculateUp(index);
		}

		//Else: We can't perculateUp so we continue this method to exit
	}
}

template <typename DataType>
void MMHeap<DataType>::perculateDown(int index)
{
	int leftChild = index << 1;
	int rightChild = (index << 1) + 1;

	int height = log(index) / log(2);


	//If our children are not instantiated, we are at a leaf
	if (leftChild >= currentIndex)
	{
		return;
	}

	//We are on an even height
	if(height % 2 == 0)
	{
		//If only the leftChild is viable,  go left child
		if(leftChild < currentIndex && rightChild == currentIndex)
		{
			//If 
			if()
		}
	}
}

template <typename DataType>
int MMHeap<DataType>::size()
{
	//We can just return currentIndex because
	//even though it holds the next index we should
	//use, it displays how many are current in there because
	//it starts at 0
	return currentIndex;
}

template <typename DataType>
void MMHeap<DataType>::swap(int indexOne, int indexTwo)
{
	DataType temp = heap[indexOne];
	heap[indexOne] = heap[indexTwo];
	heap[indexTwo] = temp;
}

