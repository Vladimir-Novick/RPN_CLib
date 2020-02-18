#include "pch.h"
#include "MatchUtils.h"
#include <string>

using namespace std;

///
/// This Boyer-Moore algorithm is more efficient 
/// for matching of long patterns on textual data.
///
int  MatchUtils::boyerMooreMatch(char S[], char P[])
{
	int n, m, i, j, lastch; 
	n = strlen(S); 
	m = strlen(P);
	i = m - 1;
	j = m - 1;
	while (i < n)
	{
		if (P[j] == S[i])
			if (j == 0) 	// first char of pattern
				return  i;
			else
			{
				j--;  i--;	//  go left
			}
		else		//  no match – find char in pattern
		{
			lastch = find(P, S[i]);
			if (lastch == -1) 	// not found
				i = i + m;		// jump over
			else
				i = i + j - lastch;	// align char
			j = m - 1;	// restart from right
		}
	}
	return  -1;	//  not matched
}

int MatchUtils::find(char P[], char ch) {
	int m = strlen(P)-2;
	for (int i = m; i >= 0; i--)
	{
		if (ch == P[i]) return i;
	}
	return -1;
}

