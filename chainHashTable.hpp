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
		int size(void);
		int count(void);

		ChainHashTable(int desiredSize, int (*hashFunc)(T, int), int loadFact = 20);

    // private:
        int tableSize;
		int tableCount;
		int loadFactor;
		int (*hashFunction)(T vlaue, int size);
		ChainHashTableNode<T>** table;

		void rehash();
};

template<class T>
ChainHashTable<T>::ChainHashTable(int desiredSize, int (*hashFunc)(T, int), int loadFact) {
	tableSize = desiredSize;
	loadFactor = loadFact;
	tableCount = 0;
	hashFunction = hashFunc;

	table = new ChainHashTableNode<T>*[tableSize];
	for (int i = 0; i < tableSize; i++)
		table[i] = nullptr;
}

template<class T>
int ChainHashTable<T>::count(void) {
	return tableCount;
}

template<class T>
int ChainHashTable<T>::size(void) {
	return tableSize;
}

template<class T>
LinkedListNode<T>* ChainHashTable<T>::search(T value) {
	int index = hashFunction(value, tableSize);
	if (table[index] == nullptr)
		return nullptr;

	return table[index]->list.search(value);
}

template<class T>
void ChainHashTable<T>::insert(T value) {
	int index = hashFunction(value, tableSize);

	if (table[index] == nullptr)
		table[index] = new ChainHashTableNode<T>;

	table[index]->list.insertFront(value);
	tableCount++;

	if (tableCount/tableSize > loadFactor)
		rehash();
}

template<class T>
T ChainHashTable<T>::remove(T value) {
	int index = hashFunciton(value, tableSize);

	T status = table[index]->list.remove(value);

	if (status == nullptr)
		tableCount--;
}
	
template<class T>
void ChainHashTable<T>::rehash() {
	int oldSize = tableSize;
	ChainHashTableNode<T>** oldTable = table;
	tableSize *= 2;
	
	table = new ChainHashTableNode<T>*[tableSize];
	for (int i = 0; i < tableSize; i++)
		table[i] = nullptr;

	int index;
	LinkedListNode<T>* temp;
	for (int i = 0; i < oldSize; i++) {
		if (oldTable[i] == nullptr)
			continue;
		for (temp = oldTable[i]->list.head; temp; temp = temp->next) {
			index = hashFunction(temp->data, tableSize);
            if (table[index] == nullptr)
                table[index] = new ChainHashTableNode<T>;
			table[index]->list.insertFront(temp->data);
		}
	}
	delete oldTable;
}

#endif // #ifndef CHAIN_HASH_TABLE_HPP
