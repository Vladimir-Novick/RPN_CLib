#include "pch.h"
#include "RPNProcessor.h"
#include <list>

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


using namespace std;

RPNProcessor::RPNProcessor() {
    m_expression= "";
}

RPNProcessor::RPNProcessor(list<RPNToken*>& Tokens) {
    for (auto item = Tokens.begin(); item != Tokens.end(); item++) {
        RPNToken *newToken  = *item;
        m_Tokens.push_back(newToken);
    }
}

RPNProcessor::RPNProcessor(string &expr) {
    m_expression = expr;
    GetTokens(expr, m_Tokens);

}

RPNProcessor::~RPNProcessor() {
    for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
        delete (*item);
    }
}

 bool RPNProcessor::GetTokens(string &expr, list<RPNToken*> &Tokens)
{
    int i = 0;
    string tok = "";
    RPNToken *token;

    bool IsGood = true;
    Tokens.clear();

    int expr_Length = expr.size();

    while (i <= expr_Length)
    {
        tok = "";
        token = new RPNToken();

        if (i > expr_Length - 1) { break; }

        if (OperationConvertor::IsWhiteSpace(expr[i]))
        {
            while (OperationConvertor::IsWhiteSpace(expr[i]))
            {
                i++;
                if (i > expr_Length - 1) { break; }
            }
        }

        if (i > expr_Length - 1) { break; }

        if (expr[i] == '\'')
        {
            while (!(expr[i] == '\''))
            {
                tok += expr[i];
                i++;
                if (i > expr_Length - 1)
                {
                    throw  RPNException(OperationConvertor::Format("Invalid string", tok).c_str());
                }
            }
            if (i <= expr_Length - 1)
            {
                {
                    tok += expr[i];
                    i++;
                }
            }
            token->m_sType = STRING;
            token->m_sToken = tok;
            Tokens.push_back(token);
        }

        if (i > expr_Length - 1) { break; }

        if (expr[i] == '[')
        {
            while (!(expr[i] == ']'))
            {
                tok += expr[i];
                i++;
                if (i > expr_Length - 1) { break; }
            }
            if (i <= expr_Length - 1)
            {
                {
                    tok += expr[i];
                    i++;
                }
            }
            token->m_sType = STRING;
            token->m_sToken = tok;
            Tokens.push_back(token);
        }

        if (i > expr_Length - 1) { break; }

        if (expr[i] == '"')
        {
            while (!(expr[i] == '"'))
            {
                tok += expr[i];
                i++;
                if (i > expr_Length - 1)
                {
                    throw  RPNException(OperationConvertor::Format("Invalid string", tok).c_str());
                }
            }
            if (i <= expr_Length - 1)
            {
                {
                    tok += expr[i];
                    i++;
                }
            }
            token->m_sType = STRING;
            token->m_sToken = tok;
            Tokens.push_back(token);
        }

        if (i > expr_Length - 1) { break; }

        if (isalpha(expr[i]))
        {
            while (isalpha(expr[i]) || (isdigit(expr[i]) || (expr[i] == '_')))
            {
                tok += expr[i];
                i++;
                if (i > expr_Length - 1) { break; }
            }
            token->m_sType = ALPHA;
            if (i < expr_Length)
            {
                if (expr[i] == '(')
                {
                    tok += "$";

                    token->m_sType = FUNCTION;
                }
                if (expr[i] == '$')
                {
                    tok += "$";
                    i++;

                    token->m_sType = FUNCTION;
                }
            }
            token->m_sToken = tok;
            Tokens.push_back(token);
        }
        else if (isdigit(expr[i]))
        {
            while (isdigit(expr[i]) || (expr[i] == '.'))
            {
                tok += expr[i];
                i++;
                if (i > expr_Length - 1) { break; }
            }
            token->m_sType = NUMBER;
            token->m_sToken = tok;
            Tokens.push_back(token);
        }
        else
            if ((i + 1 < expr_Length) && ((OperationConvertor::isDoubleOperation(expr[i] , expr[i + 1]))))
            {
                tok = expr[i];
                tok = tok + expr[i + 1];
                i++;
                token->m_sType = OPERAND;
                token->m_sToken = tok;
                token->m_OperandType = ARIFMETICAL;
                token->m_Operation = OperationConvertor::GetOperationType(tok);
                Tokens.push_back(token);
                i++;

                if (i > expr_Length - 1) { break; }

            }
            else
                if (OperationConvertor::isOperation(expr[i]))
                {
                    tok = expr[i];
                    token->m_sType = OPERAND;
                    token->m_sToken = tok;

                    token->m_OperandType = ARIFMETICAL;
                    token->m_Operation = OperationConvertor::GetOperationType(tok);

                    if (token->m_Operation == MINUS_OPERATOR)
                    {
                        auto it = Tokens.end();
                        if (Tokens.size() > 0 && (((*it)->m_sType == OPERAND)))
                        {
                            if ((*it)->m_Operation != END_PARENTHESES)
                            {
                                token->m_Operation = JUSTMINUS;
                                token->m_sToken = tok = "~";
                            }
                        }
                    }
                    if (token->m_Operation == PLUS_OPERATOR)
                    {
                        auto it = Tokens.end();
                        if (Tokens.size() > 0 && (*it)->m_sType == OPERAND)
                        {
                            if ((*it)->m_Operation != END_PARENTHESES)
                            {
                                token->m_Operation = JUSTPLUS;
                            }
                        }
                    }
                    Tokens.push_back(token);
                    i++;
                    if (i > expr_Length - 1) { break; }
                }
                else
                {
                    IsGood = false;
                    Tokens.clear();
                    if (i < expr_Length)
                    {
                        throw  RPNException(OperationConvertor::Format("Invalid token type ",  expr[i]).c_str());
                    }
                    else
                    {
                        throw  RPNException(OperationConvertor::Format("Invalid Expression ", expr).c_str());
                       
                    }
                }

    }
    return IsGood;
}
