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
DataType MMheap<DataType>::deleteMin()
{
	DataType toRet = heap[0];

	//If we only have one element
	if(heap.size() == 1)
	{
		//Heap now empty
		currentIndex--;
		heap.pop_back();
	}

	else
	{
		heap[0] = heap[currentIndex - 1];
		currentIndex--;
		heap.pop_back();
		perculateDown(0);
	}

	return toRet;
}

template <typename DataType>
DataType MMheap<DataType>::deleteMax()
{
	DataType toRet;

	//only one element in
	if(currentIndex == 1)
	{
		toRet = heap[0];
		heap.pop_back();
		currentIndex--;
	}

	//Get the second element
	else if(currentIndex == 2)
	{
		toRet = heap[1];
		heap.pop_back();
		currentIndex--;
	}

	else if(currentIndex == 3)
	{
		toRet = max(heap[1], heap[2]);

		//If biggest is the last thing in the heap, don't worry about it
		if(toRet == heap[2])
		{
			heap.pop_back();
			currentIndex--;
		}

		//toRet = heap[1]
		else
		{
			heap[1] = heap[2];
			heap.pop_back();
			currentIndex--;
		}
	}		

	//Deal with perculate down here
	else
	{
		toRet = max(heap[1], heap[2]);

		if(toRet == heap[1])
		{
			heap[1] = heap[currentIndex - 1];
			heap.pop_back();
			currentIndex--;
			perculateDown(1);
		}

		//Else: toRet = heap[2]
		{
			heap[2] = heap[currentIndex - 1];
			heap.pop_back();
			currentIndex--;
			perculateDown(2);
		}
	}

	return toRet;
}


template <typename DataType>
void MMheap<DataType>::perculateUp(int index)
{
	bool hasSwitched = false;
	//If we are at root, or children of root, return
	//(because we can't go any higher)
	if(index < 3)
	{
		if(index == 0)
		{
			//cout << "YAY" << endl;
			return;
		}

		int parent = (index - 1) / 2;

		//cout << "Evaluating: " << heap[index] << " < " << heap[parent] << endl;
		//PARENT SHOULD BE GREATER THAN
		if(heap[parent] < heap[index])
		{
			//cout << "Swapping" << endl;
			swap(parent, index);
		}

		return;
	}

	int height = (log(index) / log(2));
	//cout << "Currently at height " << height << endl;
	//cout << "index " << index << endl;
	//cout << "calc  " << (log(index) / log(2)) << endl;
	int parent = (index - 1) / 2;
	int grandparent = (parent - 1) / 2;


	//cout << "Index is : " << index << endl;
	//cout << "grand par: " << grandparent << endl;

	//If height is even
	if(height % 2 == 0)
	{
		//cout << "Height is odd" << endl;

		//cout << "Evaluating: " << heap[index] << " < " << heap[grandparent] << endl;

		//Check if we can perculate up
		if(heap[grandparent] > heap[index])
		{

			hasSwitched = true;

			//cout << "Swapping" << endl;

			//Swap them
			swap(grandparent, index);

			//Our index is now parent
			index = grandparent;

			//See if we can perculate up again
			perculateUp(index);


		}

		if(!hasSwitched)
		{
			int parent = (index - 1) / 2;

			//PARENT SHOULD BE GREATER THAN
			if(heap[parent] > heap[index])
				swap(parent, index);
		}

		//Else: We can't perculateUp so continue this method to exit
	}

	//Height is odd
	else
	{
		//cout << "Height is odd" << endl;
		//Check if we perculate up

		//cout << "Evaluating: " << heap[index] << " < " << heap[grandparent] << endl;

		if(heap[grandparent] > heap[index])
		{
			hasSwitched = true;
			//cout << "Swapping" << endl;
			//Swap them
			swap(grandparent, index);

			//Our index is now parent
			index = grandparent;

			//See if we can perculate up again
			perculateUp(index);
		}

		if(!hasSwitched)
		{

			int parent = (index - 1) / 2;

			//PARENT SHOULD BE SMALLER THAN
			if(heap[parent] < heap[index])
				swap(parent, index);
		}

		//Else: We can't perculateUp so we continue this method to exit
	}
}

template <typename DataType>
void MMheap<DataType>::perculateDown(int index)
{
	int child = (index * 2) + 1;
	int grandchildren = (child * 2) + 1;
	int height = log(index) / log(2);

	//We are on an ODD height (root is level 1)
	if(height % 2 == 0)
	{
		//We have all of our grandchildren
		if((grandchildren + 4) < currentIndex)
		{
			cout << "heap at index: " << heap[index] << endl;
			cout << "grandchildren: " << endl;
			//Get the smallest one
			int smallestGrandchild = grandchildren;
			cout << heap[smallestGrandchild] << endl;

			for(int i = grandchildren + 1; i < grandchildren + 4; i++)
			{
				cout << heap[grandchildren + i] << endl;
				if(heap[smallestGrandchild] > heap[i])
					smallestGrandchild = i;
			}

			cout << "smallest grandchild is " << heap[smallestGrandchild];

			//Base case: We're in the right position so check parent, and return
			if(heap[index] < heap[smallestGrandchild])
			{
				int parent = index / 2;

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

			int parent = (index - 1) / 2;

			if(heap[index] < heap[parent])
			{
				swap(index, parent);
			}
		}
	}

	//We're on an EVEN height, root starts at height 1
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
				int parent = (index - 1) / 2;

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

			int parent = (index - 1) / 2;

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

	int children = (index * 2) + 1;
	int grandchild = (children * 2) + 1 ;

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

	int children = (index * 2) + 1;
	int grandchild = (children * 2) + 1;

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
		int minIndex = 0;

		for(unsigned int i = 1; i < descendents.size(); i++)
		{
			if(min > descendents[i])
			{
				min = descendents[i];
				minIndex = i;
			}
		}

		return indexes[minIndex];
	}

	//Idk what to do. Just return index I guess.
	return index;
}

