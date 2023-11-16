#ifndef CHAIN_HASH_TABLE_HPP
#define CHAIN_HASH_TABLE_HPP

#include "doublyLinkedList.hpp"

template<class T>
struct ChainHashTableNode {
	DoublyLinkedList<T> list;
};

template<class T>
class ChainHashTable {
	public:
		void insert(T value);
		LinkedListNode<T>* search(T value);
		T remove(T value);

		ChainHashTable(int desiredSize, int (*hashFunc)(T, int), int loadFact = 20);

	/* private: */
		int size;
		int count;
		int loadFactor;
		int (*hashFunction)(T vlaue, int size);
		ChainHashTableNode<T>** table;

		void rehash();
};

template<class T>
ChainHashTable<T>::ChainHashTable(int desiredSize, int (*hashFunc)(T, int), int loadFact) {
	size = desiredSize;
	loadFactor = loadFact;
	count = 0;
	hashFunction = hashFunc;

	table = new ChainHashTableNode<T>*[size];
	for (int i = 0; i < size; i++)
		table[i] = nullptr;
}

template<class T>
LinkedListNode<T>* ChainHashTable<T>::search(T value) {
	return table[hashFunction(value, size)].search(value);
}

template<class T>
void ChainHashTable<T>::insert(T value) {
	int index = hashFunction(value, size);

	std::cout << index << " " << value << std::endl << std::flush;

	if (table[index] == nullptr)
		table[index] = new ChainHashTableNode<T>;

	table[index]->list.insertFront(value);
	count++;

	if (count/size > loadFactor)
		rehash();
}

template<class T>
T ChainHashTable<T>::remove(T value) {
	int index = hashFunciton(value, size);

	T status = table[index]->list.remove(value);

	if (status == nullptr)
		count--;
}
	
template<class T>
void ChainHashTable<T>::rehash() {
	int oldSize = size;
	std::cout << "REHASHING" << std::endl;
	ChainHashTableNode<T>** oldTable = table;
	size *= 2;
	
	table = new ChainHashTableNode<T>*[size];
	for (int i = 0; i < size; i++)
		table[i] = nullptr;

	int index;
	LinkedListNode<T>* temp;
	LinkedListNode<T>* temp2;
	for (int i = 0; i < oldSize; i++) {
		if (oldTable[i] == nullptr)
			continue;
		for (temp = oldTable[i]->list.head; temp; temp = temp->next) {
			index = hashFunction(temp->data, size);
			table[index] = new ChainHashTableNode<T>;
			table[index]->list.insertFront(temp->data);
		}
	}
	delete oldTable;
	std::cout << "REHASHING FINISHED" << std::endl;
}

#endif // #ifndef CHAIN_HASH_TABLE_HPP
