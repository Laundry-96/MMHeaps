#include "MMheap.h"

template <typename DataType>
MMheap<DataType>::MMheap()
{
	currentIndex = 0;
}

template <typename DataType>
void MMheap<DataType>::dump()
{
	cout << "--- min-max heap dump ---"  << endl;
	cout << "Size = " << size() << endl;
	cout << "Minimum = " << getMin() << endl;
	cout << "Maximum = " << getMax() << endl;

	int height = log(currentIndex) / log(2);

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
		cout << "H[" << i+1 << "] = " << heap[i] << endl;
	}

}

template <typename DataType>
DataType MMheap<DataType>::getMin()
{
	if(currentIndex != 0)
	{
		return heap[0];
	}

	throw MyException("The heap is empty.");
}

template <typename DataType>
DataType MMheap<DataType>::getMax()
{
	if(currentIndex == 0)
	{
		throw MyException("The heap is empty.");
	}

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

	if(currentIndex == 0)
	{
		throw MyException("The heap is empty");
	}

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

	if(currentIndex == 0)
	{
		throw MyException("The heap is empty");
	}

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
		else
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
	//WE ONLY CARE ABOUT FIRST 3 NODES HERE
	if(index < 3)
	{
		if(index == 0)
		{
			//cout << "YAY" << endl;
			return;
		}

		int parent = (index - 1) / 2;

		//PARENT SHOULD BE LESS THAN
		//SO WE CHECK IF IT'S BIGGER
		if(heap[parent] > heap[index])
		{
			swap(parent, index);
		}

		return;
	}


	bool hasSwitched = false;
	int parent = (index - 1) / 2;
	int grandparent = (parent - 1) / 2;

	unsigned int height = log(index + 1) / log(2);

	//If even
	if(height % 2 == 0)
	{
		//Parent should be greater than
		if(heap[parent] < heap[index])
		{
			hasSwitched = true;

			swap(parent, index);

			index = parent;

			perculateUp(index);
		}

		//Grandparent should be less than
		else if(!hasSwitched && heap[grandparent] > heap[index])
		{
			hasSwitched = true;

			swap(grandparent, index);

			index = grandparent;

			perculateUp(index);
		}
	}

	//Else: odd
	else
	{
		//Parent should be less than
		if(heap[parent] > heap[index])
		{
			hasSwitched = true;

			swap(parent, index);

			index = parent;

			perculateUp(index);
		}

		//Grandparent should be greater than
		else if(!hasSwitched && heap[grandparent] < heap[index])
		{
			hasSwitched = true;

			swap(grandparent, index);

			index = grandparent;

			perculateUp(index);
		}
	}
}

template <typename DataType>
void MMheap<DataType>::perculateDown(int index)
{
	int child = (index * 2) + 1;
	int grandchildren = (child * 2) + 1;
	int height = log(index + 1) / log(2);

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

			//We should be smaller than our smallest grandchild
			//Base case: We're in the right position so check parent, and return
			if(heap[index] < heap[smallestGrandchild])
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
			int absMin = getMinTwoGen(index);

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

			//We should be bigger than our biggest grandchild
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

			//If we're bigger than the max (base case)
			if(heap[index] > heap[absMax])
			{
				//We're good and we can return
				return;
			}



			//If we're smaller than max, that's not good.
			else
			{
				swap(index, absMax);

				index = absMax;
			}

			int parent = (index - 1) / 2;

			//We want index to be bigger than parent
			if(heap[index] < heap[parent])
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

template <typename DataType>
int MMheap<DataType>::getMinTwoGen(int index)
{
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

