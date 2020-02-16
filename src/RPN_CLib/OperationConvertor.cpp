#include "pch.h"

#include "Types.h"
#include "OperationConvertor.h"
#include "RPNOperandType.h"
#include "Operators.h"

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



    bool OperationConvertor::IsWhiteSpace(char& chr)
    {
        if (chr == ' ' || chr == '/r' || chr == '\n' || chr == '\t') return true;
        return false;
    }







