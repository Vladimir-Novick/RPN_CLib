#include "pch.h"
#include <iostream>
#include <vector>
#include "Stack.h"



	using namespace std;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#ifdef _DEBUG
#define new DBG_NEW
#endif


	template <class T>
	unsigned char Stack<T>::stack_size(Stack<T>& ctxt) {
		return ctxt.stack.size();
	}

	template <class T>
	bool Stack<T>::stack_clear(Stack<T>& ctxt) {
		ctxt.stack.clear();
		return true;
	}

	template <class T>
	bool Stack<T>::stack_push(Stack<T>& ctxt, T value) {
		ctxt.stack.push_back(value);
		return true;
	}

	template <class T>
	bool Stack<T>::stack_pop(Stack<T>& ctxt, T& value) {
		if (0 == ctxt.stack.size()) return false;
		value = ctxt.stack.back();
		ctxt.stack.pop_back();
		return true;
	}

	template <class T>
	bool Stack<T>::stack_get(Stack<T>& ctxt, unsigned char index, T& value) {
		unsigned char size = ctxt.stack.size();
		if (index >= size) return false;
		value = ctxt.stack[size - index - 1];
		return true;
	}

	template <class T>
	bool Stack<T>::empty() //checks if stack is empty 
	{
		return data.empty();
	}

	template <class T>
	T Stack<T>::operator [](int index) 
	{
		return data[index];
	}

	template <class T>
	void Stack<T>::push(T item) //adds item to stack
	{
		data.push_back(item);
	}

	template <class T>
	T Stack<T>::top() //returns item at top of stack
	{
		if (data.back() > -1)
			return data.back();

		else
			cerr << "Stack is empty\n";
	}

	template <class T>
	void Stack<T>::pop() //removes item at top of stack
	{
		data.pop_back();
	}

	template <class T>
	int Stack<T>::size() 
	{
		return data.size();
	}

	template <class T>
	T Stack<T>::back()
	{
		return data.back();
	}


	template <class T>
	void Stack<T>::push_back(T value)
	{data.push_back(value);
	return;
	}

	template <class T>
	void Stack<T>::pop_back()
	{
		data.pop_back();
		return;
	}

	template <class T>
	void Stack<T>::clear()
	{
		data.clear();
		return;
	}


	template <class T>
	ostream& operator<<(ostream& out, const Stack<T>& s) //overloaded output operator
	{
		while (!s.empty())
		{
			out << s.top();
			s.pop();
		}return out;
	}

