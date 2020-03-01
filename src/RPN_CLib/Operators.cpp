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

namespace RPN {


	// ----------------------------------------------------------------------------
	// Constants
	// ----------------------------------------------------------------------------

	bool Operators::pi(rpn_stack& ctxt) {
		ctxt.push(RPN_CONST_PI);
		return true;
	}



	bool Operators::e(rpn_stack& ctxt) {
		ctxt.push(RPN_CONST_E);
		return true;
	}

	// ----------------------------------------------------------------------------
	// Math
	// ----------------------------------------------------------------------------

	bool Operators::sum(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a + b);
		return true;
	}

	bool Operators::substract(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a - b);
		return true;
	}

	bool Operators::times(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a * b);
		return true;
	}

	bool Operators::divide(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		if (0 == b) {
			return false;
		}
		ctxt.push(a / b);
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
		ctxt.push(mod);
		return true;
	}

	bool Operators::abs(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		if (a < 0) a = -a;
		ctxt.push(a);
		return true;
	}



	bool Operators::sqrt(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(OperationMath::fs_sqrt(a));
		return true;
	}

	bool Operators::log(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		if (0 >= a) {
			return false;
		}
		ctxt.push(OperationMath::fs_log(a));
		return true;
	}

	bool Operators::log10(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		if (0 >= a) {
			return false;
		}
		ctxt.push(OperationMath::fs_log10(a));
		return true;
	}

	bool Operators::exp(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(OperationMath::fs_exp(a));
		return true;
	}

	bool Operators::fmod(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		if (0 == b) {
			return false;
		}
		ctxt.push(OperationMath::fs_fmod(a, b));
		return true;
	}

	bool Operators::pow(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(OperationMath::fs_pow(a, b));
		return true;
	}

	bool Operators::cos(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(OperationMath::fs_cos(a));
		return true;
	}

	bool Operators::sin(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		float cos = OperationMath::fs_cos(a);
		float sin = OperationMath::fs_sqrt(1 - cos * cos);
		ctxt.push(sin);
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
		ctxt.push(sin / cos);
		return true;
	}


	// ----------------------------------------------------------------------------
	// Logic
	// ----------------------------------------------------------------------------

	bool Operators::eq(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a == b ? 1 : 0);
		return true;
	}

	bool Operators::ne(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a != b ? 1 : 0);
		return true;
	}

	bool Operators::gt(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a > b ? 1 : 0);
		return true;
	}

	bool Operators::ge(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a >= b ? 1 : 0);
		return true;
	}

	bool Operators::lt(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a < b ? 1 : 0);
		return true;
	}

	bool Operators::le(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a <= b ? 1 : 0);
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
			ctxt.push(-1);
		}
		else if (a > b) {
			ctxt.push(1);
		}
		else {
			ctxt.push(0);
		}
		return true;
	};

	bool Operators::cmp3(rpn_stack& ctxt) {
		float a, b, c;
		stack_pop(ctxt, c); // upper threshold
		stack_pop(ctxt, b); // lower threshold
		stack_pop(ctxt, a); // value
		if (a < b) {
			ctxt.push(-1);
		}
		else if (a > c) {
			ctxt.push(1);
		}
		else {
			ctxt.push(0);
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
		ctxt.push(values[index]);
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
		ctxt.push(value);
		return true;

	};

	bool Operators::constrain(rpn_stack& ctxt) {
		float a, b, c;
		stack_pop(ctxt, c); // upper threshold
		stack_pop(ctxt, b); // lower threshold
		stack_pop(ctxt, a); // value
		if (a < b) {
			ctxt.push(b);
		}
		else if (a > c) {
			ctxt.push(c);
		}
		else {
			ctxt.push(a);
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
		ctxt.push(((a != 0) & (b != 0)) ? 1 : 0);
		return true;
	}

	bool Operators::or_(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(((a != 0) | (b != 0)) ? 1 : 0);
		return true;
	}

	void  Operators::stack_pop(rpn_stack& ctxt,float& b)
	{
		b = ctxt.top();
		ctxt.pop();
	}

	bool Operators::xor_(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(((a != 0) ^ (b != 0)) ? 1 : 0);
		return true;
	}

	bool Operators::not_(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(a == 0 ? 1 : 0);
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

		ctxt.push(a);
		return true;

	}

	bool Operators::ceil(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(int(a) + (a == int(a) ? 0 : 1));
		return true;
	}

	bool Operators::floor(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		ctxt.push(int(a));
		return true;
	}


	bool Operators::ifn(rpn_stack& ctxt) {
		float a, b, c;
		stack_pop(ctxt, c);
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push((a != 0) ? b : c);
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
		ctxt.push(a);
		ctxt.push(a);
		return true;
	}

	bool Operators::dup2(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a);
		ctxt.push(b);
		ctxt.push(a);
		ctxt.push(b);
		return true;
	}

	bool Operators::over(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(a);
		ctxt.push(b);
		ctxt.push(a);
		return true;
	}

	bool Operators::swap(rpn_stack& ctxt) {
		float a, b;
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(b);
		ctxt.push(a);
		return true;
	}

	bool Operators::unrot(rpn_stack& ctxt) {
		float a, b, c;
		stack_pop(ctxt, c);
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(c);
		ctxt.push(a);
		ctxt.push(b);
		return true;
	}

	bool Operators::rot(rpn_stack& ctxt) {
		float a, b, c;
		stack_pop(ctxt, c);
		stack_pop(ctxt, b);
		stack_pop(ctxt, a);
		ctxt.push(b);
		ctxt.push(c);
		ctxt.push(a);
		return true;
	}

	bool Operators::drop(rpn_stack& ctxt) {
		float a;
		stack_pop(ctxt, a);
		return true;
	}


	bool Operators::depth(rpn_stack& ctxt) {
		ctxt.push(ctxt.size());
		return true;
	}

	bool Operators::none(rpn_stack& ctxt) {

		return true;
	}

	ActionType Operators::GetOperation(char& c, char& c2) {
		string f;
		f.push_back(c);
		f.push_back(c2);
		auto rez = Actions.find(f);
		if (rez == Actions.end()) {
			f.clear();
			f.push_back(c);
			rez = Actions.find(f);
		}
		if (rez != Actions.end()) {
			return rez->second;
		}
		return { "(",0 , none,0,UNKNOWN,false };
	}

	const int Operators::traslTable[6][7] = {
//   V ( + - * /  )
	{0,1,1,1,1,1,-1}, // V
	{-1,1,1,1,1,1,3}, // (
	{4,1,2,2,1,1,4},  // +
	{4,1,2,2,1,1,4},  // -
	{4,1,4,4,2,2,4},  // *
	{4,1,4,4,2,2,4}   // /
	};

	const ActionDictType Operators::Actions =
	{
		{"(",{"(",0 , none,1,START_TPARENTHESES,false}},
		{"+",{"+", 2, sum,2,PLUS_OPERATOR,false}},
		{"-",{"-", 2, substract,3,MINUS_OPERATOR,false}},
		{"*",{"*", 2, times,4,MULITIPLY,false}},
		{"/",{"/", 2, divide,5,DIVIDE,false}},
		{")",{")",0 , none,6,END_PARENTHESES,false}},
		{"=",{"=", 2, eq,9,EQUAL,false}},
		{"==",{"==", 2, eq,10,EQUAL,true}},


		{">",{">", 2, gt,11,GREATER,false}},
		{">=",{">=", 2, ge,12,GREATE_OR_EQUAL,false}},
		{"<",{"<", 2, lt,13,LESS,false}},
		{"<=",{"<=", 2, le,14,LESS_OR_EQUAL,true}},
		{"<>",{"<>", 2, ne,15,NOT_EQUAL,true}},
		{"!=",{"!=", 2, ne,16,NOT_EQUAL,true}},


		{"^",{"^", 1, exp,17,EXPONENTIATION,false}},
		{"&&",{"&&", 2, and_,18,AND_OPERATOR,true}},
		{"||",{"||", 2, or_,19,OR_OPERATOR,true}},
		{"!",{"!", 1, not_,20,NOT_OPERATOR,false}},
	};


	const ActionType Operators::JUST_MINUS_ACTION = {"-", 7, substract,3,JUST_MINUS,false} ;
	const ActionType Operators::JUST_PLUS_ACTION = { "+", 8, sum,2,JUST_PLUS,false };
	const ActionType Operators::VARIABLE_ACTION = { "", 2, none,0,UNKNOWN,false };

	const ActionDictType Operators::Functions = {


		{"mod",{"mod", 2, mod,0,UNKNOWN,false}},
		{"abs",{"abs", 1, abs,0,UNKNOWN,false}},
		{"pi",{"pi", 0, pi,0,UNKNOWN,false}},
		{"e",{"e", 0, e,0,UNKNOWN,false}},
		{"round",{"round", 2, round,0,UNKNOWN,false}},
		{"ceil",{"ceil", 1, ceil,0,UNKNOWN,false}},
		{"floor",{"floor", 1, floor,0,UNKNOWN,false}},
		{"sqrt",{"sqrt", 1, sqrt,0,UNKNOWN,false}},
		{"log",{"log", 1, log,0,UNKNOWN,false}},
		{"log10",{"log10", 1, log10,0,UNKNOWN,false}},
		{"exp",{"exp", 1, exp,0,UNKNOWN,false}},
		{"fmod",{"fmod", 2, fmod,0,UNKNOWN,false}},
		{"pow",{"pow", 2, pow,0,UNKNOWN,false}},
		{"cos",{"cos", 1, cos,0,UNKNOWN,false}},
		{"sin",{"sin", 1, sin,0,UNKNOWN,false}},
		{"tan",{"tan", 1, tan,0,UNKNOWN,false}},

		{"cmp",{"cmp", 2, cmp,0,UNKNOWN,false}},
		{"cmp3",{"cmp3", 3, cmp3,0,UNKNOWN,false}},
		{"index",{"index", 1, index,0,UNKNOWN,false}},
		{"map",{"map", 5, map,0,UNKNOWN,false}},
		{"constrain",{"constrain", 3, constrain,0,UNKNOWN,false}},

		{"dup",{"dup", 1, dup,0,UNKNOWN,false}},
		{"dup2",{"dup2", 2, dup2,0,UNKNOWN,false}},
		{"swap",{"swap", 2, swap,0,UNKNOWN,false}},
		{"rot",{"rot", 3, rot,0,UNKNOWN,false}},
		{"unrot",{"unrot", 3, unrot,0,UNKNOWN,false}},
		{"drop",{"drop", 1, drop,0,UNKNOWN,false}},
		{"over",{"over", 2, over,0,UNKNOWN,false}},
		{"depth",{"depth", 0, depth,0,UNKNOWN,false}},

		{"ifn",{"ifn", 3, ifn}}

	};
}

