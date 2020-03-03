#include "pch.h"
#include "CppUnitTest.h"
#include "..\RPN_CLib\RPNProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RPN;
using namespace std;
namespace UnitTest
{

	TEST_CLASS(LogicalOperation)
	{
	public:

		void log(char* message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str() + "\n").c_str());
		}

		TEST_METHOD(EQUAL)
		{
			string sourceString = "a=b";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b = ", ret.c_str());

		};

		TEST_METHOD(EQUAL_ARIFMETICAL)
		{
			string sourceString = "(a+b)=(c*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b + c k * = ", ret.c_str());

		};

		TEST_METHOD(EQUAL_ARIFMETICAL2)
		{
			string sourceString = "(a+b/l)==((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * == ", ret.c_str());

		};

		TEST_METHOD(NOT_EQUAL)
		{
			string sourceString = "a!=b";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b != ", ret.c_str());

		};

		TEST_METHOD(NOT_EQUAL2)
		{
			string sourceString = "a<>b";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b <> ", ret.c_str());

		};



		TEST_METHOD(NOT_EQUAL_ARIFMETICAL)
		{
			string sourceString = "(a+b)!=(c*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b + c k * != ", ret.c_str());

		};

		TEST_METHOD(NOT_EQUAL_ARIFMETICAL2)
		{
			string sourceString = "(a+b/l)<>((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * <> ", ret.c_str());

		};

		TEST_METHOD(GREATER)
		{
			string sourceString = "(a+b/l)>((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * > ", ret.c_str());

		};

		TEST_METHOD(GREATE_OR_EQUAL)
		{
			string sourceString = "(a+b/l)>=((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * >= ", ret.c_str());

		};

		TEST_METHOD(LESS)
		{
			string sourceString = "(a+b/l)<((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * < ", ret.c_str());

		};

		TEST_METHOD(LESS_OR_EQUAL)
		{
			string sourceString = "(a+b/l)<=((c+n)*k)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b l / + c n + k * <= ", ret.c_str());

		};


		TEST_METHOD(NOT)
		{
			string sourceString = "!(a>b)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b > ! ", ret.c_str());

		};

		TEST_METHOD(IF)
		{
			string sourceString = "(a>b)?(A-B)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b > ? A B - ", ret.c_str());

		};

		TEST_METHOD(IF_2)
		{
			string sourceString = "a>b?(A-B)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b > ? A B - ", ret.c_str());

		};


		TEST_METHOD(IF_3)
		{
			string sourceString = "a>b?A-B";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a b > ? A B - ", ret.c_str());

		};

		TEST_METHOD(IF_4)
		{
			string sourceString = "(a-23)>b?A-(B*20)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);

			Assert::AreEqual("a 23 - b > ? A B 20 * - ", ret.c_str());

		};

	};


	TEST_CLASS(GetTokens)
	{
	public:

		void log(char* message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str() + "\n").c_str());
		}

		TEST_METHOD(PrepareTokens)
		{
			string sourceString = "((15 / (7 - (A + 1))) * 3) - (B + (1 + 1))";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto ret = processor.GetTokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", ret);

			Assert::AreEqual("( ( 15 / ( 7 - ( A + 1 ) ) ) * 3 ) - ( B + ( 1 + 1 ) ) ", ret.c_str());

		};

		TEST_METHOD(PrepareTokens2)
		{
			string sourceString = "(a*b+c*d)/(a-d)+b*c";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto ret = processor.GetTokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", ret);
			Assert::AreEqual("( a * b + c * d ) / ( a - d ) + b * c ", ret.c_str());

		};

	};

	TEST_CLASS(SimpleARIFMETICAL)
	{
	public:

		void log(char* message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str() + "\n").c_str());
		}


		TEST_METHOD(Compile)
		{
			string sourceString = "(a*b+c*d)/(a-d)+b*c";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c d * + a d - / b c * + ", ret.c_str());
		};

		TEST_METHOD(Compile2)
		{
			string sourceString = "(a+b)/(c+d)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b + c d + / ", ret.c_str());
		};


		TEST_METHOD(Compile3)
		{
			string sourceString = "a*b*c*d";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c * d * ", ret.c_str());
		};

		TEST_METHOD(Compile4)
		{
			string sourceString = "c*(a+b)/d";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("c a b + * d / ", ret.c_str());
		};

		TEST_METHOD(Compile5)
		{
			string sourceString = "(a*b+c)*d*(e/f)";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c + d * e f / * ", ret.c_str());
		};

		TEST_METHOD(Compile6)
		{
			string sourceString = "a+b*(c-d/(10+x)+y)-e";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b c d 10 x + / - y + * + e - ", ret.c_str());
		};

		TEST_METHOD(JustMinus)
		{
			string sourceString = "-a+b*(-c-d/(-10+x)+y)-e";
			RPNProcessor processor(sourceString);
			processor.PrepareTokens();
			auto tokens = processor.GetTokens();
			processor.Prepare();
			auto ret = processor.GetRPN_Tokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			//Assert::AreEqual("a b * c + d * e f / * ", ret.c_str());
		};
	};
}
