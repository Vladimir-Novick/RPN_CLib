#include "pch.h"
#include "RPNException.h"


using namespace std;

RPNException::RPNException(char const* const message) throw()
    : runtime_error(message)
{

}

char const* RPNException::what() const throw()
{
    return exception::what();
}
