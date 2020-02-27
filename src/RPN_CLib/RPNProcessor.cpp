#include "pch.h"
#include "RPNProcessor.h"
#include "Operators.h"
#include <list>

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

	using namespace std;


	RPNProcessor::RPNProcessor(list<RPNToken*>& Tokens) {
		m_expression = "";
		for (auto item = Tokens.begin(); item != Tokens.end(); item++) {
			RPNToken* newToken = new RPNToken();
			*newToken = *(*item);
			m_Tokens.push_back(newToken);
			if (newToken->m_sType = ALPHA) {
				m_arguments.push_back(newToken->m_sToken);
			}
		}
	}

	RPNProcessor::RPNProcessor(string& expr) {
		m_expression = expr;

	}

	RPNProcessor::~RPNProcessor() {
		ClearMemory();
	}

	void RPNProcessor::ClearMemory()
	{
		for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
			delete (*item);
		}
		m_Tokens.clear();
		m_arguments.clear();
	}


	bool RPNProcessor::MakeTokens(string& expr, list<RPNToken*>& Tokens)
	{
		int i = 0;
		string tok = "";
		RPNToken* token;

		bool IsGood = true;
		Tokens.clear();

		int expr_Length = expr.size();

		while (i <= expr_Length)
		{

			if (i > expr_Length - 1) { break; }



			if (RPN_Utils::IsWhiteSpace(expr[i]))
			{
				while (RPN_Utils::IsWhiteSpace(expr[i]))
				{
					i++;
					if (i > expr_Length - 1) { break; }
				}
			}

			if (i > expr_Length - 1) { break; }



			if (expr[i] == '\'')
			{
				tok = "";
				token = new RPNToken();

				while (!(expr[i] == '\''))
				{
					tok += expr[i];
					i++;
					if (i > expr_Length - 1)
					{
						delete token;
						ThrowException(tok, expr);
					}
				}
				if (i <= expr_Length - 1)
				{
					{
						tok += expr[i];
						i++;
					}
				}
				else {
					delete token;
					ThrowException(tok, expr);
				}
				token->m_sType = STRING;
				token->m_sToken = tok;
				Tokens.push_back(token);
			}

			if (i > expr_Length - 1) { break; }

			if (expr[i] == '[')
			{
				tok = "";
				token = new RPNToken();

				while (!(expr[i] == ']'))
				{
					tok += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				}
				if (i <= expr_Length - 1)
				{
					{
						tok += expr[i];
						i++;
					}
				}
				else {
					delete token;
					ThrowException(tok, expr);
				}
				token->m_sType = ALPHA;
				token->m_sToken = tok;
				Tokens.push_back(token);
			}

			if (i > expr_Length - 1) { break; }

			if (expr[i] == '"')
			{
				tok = "";
				token = new RPNToken();

				while (!(expr[i] == '"'))
				{
					tok += expr[i];
					i++;
					if (i > expr_Length - 1)
					{
						delete token;
						ThrowException(tok, expr);
					}
				}
				if (i <= expr_Length - 1)
				{
					{
						tok += expr[i];
						i++;
					}
				}
				else {
					delete token;
					ThrowException(tok, expr);
				}
				token->m_sType = STRING;
				token->m_sToken = tok;
				Tokens.push_back(token);
			}

			if (i > expr_Length - 1) { break; }

			if (isalpha(expr[i]))
			{
				tok = "";
				token = new RPNToken();

				token->m_sType = ALPHA;
				token->m_OperandType = VARIABLE;
				token->m_Operation = VARIABLE;
				token->m_sToken = tok;
				Tokens.push_back(token);

				while (isalpha(expr[i]) || (isdigit(expr[i]) || (expr[i] == '_')))
				{
					token->m_sToken += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				}

				if (i + 1 < expr_Length)
				{
					if (expr[i + 1] == '(')
					{
						tok += "$";

						token->m_sType = FUNCTION;
					}

				}

			}
			else if (isdigit(expr[i]))
			{
				tok = "";
				token = new RPNToken();

				token->m_sType = NUMBER;
				token->m_OperandType = ARIFMETICAL;
				Tokens.push_back(token);

				while (isdigit(expr[i]) || (expr[i] == '.'))
				{
					token->m_sToken += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				}



			}
			else if (i + 1 < expr_Length)
			{

				auto action = Operators::GetOperation(expr[i], expr[i + 1]);
				if (action.dataType != UNKNOWN)
				{
					tok = "";
					token = new RPNToken();

					tok = expr[i];
					if (action.isDoubleChar) {
						tok = tok + expr[i + 1];
						i++;
					}
					token->m_sType = OPERAND;
					token->m_sToken = tok;
					token->m_OperandType = ARIFMETICAL;
					token->m_Operation = action.dataType;
					Tokens.push_back(token);


					if (action.dataType != UNKNOWN)
					{

						if (token->m_Operation == MINUS_OPERATOR)
						{
							if (Tokens.size() == 0) {
								token->m_Operation = JUST_MINUS;
							}
							else {
								auto it = Tokens.back();
								if ((((it)->m_sType == OPERAND)))
								{
									token->m_Operation = JUST_MINUS;
								}
							}
						}
						if (token->m_Operation == PLUS_OPERATOR)
						{
							if (Tokens.size() == 0) {
								token->m_Operation = JUST_PLUS;
							}
							else {
								auto it = Tokens.back();
								if ((it)->m_sType == OPERAND)
								{
									token->m_Operation = JUST_PLUS;
								}
							}
						}

						i++;
						if (i > expr_Length - 1) { break; }
					}
					else
					{
						IsGood = false;
						tok = "";
						ThrowException(tok, expr);


					}
				}
			}
		}
		return IsGood;
	}

	void RPNProcessor::ThrowException(std::string& tok, std::string& expr)
	{
		ClearMemory();
		throw  RPNException(RPN_Utils::Format("Complie error: ", tok, expr).c_str());
	}



	string RPN::RPNProcessor::Prepare()
	{
		string ret = "";
		if (!m_expression.empty()) {
			ClearMemory();
			MakeTokens(m_expression, m_Tokens);
			m_arguments.clear();
			for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
				if ((*item)->m_sType = ALPHA) {
					m_arguments.push_back((*item)->m_sToken);
				}
			}
		}

		return GetRPN_String();

	}




	string RPN::RPNProcessor::GetRPN_String()
	{
		string ret;
		for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
			ret.append((*item)->m_sToken);
			ret.append(" ");
		}
		return ret;
	}

}
