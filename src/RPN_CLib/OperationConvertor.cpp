#include "pch.h"

#include "Types.h"
#include "OperationConvertor.h"
#include "RPNOperandType.h"

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

    string OperationConvertor::Format(const char *message, string& token) {
        char buff[120];

        snprintf(buff, sizeof(buff), "%s -> %s", message, token.c_str());
        std::string buffAsStdStr = buff;
        return buffAsStdStr;
    }

    string OperationConvertor::Format(const char* message, char* token) {
        char buff[120];

        snprintf(buff, sizeof(buff), "%s -> %s", message, token);
        std::string buffAsStdStr = buff;
        return buffAsStdStr;
    }

    const char OperationConvertor::operators[] = { '+', '-', '*', '/', '<', '>', '=', '%', '^', '(', ')', '~', 'x', '÷' };
    const string OperationConvertor::doubleOperators[] = { "<>", ">=", "<=", "%=", "/=","==","||","&&" };
    const char OperationConvertor::doubleOperatorsChar[] = { '<','>', '>','=', '<','=', '%','=', '/','=','=','=','|','|','&','&' };

    RPNOperandType OperationConvertor::GetOperationType(string str) {
         OperationDictionaryType::const_iterator ret1 = OperationConvertor::GetOperation.find(str);
        if (ret1 != OperationConvertor::GetOperation.end()) return ret1->second;
        return UNKNOWN;
    }

    bool OperationConvertor::IsWhiteSpace(char& chr)
    {
        if (chr == ' ' || chr == '/r' || chr == '\n' || chr == '\t') return true;
        return false;
    }

    bool OperationConvertor::isOperation(char& c)
    {

        for (int i = 0; OperationConvertor::operators[i] != 0; i++)
            if (c == OperationConvertor::operators[i])
                return true;

        return false;
    }

    bool OperationConvertor::isDoubleOperation(string& c)
    {
        for (unsigned int i = 0; OperationConvertor::doubleOperators->size() > i; i++)
            if (c == OperationConvertor::doubleOperators[i])
                return true;

        return false;
    }

    bool OperationConvertor::isDoubleOperation(char& c, char& c2)
    {
        for (unsigned int i = 0; OperationConvertor::doubleOperators->size() > i; i = i + 2)
            if (c == OperationConvertor::doubleOperatorsChar[i] &&
                c2 == OperationConvertor::doubleOperatorsChar[i + 1]

                )
                return true;

        return false;
    }




    const  OperationDictionaryType OperationConvertor::GetOperation = {
{ "@",UNKNOWN},
{ "*",MULITIPLY},
{ "/",DIVIDE},
{ "÷",DIVIDE},
{ "/=",DIV_OPERATOR},
{ "^",EXPONENTIATION },
{ "%=",MOD_OPERATOR },
{ "+",PLUS_OPERATOR},
{ "-",MINUS_OPERATOR},
{ "~",JUST_MINUS},
{ "<",LESS},
{ ">",GREATER},
{ "<=",LESS_OR_EQUAL},
{ ">=",GREATE_OR_EQUAL},
{ "!=",NOT_EQUAL},
{ "==",EQUAL},
{ "=",EQUAL},
{ "||",OR_OPERATOR},
{ "&&",AND_OPERATOR},
{ "!",NOT_OPERATOR},
{ "(",STAR_TPARENTHESES },
{ ")",END_PARENTHESES }

    };
