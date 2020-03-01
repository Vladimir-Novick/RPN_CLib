#pragma once
#include "pch.h"
#include <string>
#include <math.h>
#include <map>
#include <stack>
#include "RPNOperandType.h"

namespace RPN {

    using namespace std;


    typedef stack<float>  rpn_stack;
    typedef map<string, RPNOperandType>  OperationDictionaryType;
    typedef bool (*CallbackFunction)(rpn_stack&);

    struct ActionType
    {
        string name;
        int arguments;
        CallbackFunction f;
        int index;
        RPNOperandType dataType;
        bool isDoubleChar;
    };

    typedef map<string, ActionType>  ActionDictType;

}
