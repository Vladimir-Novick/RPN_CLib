#pragma once


#include "pch.h"

#include "RPNTokenType.h"
#include "RPNOperandType.h"
#include "RPNTokenType.h"
#include "RPNToken.h"
#include <string>
#include <iterator> 
#include <iostream>
#include <map> 
#include <list>
#include <vector>
#include "RPNException.h"

#include "RPNOperandType.h"
#include "Types.h"


using namespace std;


class OperationConvertor
{

  public:

	  static string Format(const char * message, string& token);
	  static string Format(const char* message, char* token);

	  static const char operators[];
	  static const string doubleOperators[];
	  static const char doubleOperatorsChar[];

	  static const OperationDictionaryType GetOperation;

	  static RPNOperandType GetOperationType(string str);

	  static bool isOperation(char& c);
	  static bool isDoubleOperation(string& c);
	  static bool isDoubleOperation(char& c, char& c2);
	  static bool IsWhiteSpace(char& chr);

};


