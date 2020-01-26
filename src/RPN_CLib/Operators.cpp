#include "pch.h"
#include "Types.h"
#include "Operators.h"

#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4305 ) 

#define RPN_CONST_PI    3.141593
#define RPN_CONST_E     2.178282


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

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------

bool Operators::pi(rpn_stack& ctxt) {
    ctxt.stack_push(ctxt, RPN_CONST_PI);
    return true;
}

bool Operators::e(rpn_stack& ctxt) {
    ctxt.stack_push(ctxt, RPN_CONST_E);
    return true;
}

// ----------------------------------------------------------------------------
// Math
// ----------------------------------------------------------------------------

bool Operators::sum(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a + b);
    return true;
}

bool Operators::substract(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a - b);
    return true;
}

bool Operators::times(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a * b);
    return true;
}

bool Operators::divide(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    if (0 == b) {
        ctxt.rpn_error = DIVIDE_BY_ZERO;
        return false;
    }
    ctxt.stack_push(ctxt, a / b);
    return true;
}

bool Operators::mod(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    a = (int)a;
    b = (int)b;
    if (0 == b) {
        ctxt.rpn_error = DIVIDE_BY_ZERO;
        return false;
    }
    float mod = a - (int)(a / b) * b;
    ctxt.stack_push(ctxt, mod);
    return true;
}

bool Operators::abs(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    if (a < 0) a = -a;
    ctxt.stack_push(ctxt, a);
    return true;
}



bool Operators::sqrt(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, OperationMath::fs_sqrt(a));
    return true;
}

bool Operators::log(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    if (0 >= a) {
        ctxt.rpn_error = UNVALID_ARGUMENT;
        return false;
    }
    ctxt.stack_push(ctxt, OperationMath::fs_log(a));
    return true;
}

bool Operators::log10(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    if (0 >= a) {
        ctxt.rpn_error = UNVALID_ARGUMENT;
        return false;
    }
    ctxt.stack_push(ctxt, OperationMath::fs_log10(a));
    return true;
}

bool Operators::exp(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, OperationMath::fs_exp(a));
    return true;
}

bool Operators::fmod(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    if (0 == b) {
        ctxt.rpn_error = DIVIDE_BY_ZERO;
        return false;
    }
    ctxt.stack_push(ctxt, OperationMath::fs_fmod(a, b));
    return true;
}

bool Operators::pow(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, OperationMath::fs_pow(a, b));
    return true;
}

bool Operators::cos(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, OperationMath::fs_cos(a));
    return true;
}

bool Operators::sin(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    float cos = OperationMath::fs_cos(a);
    float sin = OperationMath::fs_sqrt(1 - cos * cos);
    ctxt.stack_push(ctxt, sin);
    return true;
}

bool Operators::tan(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    float cos = OperationMath::fs_cos(a);
    if (0 == cos) {
        ctxt.rpn_error = UNVALID_ARGUMENT;
        return false;
    }
    float sin = OperationMath::fs_sqrt(1 - cos * cos);
    ctxt.stack_push(ctxt, sin / cos);
    return true;
}


// ----------------------------------------------------------------------------
// Logic
// ----------------------------------------------------------------------------

bool Operators::eq(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a == b ? 1 : 0);
    return true;
}

bool Operators::ne(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a != b ? 1 : 0);
    return true;
}

bool Operators::gt(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a > b ? 1 : 0);
    return true;
}

bool Operators::ge(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a >= b ? 1 : 0);
    return true;
}

bool Operators::lt(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a < b ? 1 : 0);
    return true;
}

bool Operators::le(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a <= b ? 1 : 0);
    return true;
}

// ----------------------------------------------------------------------------
// Advanced logic
// ----------------------------------------------------------------------------

bool Operators::cmp(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b); // compare to this
    ctxt.stack_pop(ctxt, a); // value
    if (a < b) {
        ctxt.stack_push(ctxt, -1);
    }
    else if (a > b) {
        ctxt.stack_push(ctxt, 1);
    }
    else {
        ctxt.stack_push(ctxt, 0);
    }
    return true;
};

bool Operators::cmp3(rpn_stack& ctxt) {
    float a, b, c;
    ctxt.stack_pop(ctxt, c); // upper threshold
    ctxt.stack_pop(ctxt, b); // lower threshold
    ctxt.stack_pop(ctxt, a); // value
    if (a < b) {
        ctxt.stack_push(ctxt, -1);
    }
    else if (a > c) {
        ctxt.stack_push(ctxt, 1);
    }
    else {
        ctxt.stack_push(ctxt, 0);
    }
    return true;
};

bool Operators::index(rpn_stack& ctxt) {

    float tmp;

    // Number of values to map
    ctxt.stack_pop(ctxt, tmp);
    unsigned char num = int(tmp);
    if (0 == num) return false;

    // Get mapped values from stack
    if (ctxt.stack_size(ctxt) < num + 1) return false;
    float* values = new float[num];
    for (unsigned char i = 0; i < num; i++) {
        ctxt.stack_pop(ctxt, tmp);
        values[num - i - 1] = tmp;
    }

    // Get index
    ctxt.stack_pop(ctxt, tmp);
    unsigned char index = int(tmp);

    // Return indexed value
    if (index >= num) return false;
    ctxt.stack_push(ctxt, values[index]);
    delete[] values;
    return true;

};

bool Operators::map(rpn_stack& ctxt) {

    float value, from_low, from_high, to_low, to_high;
    ctxt.stack_pop(ctxt, to_high);
    ctxt.stack_pop(ctxt, to_low);
    ctxt.stack_pop(ctxt, from_high);
    ctxt.stack_pop(ctxt, from_low);
    ctxt.stack_pop(ctxt, value);

    if (from_high == from_low) return false;
    if (value < from_low) value = from_low;
    if (value > from_high) value = from_high;
    value = to_low + (value - from_low) * (to_high - to_low) / (from_high - from_low);
    ctxt.stack_push(ctxt, value);
    return true;

};

bool Operators::constrain(rpn_stack& ctxt) {
    float a, b, c;
    ctxt.stack_pop(ctxt, c); // upper threshold
    ctxt.stack_pop(ctxt, b); // lower threshold
    ctxt.stack_pop(ctxt, a); // value
    if (a < b) {
        ctxt.stack_push(ctxt, b);
    }
    else if (a > c) {
        ctxt.stack_push(ctxt, c);
    }
    else {
        ctxt.stack_push(ctxt, a);
    }
    return true;
};

// ----------------------------------------------------------------------------
// Boolean
// ----------------------------------------------------------------------------

bool Operators::and_(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, ((a != 0) & (b != 0)) ? 1 : 0);
    return true;
}

bool Operators::or_(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, ((a != 0) | (b != 0)) ? 1 : 0);
    return true;
}

bool Operators::xor_(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, ((a != 0) ^ (b != 0)) ? 1 : 0);
    return true;
}

bool Operators::not_(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a == 0 ? 1 : 0);
    return true;
}

// ----------------------------------------------------------------------------
// Casting
// ----------------------------------------------------------------------------

bool Operators::round(rpn_stack& ctxt) {

    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);

    unsigned char decimals = (int)b;
    unsigned long multiplier = 1;
    for (unsigned char i = 0; i < decimals; i++) {
        multiplier *= 10;
    }
    a = (float)(int(a * multiplier + 0.5)) / multiplier;

    ctxt.stack_push(ctxt, a);
    return true;

}

bool Operators::ceil(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, int(a) + (a == int(a) ? 0 : 1));
    return true;
}

bool Operators::floor(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, int(a));
    return true;
}

// ----------------------------------------------------------------------------
// Conditionals
// ----------------------------------------------------------------------------

bool Operators::ifn(rpn_stack& ctxt) {
    float a, b, c;
    ctxt.stack_pop(ctxt, c);
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, (a != 0) ? b : c);
    return true;
}

bool Operators::end(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    if (a != 0) return false;
    return true;
};

// ----------------------------------------------------------------------------
// Stack
// ----------------------------------------------------------------------------

bool Operators::dup(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a);
    ctxt.stack_push(ctxt, a);
    return true;
}

bool Operators::dup2(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a);
    ctxt.stack_push(ctxt, b);
    ctxt.stack_push(ctxt, a);
    ctxt.stack_push(ctxt, b);
    return true;
}

bool Operators::over(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, a);
    ctxt.stack_push(ctxt, b);
    ctxt.stack_push(ctxt, a);
    return true;
}

bool Operators::swap(rpn_stack& ctxt) {
    float a, b;
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, b);
    ctxt.stack_push(ctxt, a);
    return true;
}

bool Operators::unrot(rpn_stack& ctxt) {
    float a, b, c;
    ctxt.stack_pop(ctxt, c);
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, c);
    ctxt.stack_push(ctxt, a);
    ctxt.stack_push(ctxt, b);
    return true;
}

bool Operators::rot(rpn_stack& ctxt) {
    float a, b, c;
    ctxt.stack_pop(ctxt, c);
    ctxt.stack_pop(ctxt, b);
    ctxt.stack_pop(ctxt, a);
    ctxt.stack_push(ctxt, b);
    ctxt.stack_push(ctxt, c);
    ctxt.stack_push(ctxt, a);
    return true;
}

bool Operators::drop(rpn_stack& ctxt) {
    float a;
    ctxt.stack_pop(ctxt, a);
    return true;
}

bool Operators::depth(rpn_stack& ctxt) {
    ctxt.stack_push(ctxt, ctxt.stack_size(ctxt));
    return true;
}


