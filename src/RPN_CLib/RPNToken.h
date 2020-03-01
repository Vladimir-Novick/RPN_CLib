#pragma once

#include "pch.h"
#include <string>
#include "RPNTokenType.h"
#include "RPNOperandType.h"
#include "RPNToken.h"
#include "Types.h"

namespace RPN {

    using namespace std;

    class RPNToken
    {
    public:
        RPNTokenType m_sType;
        string m_sToken;
        RPNOperandType m_OperandType;
        ActionType m_Action;
        RPNToken();
        RPNToken(const RPNToken& token);
    };

}

