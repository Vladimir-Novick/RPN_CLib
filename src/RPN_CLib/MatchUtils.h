#pragma once

namespace RPN {


	class MatchUtils
	{
	public:
		int  find(char P[], char  ch);

		int boyerMooreMatch(char S[], char P[]);
	};
}