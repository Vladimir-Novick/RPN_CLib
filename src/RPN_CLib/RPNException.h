#pragma once
#include <exception>
using namespace std;
class  RPNException : 	public runtime_error
{
public:
    RPNException(char const* const message) throw();
    virtual char const* what() const throw();
};

