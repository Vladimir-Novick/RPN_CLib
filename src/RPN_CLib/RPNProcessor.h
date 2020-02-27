#pragma once

#include "pch.h"

#include "RPN_Utils.h"
#include "Types.h"

namespace RPN {

	using namespace std;

	class RPNProcessor
	{
	private:
		list<RPNToken*> m_Tokens;
		list<string> m_arguments;
		string m_expression;

		/// <summary>
		/// Makes the tokens.
		/// </summary>
		/// <param name="expr">The expr.</param>
		/// <param name="Tokens">The tokens.</param>
		/// <returns></returns>
		bool MakeTokens(string& expr, list<RPNToken*>& Tokens);
		void ThrowException(std::string& tok, std::string& expr);
	public:


		/// <summary>
		/// Gets the existing tokens.
		/// </summary>
		/// <returns></returns>
		const list<RPNToken*> GetExistingTokens() {
			return m_Tokens;
		}
		/// <summary>
		/// Gets the argument list.
		/// </summary>
		/// <returns></returns>
		const list<string> GetArgumentList() {
			return m_arguments;
		}

		RPNProcessor(list<RPNToken*>& Tokens);
		RPNProcessor(string& expr);
		~RPNProcessor();		
		/// <summary>
		/// Clears the memory.
		/// </summary>
		void ClearMemory();
		/// <summary>
		/// Prepares this instance.
		/// </summary>
		/// <returns></returns>
		string Prepare();
		string GetRPN_String();
	};

}

