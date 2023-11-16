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
    void removeFront();
    void removeBack();
    bool isEmpty();
    void remove(LinkedListNode<T>* node);
    void display();
    int length();
    LinkedListNode<T>* search(T);

    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;
 
};
 
template<class T> DoublyLinkedList<T>::DoublyLinkedList() {
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
void DoublyLinkedList<T>::remove(LinkedListNode<T>* node) {
	if (!node)
        return;

	if (node == head)
        removeFront();
    else if (node == tail) {
        qDebug() << "tail:";
        removeBack();
    }
	else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
 
        delete node;
 
        size--;
    }
}
 
template<class T>
void DoublyLinkedList<T>::removeFront() {
    if (!isEmpty())
    {
        LinkedListNode<T>* temp = head;
        if (head == tail)
        {
            tail = nullptr;
        }
        head = head->next;
 
        delete temp;
 
        size--;
    }
}
 
template<class T>
void DoublyLinkedList<T>::removeBack() {
    if (!isEmpty())
    {
        LinkedListNode<T>* temp = tail;
        if (head == tail)
        {
            head = nullptr;
        }
        tail->prev->next = nullptr;
        tail = tail->prev;
 
        delete temp;
 
        size--;
    }
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
        while (temp != nullptr) {
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
