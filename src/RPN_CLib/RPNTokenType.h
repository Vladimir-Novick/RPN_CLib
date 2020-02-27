#pragma once

#include "pch.h"

namespace RPN {

    enum RPNTokenType
    {
        NONE = 0,
        ALPHA,
        NUMBER,
        OPERAND,
        STRING,
        FUNCTION
    };

}
