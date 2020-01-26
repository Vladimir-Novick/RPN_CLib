#pragma once

#include "pch.h"
#include <string>

using namespace std;

class RPNToken
{
public:
     RPNTokenType m_sType;
     string m_sToken;
     RPNOperandType m_OperandType;
     RPNOperandType m_Operation;
     RPNToken();
     RPNToken(const RPNToken& token); // Copy constructor 
};

