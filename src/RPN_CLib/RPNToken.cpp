#include "pch.h"
#include "RPNToken.h"

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

namespace RPN {


    RPNToken::RPNToken() {
    }

    RPNToken::RPNToken(const RPNToken& token) {
        m_sType = token.m_sType;
        m_sToken = token.m_sToken;
        m_OperandType = token.m_OperandType;
        m_Operation = token.m_Operation;
    }
}
