#pragma once

template<class ElType>
struct ListItem
{
	ElType* data = nullptr;
	ListItem<ElType>** nextPtrs = nullptr;
};

template<class ElType>
struct DescriptorList
{
	ListItem<ElType>* first = nullptr;
	ListItem<ElType>* last = nullptr;
};

template<class ElType>
class MultiplyLinkedList
{
public:
	MultiplyLinkedList(unsigned int numDescrtiptors);
	~MultiplyLinkedList();

	void insertItem(ElType* data);
	void deleteCurrentItem();

	void insertCurrentItemToDescriptor(unsigned int numDescriptor);

	void toNextItem(unsigned int numDescriptor);

	void setFirstListItem(unsigned int numDescriptor);
	void setLastListItem(unsigned int numDescriptor);

	unsigned int sizeList();

	ElType* getCurrentItemData();
	ElType* getNextItemData(unsigned int numDescriptor);

	bool checkExistCurrentListItem();

private:
	ListItem<ElType>* currentListItem;

	DescriptorList<ElType>* descriptorArray;
	unsigned int numDescriptors;
	unsigned int countItem;

	unsigned int checkNumDescriptor(unsigned int checkNum);
};

template<class ElType>
inline MultiplyLinkedList<ElType>::MultiplyLinkedList(unsigned int numDescrtiptors)
{
	this->numDescriptors = (numDescrtiptors < 1) ? 1 : numDescrtiptors;
	this->countItem = 0;
	this->descriptorArray = new DescriptorList<ElType>[numDescriptors];
	currentListItem = nullptr;
}

template<class ElType>
inline MultiplyLinkedList<ElType>::~MultiplyLinkedList()
{
	setFirstListItem(0);
	
	while (checkExistCurrentListItem()) {
		ListItem<ElType>* ptr = currentListItem;
		currentListItem = currentListItem->nextPtrs[0];

		delete[] ptr->nextPtrs;
		delete ptr->data;
		delete ptr;
	}

	delete[] descriptorArray;
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::insertItem(ElType* data)
{
	ListItem<ElType>* item = new ListItem<ElType>;
	item->data = data;
	item->nextPtrs = new ListItem<ElType>*[numDescriptors] {nullptr};

	if (this->descriptorArray[0].first == nullptr) {
		this->descriptorArray[0].first = item;
	}
	else {
		this->descriptorArray[0].last->nextPtrs[0] = item;
	}

	this->descriptorArray[0].last = item;

	this->countItem++;
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::deleteCurrentItem()
{
	if (!checkExistCurrentListItem()) {
		return;
	}

	for (unsigned int i = 0; i < numDescriptors; i++) {
		ListItem<ElType>* ptr = descriptorArray[i].first;

		if (ptr == nullptr) {
			continue;
		}

		if (ptr == currentListItem) {
			descriptorArray[i].first = currentListItem->nextPtrs[i];
		}
		else {
			while (ptr->nextPtrs[i] != nullptr) {
				if (ptr->nextPtrs[i] == currentListItem) {
					ptr->nextPtrs[i] = currentListItem->nextPtrs[i];

					if (descriptorArray[i].last == currentListItem) {
						descriptorArray[i].last = ptr;
					}
					break;
				}
				ptr = ptr->nextPtrs[i];
			}
		}
	}
	delete[] currentListItem->nextPtrs;
	delete currentListItem->data;
	delete currentListItem;
	this->currentListItem = nullptr;

	this->countItem--;
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::insertCurrentItemToDescriptor(unsigned int numDescriptor)
{
	if (!checkExistCurrentListItem()) {
		return;
	}

	numDescriptor = checkNumDescriptor(numDescriptor);

	if (this->descriptorArray[numDescriptor].first == nullptr) {
		this->descriptorArray[numDescriptor].first = currentListItem;
	}
	else {
		this->descriptorArray[numDescriptor].last->nextPtrs[numDescriptor] = currentListItem;
	}

	this->descriptorArray[numDescriptor].last = currentListItem;
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::toNextItem(unsigned int numDescriptor)
{
	if (!checkExistCurrentListItem()) {
		return;
	}

	numDescriptor = checkNumDescriptor(numDescriptor);

	currentListItem = currentListItem->nextPtrs[numDescriptor];
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::setFirstListItem(unsigned int numDescriptor)
{
	numDescriptor = checkNumDescriptor(numDescriptor);

	this->currentListItem = this->descriptorArray[numDescriptor].first;
}

template<class ElType>
inline void MultiplyLinkedList<ElType>::setLastListItem(unsigned int numDescriptor)
{
	numDescriptor = checkNumDescriptor(numDescriptor);

	this->currentListItem = this->descriptorArray[numDescriptor].last;
}

template<class ElType>
inline unsigned int MultiplyLinkedList<ElType>::sizeList()
{
	return countItem;
}

template<class ElType>
inline ElType* MultiplyLinkedList<ElType>::getCurrentItemData()
{
	return (!checkExistCurrentListItem()) ? nullptr : currentListItem->data;
}

template<class ElType>
inline ElType* MultiplyLinkedList<ElType>::getNextItemData(unsigned int numDescriptor)
{
	if (!checkExistCurrentListItem()) {
		return nullptr;
	}

	numDescriptor = checkNumDescriptor(numDescriptor);

	return (currentListItem->nextPtrs[numDescriptor] == nullptr) ? nullptr : currentListItem->nextPtrs[numDescriptor]->data;
}

template<class ElType>
inline unsigned int MultiplyLinkedList<ElType>::checkNumDescriptor(unsigned int checkNum)
{
	return (checkNum >= this->numDescriptors) ? this->numDescriptors : checkNum;
}

template<class ElType>
inline bool MultiplyLinkedList<ElType>::checkExistCurrentListItem()
{
	return currentListItem != nullptr;
}

