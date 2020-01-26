#pragma once

#include "pch.h"

#include "OperationConvertor.h"
#include "Types.h"

using namespace std;

class RPNProcessor 
{
private:
    list<RPNToken*> m_Tokens;
    string m_expression;
    bool GetTokens(string &expr, list<RPNToken*>& Tokens);
public:
    RPNProcessor(list<RPNToken*>& Tokens);
    RPNProcessor(string& expr);
    RPNProcessor();
    ~RPNProcessor();



};

