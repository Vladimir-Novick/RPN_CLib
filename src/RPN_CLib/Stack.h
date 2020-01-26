#pragma once

#include "pch.h"

#include <iostream>
#include <vector>
#include "RPN_Errors.h"
using namespace std;

template <class T>
class Stack {

private:
	vector<T> data;

public:

	RPN_ERRORS rpn_error;

	unsigned char  stack_size(Stack<T>& ctxt);
	bool  stack_clear(Stack<T>& ctxt);
	bool  stack_push(Stack<T>& ctxt, T value);
	bool  stack_pop(Stack<T>& ctxt, T& value);

	bool  stack_get(Stack<T>& ctxt, unsigned char index, T& value);
	bool empty(); //checks if stack is empty 
	void push(T item); //adds item to stack
	void push_back(T value);
	void pop_back();
	T top(); //returns item at top of stack
	T back();
	void pop(); //removes item at top of stack
	int size();
	void clear();
	T operator [](int index);
	friend ostream& operator<<(ostream& out, const Stack& s); //overloaded output operator

};



