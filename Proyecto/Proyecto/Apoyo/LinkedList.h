#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedList : public List<E>
{
private:
	Node<E>* head;
	Node<E>* current;
	Node<E>* tail;
	int size;

public:
	LinkedList() {
		tail = current = head = new Node<E>();
		size = 0;
	}
	~LinkedList() {
		clear();
		delete head;
	}
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = current->next;
		size++;
	}
	void append(E element) {
		tail = tail->next = new Node<E>(element);
		size++;
	}
	void set(E element) {
		if (current->next == nullptr)
			throw runtime_error("No current element.");
		current->next->element = element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		E result = current->next->element;
		Node<E>* temp = current->next;
		if (tail == temp)
			tail = current;
		current->next = temp->next;
		delete temp;
		size--;
		return result;
	}
	void clear() {
		while (head->next != nullptr) {
			current = head->next;
			head->next = current->next;
			delete current;
		}
		current = tail = head;
		size = 0;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty.");
		if (current == tail)
			throw runtime_error("No current element.");
		return current->next->element;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current)
				temp = temp->next;
			current = temp;
		}
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail;
	}
	int getSize() {
		return size;
	}
	int getPos() {
		// Elaborado por Alejandro Madrigal
		Node<E>* temp = head;
		int i;
		for (i = 0; current != temp; i++)
			temp = temp->next;
		return i;
	}
	void print() {
		cout << "[ ";
		Node<E>* temp = head->next;
		while (temp != nullptr) {
			cout << temp->element << " ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
	int indexOf(E element) {
		Node<E>* temp = head->next;
		int i;
		for (i = 0; temp != nullptr; i++) {
			if (temp->element == element)
				return i;
			temp = temp->next;
		}
		return -1;
	}
	bool contains(E element) {
		Node<E>* temp = head->next;
		while (temp != nullptr) {
			if (temp->element == element)
				return true;
			temp = temp->next;
		}
		return false;
	}
};


