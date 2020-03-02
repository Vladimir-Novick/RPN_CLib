#pragma once

#include "pch.h"

#include "RPN_Utils.h"
#include "Types.h"

namespace RPN {

	using namespace std;

	class RPNProcessor
	{
	private:
		vector<RPNToken*> m_Tokens;
		vector<string> m_arguments;
		string m_expression;
		stack<RPNToken*> stackTranslation;
		vector<RPNToken*> RPN_Tokens;

		/// <summary>
		/// Makes the tokens.
		/// </summary>
		/// <param name="expr">The expr.</param>
		/// <param name="Tokens">The tokens.</param>
		/// <returns></returns>
		bool MakeTokens(string& expr, vector<RPNToken*>& Tokens);
		void ThrowException(std::string& tok, std::string& expr);

		void ClearMemory();
	public:


		/// <summary>
		/// Gets the existing tokens.
		/// </summary>
		/// <returns></returns>
		const vector<RPNToken*> GetExistingTokens() {
			return m_Tokens;
		}
		/// <summary>
		/// Gets the argument list.
		/// </summary>
		/// <returns></returns>
		const vector<string> GetArgumentList() {
			return m_arguments;
		}

		RPNProcessor(vector<RPNToken*>& Tokens);
		RPNProcessor(string& expr);
		~RPNProcessor();		

		/// <summary>
		/// Prepares this instance. Translatad to RPN notation
		/// </summary>
		/// <returns></returns>
		void Prepare();

		/// <summary>
		///   get all tokens without compilation.
		/// </summary>
		/// <returns></returns>
		void PrepareTokens();
		string GetTokens();
		string GetRPN_Tokens();

	};

}

