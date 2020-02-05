#pragma once
#include "pch.h"
#include <string>
#include <math.h>
#include <map>
#include "Stack.h"
#include "RPNOperandType.h"

using namespace std;


typedef Stack<float>  rpn_stack;
typedef map<string, RPNOperandType>  OperationDictionaryType;
typedef bool (*CallbackFunction)(rpn_stack &);

struct OperatorType
{
    string name;
    int arguments;
    CallbackFunction f;
};

typedef map<string, OperatorType>  ActionDictType;
