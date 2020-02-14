#include "pch.h"
#include "Types.h"
#include "Operators.h"
#include <initializer_list>

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
	ctxt.push( RPN_CONST_PI);
	return true;
}



bool Operators::e(rpn_stack& ctxt) {
	ctxt.push( RPN_CONST_E);
	return true;
}

// ----------------------------------------------------------------------------
// Math
// ----------------------------------------------------------------------------

bool Operators::sum(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a + b);
	return true;
}

bool Operators::substract(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a - b);
	return true;
}

bool Operators::times(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a * b);
	return true;
}

bool Operators::divide(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	if (0 == b) {
		return false;
	}
	ctxt.push( a / b);
	return true;
}

bool Operators::mod(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	a = (int)a;
	b = (int)b;
	if (0 == b) {
		return false;
	}
	float mod = a - (int)(a / b) * b;
	ctxt.push( mod);
	return true;
}

bool Operators::abs(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	if (a < 0) a = -a;
	ctxt.push( a);
	return true;
}



bool Operators::sqrt(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( OperationMath::fs_sqrt(a));
	return true;
}

bool Operators::log(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	if (0 >= a) {
		return false;
	}
	ctxt.push( OperationMath::fs_log(a));
	return true;
}

bool Operators::log10(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	if (0 >= a) {
			return false;
	}
	ctxt.push( OperationMath::fs_log10(a));
	return true;
}

bool Operators::exp(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( OperationMath::fs_exp(a));
	return true;
}

bool Operators::fmod(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	if (0 == b) {
		return false;
	}
	ctxt.push( OperationMath::fs_fmod(a, b));
	return true;
}

bool Operators::pow(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( OperationMath::fs_pow(a, b));
	return true;
}

bool Operators::cos(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( OperationMath::fs_cos(a));
	return true;
}

bool Operators::sin(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	float cos = OperationMath::fs_cos(a);
	float sin = OperationMath::fs_sqrt(1 - cos * cos);
	ctxt.push( sin);
	return true;
}

bool Operators::tan(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	float cos = OperationMath::fs_cos(a);
	if (0 == cos) {
		return false;
	}
	float sin = OperationMath::fs_sqrt(1 - cos * cos);
	ctxt.push( sin / cos);
	return true;
}


// ----------------------------------------------------------------------------
// Logic
// ----------------------------------------------------------------------------

bool Operators::eq(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a == b ? 1 : 0);
	return true;
}

bool Operators::ne(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a != b ? 1 : 0);
	return true;
}

bool Operators::gt(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a > b ? 1 : 0);
	return true;
}

bool Operators::ge(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a >= b ? 1 : 0);
	return true;
}

bool Operators::lt(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a < b ? 1 : 0);
	return true;
}

bool Operators::le(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a <= b ? 1 : 0);
	return true;
}

// ----------------------------------------------------------------------------
// Advanced logic
// ----------------------------------------------------------------------------

bool Operators::cmp(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b); // compare to this
	stack_pop(ctxt, a); // value
	if (a < b) {
		ctxt.push( -1);
	}
	else if (a > b) {
		ctxt.push( 1);
	}
	else {
		ctxt.push( 0);
	}
	return true;
};

bool Operators::cmp3(rpn_stack& ctxt) {
	float a, b, c;
	stack_pop(ctxt, c); // upper threshold
	stack_pop(ctxt, b); // lower threshold
	stack_pop(ctxt, a); // value
	if (a < b) {
		ctxt.push( -1);
	}
	else if (a > c) {
		ctxt.push( 1);
	}
	else {
		ctxt.push( 0);
	}
	return true;
};

bool Operators::index(rpn_stack& ctxt) {

	float tmp;

	// Number of values to map
	stack_pop(ctxt, tmp);
	unsigned char num = int(tmp);
	if (0 == num) return false;

	// Get mapped values from stack
	if (ctxt.size() < num + 1) return false;
	float* values = new float[num];
	for (unsigned char i = 0; i < num; i++) {
		stack_pop(ctxt, tmp);
		values[num - i - 1] = tmp;
	}

	// Get index
	stack_pop(ctxt, tmp);
	unsigned char index = int(tmp);

	// Return indexed value
	if (index >= num) return false;
	ctxt.push( values[index]);
	delete[] values;
	return true;

};

bool Operators::map(rpn_stack& ctxt) {

	float value, from_low, from_high, to_low, to_high;
	stack_pop(ctxt, to_high);
	stack_pop(ctxt, to_low);
	stack_pop(ctxt, from_high);
	stack_pop(ctxt, from_low);
	stack_pop(ctxt, value);

	if (from_high == from_low) return false;
	if (value < from_low) value = from_low;
	if (value > from_high) value = from_high;
	value = to_low + (value - from_low) * (to_high - to_low) / (from_high - from_low);
	ctxt.push( value);
	return true;

};

bool Operators::constrain(rpn_stack& ctxt) {
	float a, b, c;
	stack_pop(ctxt, c); // upper threshold
	stack_pop(ctxt, b); // lower threshold
	stack_pop(ctxt, a); // value
	if (a < b) {
		ctxt.push( b);
	}
	else if (a > c) {
		ctxt.push( c);
	}
	else {
		ctxt.push( a);
	}
	return true;
};

// ----------------------------------------------------------------------------
// Boolean
// ----------------------------------------------------------------------------

bool Operators::and_(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( ((a != 0) & (b != 0)) ? 1 : 0);
	return true;
}

bool Operators::or_(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt,b);
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( ((a != 0) | (b != 0)) ? 1 : 0);
	return true;
}

inline void stack_pop(float& b, rpn_stack& ctxt)
{
	b = ctxt.top();
	ctxt.pop();
}

bool Operators::xor_(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( ((a != 0) ^ (b != 0)) ? 1 : 0);
	return true;
}

bool Operators::not_(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( a == 0 ? 1 : 0);
	return true;
}

// ----------------------------------------------------------------------------
// Casting
// ----------------------------------------------------------------------------

bool Operators::round(rpn_stack& ctxt) {

	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);

	unsigned char decimals = (int)b;
	unsigned long multiplier = 1;
	for (unsigned char i = 0; i < decimals; i++) {
		multiplier *= 10;
	}
	a = (float)(int(a * multiplier + 0.5)) / multiplier;

	ctxt.push( a);
	return true;

}

bool Operators::ceil(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( int(a) + (a == int(a) ? 0 : 1));
	return true;
}

bool Operators::floor(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( int(a));
	return true;
}


bool Operators::ifn(rpn_stack& ctxt) {
	float a, b, c;
	stack_pop(ctxt, c);
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( (a != 0) ? b : c);
	return true;
}

bool Operators::end(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	if (a != 0) return false;
	return true;
};

// ----------------------------------------------------------------------------
// Stack
// ----------------------------------------------------------------------------

bool Operators::dup(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	ctxt.push( a);
	ctxt.push( a);
	return true;
}

bool Operators::dup2(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a);
	ctxt.push( b);
	ctxt.push( a);
	ctxt.push( b);
	return true;
}

bool Operators::over(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( a);
	ctxt.push( b);
	ctxt.push( a);
	return true;
}

bool Operators::swap(rpn_stack& ctxt) {
	float a, b;
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( b);
	ctxt.push( a);
	return true;
}

bool Operators::unrot(rpn_stack& ctxt) {
	float a, b, c;
	stack_pop(ctxt, c);
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( c);
	ctxt.push( a);
	ctxt.push( b);
	return true;
}

bool Operators::rot(rpn_stack& ctxt) {
	float a, b, c;
	stack_pop(ctxt, c);
	stack_pop(ctxt, b);
	stack_pop(ctxt, a);
	ctxt.push( b);
	ctxt.push( c);
	ctxt.push( a);
	return true;
}

bool Operators::drop(rpn_stack& ctxt) {
	float a;
	stack_pop(ctxt, a);
	return true;
}


bool Operators::depth(rpn_stack& ctxt) {
	ctxt.push( ctxt.size());
	return true;
}

const ActionDictType Operators::Actions =
{
    {"pi",{"pi", 0, pi}},
	{"e",{"e", 0, e}},

    {"+",{"+", 2, sum}},
	{"-",{"-", 2, substract}},
	{"*",{"*", 2, times}},
	{"/",{"/", 2, divide}},
	{"mod",{"mod", 2, mod}},
	{"abs",{"abs", 1, abs}},

	{"round",{"round", 2, round}},
	{"ceil",{"ceil", 1, ceil}},
	{"floor",{"floor", 1, floor}},
	{"sqrt",{"sqrt", 1, sqrt}},
	{"log",{"log", 1, log}},
	{"log10",{"log10", 1, log10}},
	{"exp",{"exp", 1, exp}},
	{"fmod",{"fmod", 2, fmod}},
	{"pow",{"pow", 2, pow}},
	{"cos",{"cos", 1, cos}},
	{"sin",{"sin", 1, sin}},
	{"tan",{"tan", 1, tan}},

	{"eq",{"eq", 2, eq}},
	{"ne",{"ne", 2, ne}},
	{"gt",{"gt", 2, gt}},
	{"ge",{"ge", 2, ge}},
	{"lt",{"lt", 2, lt}},
	{"le",{"le", 2, le}},

	{"cmp",{"cmp", 2, cmp}},
	{"cmp3",{"cmp3", 3, cmp3}},
	{"index",{"index", 1, index}},
	{"map",{"map", 5, map}},
	{"constrain",{"constrain", 3, constrain}},

	// Boolean
	{"and",{"and", 2, and_}},
	{"or",{"or", 2, or_}},
	{"xor",{"xor", 2, xor_}},
	{"not",{"not", 1, not_}},


	{"dup",{"dup", 1, dup}},
	{"dup2",{"dup2", 2, dup2}},
	{"swap",{"swap", 2, swap}},
	{"rot",{"rot", 3, rot}},
	{"unrot",{"unrot", 3, unrot}},
	{"drop",{"drop", 1, drop}},
	{"over",{"over", 2, over}},
	{"depth",{"depth", 0, depth}},

	{"ifn",{"ifn", 3, ifn}}

};

