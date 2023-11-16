#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "chainHashTable.hpp"
#include "doublyLinkedList.hpp"

int hash(int value, int max) {
	return value % (max);
}

int main(void) {
	ChainHashTable<int>* table = new ChainHashTable<int>(8, hash, 2);

	for (int i = 0; i < 100; i++)
		table->insert(rand() % 30);
	
	std::cout << "count: " << table->count << std::endl;
}
