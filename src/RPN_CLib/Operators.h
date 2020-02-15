#pragma once
#include "pch.h"

#include "Types.h"
#include "OperationMath.h"
#include "RPN_Errors.h"
#include "Operators.h"
#include <map>

#define RPN_CONST_PI    3.141593
#define RPN_CONST_E     2.178282

class Operators
{
public:

	// ----------------------------------------------------------------------------
	// Constants
	// ----------------------------------------------------------------------------

	static bool pi(rpn_stack& ctxt);

	static bool e(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Math
	// ----------------------------------------------------------------------------

	static bool sum(rpn_stack& ctxt);

	static bool substract(rpn_stack& ctxt);

	static bool times(rpn_stack& ctxt);

	static bool divide(rpn_stack& ctxt);

	static bool mod(rpn_stack& ctxt);

	static bool abs(rpn_stack& ctxt);

	static bool sqrt(rpn_stack& ctxt);

	static bool log(rpn_stack& ctxt);

	static bool log10(rpn_stack& ctxt);

	static bool exp(rpn_stack& ctxt);

	static bool fmod(rpn_stack& ctxt);

	static bool pow(rpn_stack& ctxt);

	static bool cos(rpn_stack& ctxt);

	static bool sin(rpn_stack& ctxt);

	static bool tan(rpn_stack& ctxt);


	// ----------------------------------------------------------------------------
	// Logic
	// ----------------------------------------------------------------------------

	static bool eq(rpn_stack& ctxt);

	static bool ne(rpn_stack& ctxt);

	static bool gt(rpn_stack& ctxt);

	static bool ge(rpn_stack& ctxt);

	static bool lt(rpn_stack& ctxt);

	static bool le(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Advanced logic
	// ----------------------------------------------------------------------------

	static bool cmp(rpn_stack& ctxt);

	static bool cmp3(rpn_stack& ctxt);

	static bool index(rpn_stack& ctxt);

	static bool map(rpn_stack& ctxt);

	static bool constrain(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Boolean
	// ----------------------------------------------------------------------------

	static bool and_(rpn_stack& ctxt);

	static bool or_(rpn_stack & ctxt);

	static inline void stack_pop(rpn_stack& ctxt,float& b);

	static bool xor_(rpn_stack& ctxt);

	static bool not_(rpn_stack& ctxt);

	static bool floor(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Casting
	// ----------------------------------------------------------------------------

	static bool round(rpn_stack& ctxt);

	static bool ceil(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Conditionals
	// ----------------------------------------------------------------------------

	static bool ifn(rpn_stack& ctxt);

	bool end(rpn_stack& ctxt);

	// ----------------------------------------------------------------------------
	// Stack
	// ----------------------------------------------------------------------------

	static bool dup(rpn_stack& ctxt);

	static bool dup2(rpn_stack& ctxt);

	static bool over(rpn_stack& ctxt);

	static bool swap(rpn_stack& ctxt);

	static bool unrot(rpn_stack& ctxt);

	static bool rot(rpn_stack& ctxt);

	static bool drop(rpn_stack& ctxt);

	static bool depth(rpn_stack& ctxt);

	static bool none(rpn_stack& ctxt);

	static const ActionDictType Actions;

};

