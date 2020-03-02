#include "pch.h"
#include "RPNProcessor.h"
#include "Operators.h"
#include <list>
#include <Windows.h>
#include <string>       // std::string
 

#ifdef _DEBUG
#include <stdio.h>
#include <wchar.h>
#include <iostream>     // std::cout
#include <sstream>   
#endif

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


	RPNProcessor::RPNProcessor(vector<RPNToken*>& Tokens) {
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

		while (!stackTranslation.empty()) {
			stackTranslation.pop();
		}

		RPN_Tokens.clear();

	}


	bool RPNProcessor::MakeTokens(string& expr, vector<RPNToken*>& Tokens)
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


				do {
					tok += expr[i];
					i++;
					if (i > expr_Length - 1)
					{
						delete token;
						ThrowException(tok, expr);
					}
				} while (!(expr[i] == '\''));
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
				token->m_Action = Operators::VARIABLE_ACTION;
				token->m_sToken = tok;
				Tokens.push_back(token);
				continue;
			}


			if (expr[i] == '[')
			{
				tok = "";
				token = new RPNToken();

				do
				{
					tok += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				} while (!(expr[i] == ']'));

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
				token->m_Action = Operators::VARIABLE_ACTION;
				token->m_sToken = tok;
				Tokens.push_back(token);
				continue;
			}


			if (expr[i] == '"')
			{
				tok = "";
				token = new RPNToken();

				do
				{
					tok += expr[i];
					i++;
					if (i > expr_Length - 1)
					{
						delete token;
						ThrowException(tok, expr);
					}
				} while ((expr[i] != '"'));

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
				token->m_Action = Operators::VARIABLE_ACTION;
				Tokens.push_back(token);
				continue;
			}



			if (isalpha(expr[i]))
			{
				tok = "";
				token = new RPNToken();

				token->m_sType = ALPHA;
				token->m_OperandType = VARIABLE;
				token->m_Action = Operators::VARIABLE_ACTION;
				token->m_sToken = tok;
				Tokens.push_back(token);

				do
				{
					token->m_sToken += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				} while (isalpha(expr[i]) || (isdigit(expr[i]) || (expr[i] == '_')));

				if (i + 1 < expr_Length)
				{
					if (expr[i + 1] == '(')
					{
						tok += "$";

						token->m_sType = FUNCTION;
					}

				}
				continue;
			}

			if (isdigit(expr[i]))
			{
				tok = "";
				token = new RPNToken();

				token->m_sType = NUMBER;
				token->m_OperandType = ARIFMETICAL;
				Tokens.push_back(token);

				do
				{
					token->m_sToken += expr[i];
					i++;
					if (i > expr_Length - 1) { break; }
				} while (isdigit(expr[i]) || (expr[i] == '.'));


				continue;
			}

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
				token->m_Action = action;



				if (action.dataType != UNKNOWN)
				{

					if (token->m_Action.dataType == MINUS_OPERATOR)
					{
						if (Tokens.size() == 0) {
							token->m_sToken = "~";
							token->m_Action = Operators::JUST_MINUS_ACTION;
						}
						else {
							auto it = Tokens.back();
							
							if (((it->m_sType == OPERAND && it->m_Action.dataType != END_PARENTHESES)))
							{   token->m_sToken = "~";
								token->m_Action = Operators::JUST_MINUS_ACTION;
							}
						}
					}
					if (token->m_Action.dataType == PLUS_OPERATOR)
					{
						if (Tokens.size() == 0) {
							token->m_Action = Operators::JUST_PLUS_ACTION;
							
						}
						else {
							auto it = Tokens.back();
							if ((it)->m_sType == OPERAND)
							{
								
								token->m_Action = Operators::JUST_PLUS_ACTION;
							}
						}
					}

					Tokens.push_back(token);
					i++;
					if (i > expr_Length - 1) { break; }
					continue;
				}
				else
				{
					IsGood = false;
					tok = "";
					ThrowException(tok, expr);


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



	void RPN::RPNProcessor::Prepare()
	{
		string ret = "";
		RPNToken* t1;
		RPNToken* action;
		if (!m_expression.empty()) {
			ClearMemory();
			MakeTokens(m_expression, m_Tokens);
			int tableRow = 0;

			int act;
			bool exit = false;
			int indexSourseToken = -1;
			int tableColumn = 0;
			while (!exit) {
				 tableColumn = 0;
#ifdef _DEBUG

				 string action_m_sToken = "V";
#endif
				if (indexSourseToken+1 < m_Tokens.size()) {
					indexSourseToken++;
					action = m_Tokens.at(indexSourseToken);

#ifdef _DEBUG
					action_m_sToken = action->m_sToken.c_str();
#endif

					if (action->m_sType != OPERAND) {
						RPN_Tokens.push_back(action);
						continue;
					}
					tableColumn = action->m_Action.index;
				}
				do {

				

					if (!stackTranslation.empty()) {
						auto stackTop = stackTranslation.top();
						tableRow = stackTop->m_Action.index;
					}
					else {
						tableRow = 0;
					}

					act = Operators::traslTable[tableRow][tableColumn];

					if (act == 0) {
						exit = true;
						break;
					}
#ifdef _DEBUG
					auto stack2 = stackTranslation;
					stringstream stack_str;
					stack_str << "V ";
					while (!stack2.empty()) {
						auto top = stack2.top();
						stack2.pop();
						stack_str << top->m_sToken;
						stack_str << " ";
					}
					while (stack_str.str().length() < 10) {
						stack_str << " ";
					}

					string trans = GetRPN_Tokens();

					CHAR  s[512];

					sprintf_s(s, "%s   input: %s , Row : %d , Column %d, operation : %d , rezult : %s\n",
						stack_str.str().c_str(), action_m_sToken.c_str(), tableRow, tableColumn, act, trans.c_str());
					OutputDebugStringA(s);
#endif // _DEBUG



					switch (act)
					{
					case 1:
						stackTranslation.push(action);
						break;
					case 2:
					  t1 = stackTranslation.top();
					          stackTranslation.pop();
							  RPN_Tokens.push_back(t1);
							  stackTranslation.push(action);
						break;
					case 3:
						stackTranslation.pop();
						break;
					case 4:
						t1 = stackTranslation.top();
						stackTranslation.pop();
						RPN_Tokens.push_back(t1);
						break;
					case -1: // Error
						break;
					default:
						break;
					}

#ifdef _DEBUG
					CHAR  s2[512];
					 auto trans2 = GetRPN_Tokens();

					sprintf_s(s2, "                                                rezult : %s\n",	 trans2.c_str());
					OutputDebugStringA(s2);
#endif // _DEBUG

				} while (act == 4);

			}

			m_arguments.clear();
			for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
				if ((*item)->m_sType = ALPHA) {
					m_arguments.push_back((*item)->m_sToken);
				}
			}
		}


	}


	void RPN::RPNProcessor::PrepareTokens()
	{
		string ret = "";
		if (!m_expression.empty()) {
			ClearMemory();
			MakeTokens(m_expression, m_Tokens);
		}


	}



	string RPN::RPNProcessor::GetTokens()
	{
		string ret = "";
		for (auto item = m_Tokens.begin(); item != m_Tokens.end(); item++) {
			ret.append((*item)->m_sToken);
			ret.append(" ");
		}
		return ret;
	}

	string RPN::RPNProcessor::GetRPN_Tokens()
	{
		string ret ="";
		for (auto item = RPN_Tokens.begin(); item != RPN_Tokens.end(); item++) {
			ret.append((*item)->m_sToken);
			ret.append(" ");
		}
		return ret;
	}





}