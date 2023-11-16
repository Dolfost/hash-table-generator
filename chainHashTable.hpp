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
        void remove(T value);
		int size(void);
		int count(void);

        ChainHashTable(int desiredSize, double loadFact, int (*hashFunc)(T, int));

    // private:
        int tableSize;
		int tableCount;
        double loadFactor;
		int (*hashFunction)(T vlaue, int size);
		ChainHashTableNode<T>** table;

		void rehash();
};

template<class T>
ChainHashTable<T>::ChainHashTable(int desiredSize, double loadFact, int (*hashFunc)(T, int)) {
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

    if (double(tableCount)/tableSize > loadFactor)
		rehash();
}

template<class T>
void ChainHashTable<T>::remove(T value) {
        int index = hashFunction(value, tableSize);

    if (table[index] == nullptr)
        return;

    LinkedListNode<T>* res = table[index]->list.search(value);
    if (res != nullptr) {
        qDebug() << value << res->data;
        table[index]->list.remove(res);
        tableCount--;
    }
}
	
template<class T>
void ChainHashTable<T>::rehash() {
	int oldSize = tableSize;
	ChainHashTableNode<T>** oldTable = table;
    tableSize = tableSize*2 + 1;
	
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
