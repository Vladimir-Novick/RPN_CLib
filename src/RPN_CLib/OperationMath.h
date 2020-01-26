#pragma once

#include "Types.h"

class OperationMath
{
public:
	static double fs_sqrt(double x);

	static long double fs_powl(long double x, long double y);

	static double fs_log(double x);

	static double fs_exp2(double x);

	static double fs_log10(double x);

	static double fs_exp(double x);

	static double fs_modf(double value, double* iptr);

	static double fs_fmod(double x, double y);

	static double fs_pow(double x, double y);

	static double fs_pi(void);

	static double fs_cos(double x);

	static double fs_log2(double x);

	static long double fs_sqrtl(long double x);

	static long double fs_logl(long double x);

	static long double fs_expl(long double x);

	static long double fs_pil(void);

	static long double fs_cosl(long double x);

	static long double fs_fmodl(long double x, long double y);

};

