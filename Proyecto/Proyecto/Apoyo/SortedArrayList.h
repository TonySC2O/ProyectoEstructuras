#pragma once

#define DEFAULT_MAX_SIZE 1024

#include <stdexcept>
#include <iostream>
#include <string>
#include "ArrayList.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class SortedArrayList : public ArrayList<E> {
public:

	SortedArrayList(int maxSize = DEFAULT_MAX_SIZE) : ArrayList<E>(maxSize){}

	void insert(E element) {
		ArrayList<E>::goToStart();
		while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement()) {
			ArrayList<E>::next();
		}
		ArrayList<E>::insert(element);
	}
	void append(E element) {
		insert(element);
	}
};