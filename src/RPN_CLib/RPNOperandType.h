#pragma once

#include "pch.h"

    enum RPNOperandType
    {
        UNKNOWN,
        STAR_TPARENTHESES,
        END_PARENTHESES,


        //operators
        MULITIPLY,
        DIVIDE,
        PLUS_OPERATOR,
        MINUS_OPERATOR,
        LESS,
        GREATER,
        LESSOREQUAL,
        GREATEOREQUAL,
        NOTEQUAL,
        EQUAL,
        OR_OPERATOR,
        AND_OPERATOR,
        NOT_OPERATOR,
        JUSTPLUS,
        JUSTMINUS,
        ARIFMETICAL,
        DIV_OPERATOR,
        EXPONENTIATION,
        MOD_OPERATOR
    };
