#include "MMheap.h"

template <typename DataType>
MMheap<DataType>::MMheap()
{
	currentIndex = 0;
}

template <typename DataType>
void MMheap<DataType>::dump()
{
	cout << "---------------------------------------" << endl;
	cout << "Size = " << size() << endl;
	cout << "Minimum = " << getMin() << endl;
	cout << "Maximum = " << getMax() << endl;

	int height = log(currentIndex - 1) / log(2);

	if(height % 2 == 0)
	{
		cout << "Last level is even" << endl;
	}

	else
	{
		cout << "Last level is odd" << endl;
	}

	cout << "--- heap data items ---" << endl;

	for(unsigned int i = 0; i < heap.size(); i++)
	{
		cout << "H[" << i << "] = " << heap[i] << endl;
	}

	cout << "---------------------------------------" << endl;

}

template <typename DataType>
DataType MMheap<DataType>::getMin()
{
	if(currentIndex != 0)
	{
		return heap[0];
	}

	return NULL;
}

template <typename DataType>
DataType MMheap<DataType>::getMax()
{
	if(currentIndex == 1)
	{
		return heap[0];
	}

	else if(currentIndex == 2)
	{
		return heap[1];
	}

	else
	{
		return max(heap[1], heap[2]);
	}
}

template <typename DataType>
void MMheap<DataType>::insert(DataType obj)
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
DataType MMheap<DataType>::deleteMax();
{
	
}


template <typename DataType>
void MMheap<DataType>::perculateUp(int index)
{
	int height = log(index) / log(2);
	int grandparent = index >> 2;

	cout << "Currently at height " << height << endl;

	//If we are at root, or children of root, return
	//(because we can't go any higher)
	if(index < 4)
		return;

	//If height is even
	if(height % 2 == 0)
	{

		cout << "Height is even" << endl;

		cout << "Evaluating: " << heap[index] << " < " << heap[grandparent] << endl;

		//Check if we can perculate up
		if(heap[grandparent] < heap[index])
		{

			cout << "Swapping" << endl;

			//Swap them
			swap(grandparent, index);

			//Our index is now parent
			index = grandparent;

			//See if we can perculate up again
			perculateUp(index);
		}

		//Else: We can't perculateUp so continue this method to exit
	}

	//Height is odd
	else
	{
		cout << "Height is odd" << endl;
		//Check if we perculate up

		cout << "Evaluating: " << heap[index] << " < " << heap[grandparent] << endl;

		if(heap[index] < heap[grandparent])
		{
			cout << "Swapping" << endl;
			//Swap them
			swap(grandparent, index);

			//Our index is now parent
			index = grandparent;

			//See if we can perculate up again
			perculateUp(index);
		}

		//Else: We can't perculateUp so we continue this method to exit
	}
}

template <typename DataType>
void MMheap<DataType>::perculateDown(int index)
{
	int grandchildren = index << 2;
	int height = log(index) / log(2);

	//We are on an even height
	if(height % 2 == 0)
	{
		//We have all of our grandchildren
		if((grandchildren + 4) < currentIndex)
		{
			//Get the smallest one
			int smallestGrandchild = grandchildren;


			for(int i = grandchildren + 1; i < grandchildren + 4; i++)
			{
				if(heap[smallestGrandchild] > heap[i])
					smallestGrandchild = i;
			}

			//Base case: We're in the right position so check parent, and return
			if(heap[index] < heap[smallestGrandchild])
			{
				int parent = index >> 1;

				//We should be less than parent
				if(heap[index] > heap[parent])
				{
					//We're not less than parent, so swap
					swap(index, parent);
				}

				//We're good
				return;
			}

			//Swap them because grandchild is smaller than grandparent (not ok)
			if(heap[index] > heap[smallestGrandchild])
			{
				swap(index, smallestGrandchild);
			
				index = smallestGrandchild;

				perculateDown(index);
			}

		}

		//Check children and grandchildren
		else
		{
			//Get the minimum data from the next two generations
			//int minChildIndex = getMinChild(index);
			//int minGrandchildIndex = getMinGrandchild(index);

			int absMin = getMinTwoGen(index);

			//int absMin = heap[minChildIndex] > heap[minGrandchildIndex] ? minGrandchildIndex : minChildIndex;

			//If we're smaller than the min (base case)
			if(heap[index] < heap[absMin])
			{
				//We're good and we can return
				return;
			}



			//If we're bigger than min, that's not good.
			else
			{
				swap(index, absMin);

				index = absMin;
			}

			int parent = index >> 1;

			if(heap[index] < heap[parent])
			{
				swap(index, parent);
			}
		}
	}

	else
	{
		//We have all of our grandchildren
		if((grandchildren + 4) < currentIndex)
		{
			//Get the biggest one
			int biggestGrandchild = grandchildren;


			for(int i = grandchildren + 1; i < grandchildren + 4; i++)
			{
				if(heap[biggestGrandchild] < heap[i])
					biggestGrandchild = i;
			}

			//Base case: We're in the right position so check parent, and return
			if(heap[index] > heap[biggestGrandchild])
			{
				int parent = index >> 1;

				//We should be less than parent
				if(heap[index] > heap[parent])
				{
					//We're not less than parent, so swap
					swap(index, parent);
				}

				//We're good
				return;
			}

			//Swap them because grandchild is smaller than grandparent (not ok)
			if(heap[index] < heap[biggestGrandchild])
			{
				swap(index, biggestGrandchild);
			
				index = biggestGrandchild;

				perculateDown(index);
			}

		}

		//Check children and grandchildren
		else
		{
			//Get the minimum data from the next two generations
			//int maxChildIndex = getMinChild(index);
			//int maxGrandchildIndex = getMinGrandchild(index);

			int absMax = getMaxTwoGen(index);

			//int absMin = heap[minChildIndex] > heap[minGrandchildIndex] ? minGrandchildIndex : minChildIndex;

			//If we're bigger than the min (base case)
			if(heap[index] > heap[absMax])
			{
				//We're good and we can return
				return;
			}



			//If we're smaller than min, that's not good.
			else
			{
				swap(index, absMax);

				index = absMax;
			}

			int parent = index >> 1;

			if(heap[index] > heap[parent])
			{
				swap(index, parent);
			}
		}

	}
}

template <typename DataType>
int MMheap<DataType>::size()
{
	//We can just return currentIndex because
	//even though it holds the next index we should
	//use, it displays how many are current in there because
	//it starts at 0
	return currentIndex;
}

template <typename DataType>
void MMheap<DataType>::swap(int indexOne, int indexTwo)
{
	DataType temp = heap[indexOne];
	heap[indexOne] = heap[indexTwo];
	heap[indexTwo] = temp;
}

template <typename DataType>
int MMheap<DataType>::getMaxTwoGen(int index)
{
	//We're going to have max 2 children and max 4 grandchildren 
	//We won't fill this because this method gets called when 
	//We don't have full grandchildren
	vector<DataType> descendents;
	vector<int> 	 indexes;

	int children = index << 1;
	int grandchild = index << 2;

	//For both children
	for(int i = 0; i < 2; i++)
	{
		//If valid index
		if((children + i) < currentIndex)
		{
			descendents.push_back(heap[children + i]);
			indexes.push_back(children + i);
		}

		//Else: invalid index, do nothing
	}

	//For all grandchildren
	for(int i = 0; i < 4; i++)
	{
		if((grandchild + i) < currentIndex)
		{
			descendents.push_back(heap[grandchild + i]);
			indexes.push_back(grandchild + i);
		}

		//Else: invalid index, do nothing
	}

	if(descendents.size() != 0)
	{
		DataType max = descendents[0];
		int maxIndex = 0;

		for(unsigned int i = 1; i < descendents.size(); i++)
		{
			if(max < descendents[i])
			{
				max = descendents[i];
				maxIndex = i;
			}
		}

		return indexes[maxIndex];
	}

	//Idk what to do. Just return index I guess.
	return index;
}

/*template <typename DataType>
int MMheap<DataType>::getMinChild(int index)
{
	//We're going to have max 2 children and max 4 grandchildren 
	//We won't fill this because this method gets called when 
	//We don't have full grandchildren
	vector<DataType> descendents;
	vector<int> 	 indexes;

	int children = index << 1;

	//For both children
	for(int i = 0; i < 2; i++)
	{
		//If valid index
		if((children + i) < currentIndex)
		{
			descendents.push_back(heap[children + i]);
			indexes.push_back(children + i);
		}

		//Else: invalid index, do nothing
	}

	if(children.size() == 0)
		return index;
	else if(children.size() == 1)
		return indexes[0];
	return children[0] > children[1] ? indexes[1] : indexes[0];
}

template <typename DataType>
int MMheap<DataType>::getMinGrandchild(int index)
{
	vector<DataType> descendents;
	vector<int>		 indexes;

	int grandchild = index << 2;

	//For all grandchildren
	for(int i = 0; i < 4; i++)
	{
		if((grandchild + i) < currentIndex)
		{
			descendents.push_back(heap[grandchild + i]);
			indexes.push_back(grandchild + i);
		}

		//Else: invalid index, do nothing
	}

	if(descendents.size() != 0)
	{
		DataType min = descendents[0];
		int maxIndex = 0;

		for(unsigned int i = 1; i < descendents.size(); i++)
		{
			if(min > descendents[i])
			{
				max = descendents[i];
				maxIndex = i;
			}
		}

		return indexes[maxIndex];
	}

	return index;
}
*/

template <typename DataType>
int MMheap<DataType>::getMinTwoGen(int index)
{
	//We're going to have max 2 children and max 4 grandchildren 
	//We won't fill this because this method gets called when 
	//We don't have full grandchildren
	vector<DataType> descendents;
	vector<int> 	 indexes;

	int children = index << 1;
	int grandchild = index << 2;

	//For both children
	for(int i = 0; i < 2; i++)
	{
		//If valid index
		if((children + i) < currentIndex)
		{
			descendents.push_back(heap[children + i]);
			indexes.push_back(children + i);
		}

		//Else: invalid index, do nothing
	}

	//For all grandchildren
	for(int i = 0; i < 4; i++)
	{
		if((grandchild + i) < currentIndex)
		{
			descendents.push_back(heap[grandchild + i]);
			indexes.push_back(grandchild + i);
		}

		//Else: invalid index, do nothing
	}

	if(descendents.size() != 0)
	{
		DataType min = descendents[0];
		int maxIndex = 0;

		for(unsigned int i = 1; i < descendents.size(); i++)
		{
			if(min > descendents[i])
			{
				max = descendents[i];
				maxIndex = i;
			}
		}

		return indexes[maxIndex];
	}

	//Idk what to do. Just return index I guess.
	return index;
}

