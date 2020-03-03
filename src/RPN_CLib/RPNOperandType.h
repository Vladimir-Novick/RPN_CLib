#pragma once

#include "pch.h"

namespace RPN {

    enum RPNOperandType
    {
        UNKNOWN,
        VARIABLE,
        START_TPARENTHESES,
        END_PARENTHESES,
        ARIFMETICAL,


        //operators
        MULITIPLY,
        DIVIDE,
        PLUS_OPERATOR,
        MINUS_OPERATOR,
        LESS,
        GREATER,
        LESS_OR_EQUAL,
        GREATE_OR_EQUAL,
        NOT_EQUAL,
        EQUAL,
        OR_OPERATOR,
        AND_OPERATOR,
        NOT_OPERATOR,
        IF_OPERATOR,
        JUST_PLUS,
        JUST_MINUS,

        DIV_OPERATOR,
        EXPONENTIATION,
        MOD_OPERATOR
    };

}
