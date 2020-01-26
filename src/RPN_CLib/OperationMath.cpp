#include "pch.h"
#include "OperationMath.h"

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

using namespace std;

double OperationMath::fs_sqrt(double x)
{
	int n;
	double a, b;

	return sqrt(x);

}

double OperationMath::fs_log(double x)
{
	return log(x);

}

double OperationMath::fs_log10(double x)
{
	return log10(x);
}

double OperationMath::fs_exp(double x)
{
	return exp(x);
}

double OperationMath::fs_modf(double value, double* iptr)
{

	return modf(value, iptr);
}

double OperationMath::fs_fmod(double x, double y)
{
	return fmod(x, y);
}

double OperationMath::fs_pow(double x, double y)
{
	return pow(x, y);
}

double OperationMath::fs_pi(void)
{
	unsigned n;
	double a, b, epsilon;
	static double p;
	static int initialized;

	if (!initialized) {
		initialized = 1;
		epsilon = DBL_EPSILON / 4;
		n = 1;
		a = 3;
		do {
			a /= 9;
			b = a / n;
			n += 2;
			a /= 9;
			b -= a / n;
			n += 2;
			p += b;
		} while (b > epsilon);
		epsilon = DBL_EPSILON / 2;
		n = 1;
		a = 2;
		do {
			a /= 4;
			b = a / n;
			n += 2;
			a /= 4;
			b -= a / n;
			n += 2;
			p += b;
		} while (b > epsilon);
		p *= 4;
	}
	return p;
}

double OperationMath::fs_cos(double x)
{

	return cos(x);


}

double OperationMath::fs_log2(double x)
{
	return log2(x);
}

double OperationMath::fs_exp2(double x)
{
	return exp2(x);
}

long double OperationMath::fs_powl(long double x, long double y)
{

	return powl(x, y);
}

long double OperationMath::fs_sqrtl(long double x)
{
	return sqrtl( x);
	
}

long double OperationMath::fs_logl(long double x)
{
	return logl( x);
	

}

long double OperationMath::fs_expl(long double x)
{
	return expl(x);

}

long double OperationMath::fs_pil(void)
{
	long unsigned n;
	long double a, b, epsilon;
	static long double p;
	static int initialized;

	if (!initialized) {
		initialized = 1;
		epsilon = LDBL_EPSILON / 4;
		n = 1;
		a = 3;
		do {
			a /= 9;
			b = a / n;
			n += 2;
			a /= 9;
			b -= a / n;
			n += 2;
			p += b;
		} while (b > epsilon);
		epsilon = LDBL_EPSILON / 2;
		n = 1;
		a = 2;
		do {
			a /= 4;
			b = a / n;
			n += 2;
			a /= 4;
			b -= a / n;
			n += 2;
			p += b;
		} while (b > epsilon);
		p *= 4;
	}
	return p;
}

long double OperationMath::fs_cosl(long double x)
{
	return cosl(x);
}

long double OperationMath::fs_fmodl(long double x, long double y)
{
	return fmodl(x, y);
}
