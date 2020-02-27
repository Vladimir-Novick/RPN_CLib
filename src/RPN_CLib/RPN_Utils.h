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


namespace RPN {


	using namespace std;


	class RPN_Utils
	{

	public:

		static string Format(const char* message, string& token);
		static string Format(const char* message, string& token, string& expression);
		static string Format(const char* message, char* token);

		static bool IsWhiteSpace(char& chr);

	};

}


