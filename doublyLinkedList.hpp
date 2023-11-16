#ifndef LINKED_LISTS_HPP
#define LINKED_LISTS_HPP

#include <iostream>
#include <string>

template <class T>
struct LinkedListNode {
    T data;
    LinkedListNode* next;
    LinkedListNode* prev;
    LinkedListNode(T value);
};
 
template<class T>
LinkedListNode<T>::LinkedListNode(T value) {
    data = value;
    next = prev = nullptr;
}
 
template<class T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    LinkedListNode<T>* insertFront(T);
    LinkedListNode<T>* insertBack(T);
    T removeFront();
    T removeBack();
    bool isEmpty();
	T remove(T value);
    void display();
    int length();
    LinkedListNode<T>* search(T);

    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;
 
};
 
template<class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head = tail = nullptr;
    size = 0;
}
 
template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()  {
}
 
template<class T>
LinkedListNode<T>* DoublyLinkedList<T>::insertFront(T value) {
    LinkedListNode<T>* temp = new LinkedListNode<T>(value);
 
    if (head == nullptr)
        head = tail = temp;
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
    size++;

	return temp;
}
 
template<class T>
LinkedListNode<T>* DoublyLinkedList<T>::insertBack(T value) {
    LinkedListNode<T>* temp = new LinkedListNode<T>(value);
 
    if (tail == nullptr)
        head = tail = temp;
    else
    {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    size++;

	return temp;
}

template<class T>
T DoublyLinkedList<T>::remove(T value) {
	LinkedListNode<T>* node = search(value);

	if (!node)
		return nullptr;

	if (node == head)
		return removeFront();
	else if (node == tail)
		return removeBack();
	else {
		T deletedValue = node->data;

		node->left->right = node->right;
		node->rigth->left = node->left;
 
        delete node;
 
        size--;
 
        return deletedValue;
    }
}
 
template<class T>
T DoublyLinkedList<T>::removeFront() {
    if (!isEmpty())
    {
        LinkedListNode<T>* temp = head;
        if (head == tail)
        {
            tail = nullptr;
        }
        T deletedValue = temp->data;
        head = head->next;
 
        delete temp;
 
        size--;
 
        return deletedValue;
    }
    return nullptr;
}
 
template<class T>
T DoublyLinkedList<T>::removeBack() {
    if (!isEmpty())
    {
        LinkedListNode<T>* temp = tail;
        if (head == tail)
        {
            head = nullptr;
        }
        T* deletedValue = temp->data;
        tail->next = nullptr;
        tail = tail->prev;
 
        delete temp;
 
        size--;
 
        return deletedValue;
    }
    return nullptr;
}
 
template<class T>
bool DoublyLinkedList<T>::isEmpty() {
    if (size <= 0)
    {
        return true;
    }
 
    return false;
}
 
template<class T>
void DoublyLinkedList<T>::display() {
    LinkedListNode<T>* temp = head;
 
    while (temp != nullptr)
    {
		std::cout << temp->data << ", ";
        temp = temp->next;
    }
	std::cout << "\b\b \b";
}
 
template<class T>
int DoublyLinkedList<T>::length() {
    return size;
}
 
template<class T>
LinkedListNode<T>* DoublyLinkedList<T>::search(T value) {
    if (!isEmpty()) {
        LinkedListNode<T>* temp = head;
        while (temp) {
            if (temp->data == value)
            {
				return temp;
            }
            temp = temp->next;
        }
    }
		return nullptr;
}

#endif // #define LINKED_LISTS_HPP
