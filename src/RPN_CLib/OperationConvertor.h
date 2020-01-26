#pragma once


#include "pch.h"

#include "RPNOperandType.h"


using namespace std;
typedef map<string, RPNOperandType>  OperationDictionaryType;

class OperationConvertor
{

  public:

	  static string Format(const char * message, string& token);
	  static string Format(const char* message, char& token);

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


