#pragma once

#include "pch.h"

    enum RPNOperandType
    {
        UNKNOWN,
        STAR_TPARENTHESES,
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
        JUST_PLUS,
        JUST_MINUS,
      
        DIV_OPERATOR,
        EXPONENTIATION,
        MOD_OPERATOR
    };
