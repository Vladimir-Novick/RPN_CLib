#pragma once

#include "pch.h"

    enum RPNTokenType
    {
        NONE = 0,
        ALPHA,
        NUMBER,
        OPERAND,
        STRING,
        FUNCTION
    };
