#include "pch.h"
#include "CppUnitTest.h"
#include "..\RPN_CLib\RPNProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RPN;
using namespace std;
namespace UnitTest
{
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
			auto ret = processor.PrepareTokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", ret);

			Assert::AreEqual("( ( 15 / ( 7 - ( A + 1 ) ) ) * 3 ) - ( B + ( 1 + 1 ) ) ", ret.c_str());

		};

		TEST_METHOD(PrepareTokens2)
		{
			string sourceString = "(a*b+c*d)/(a-d)+b*c";
			RPNProcessor processor(sourceString);
			auto ret = processor.PrepareTokens();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", ret);
			Assert::AreEqual("( a * b + c * d ) / ( a - d ) + b * c ", ret.c_str());

		};

	};

	TEST_CLASS(SimpleOperation)
	{
	public:

		void log(char* message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str() + "\n").c_str());
		}


		TEST_METHOD(Compile)
		{
			string sourceString = "(a*b+c*d)/(a-d)+b*c";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c d * + a d - / b c * + ", ret.c_str());
		};

		TEST_METHOD(Compile2)
		{
			string sourceString = "(a+b)/(c+d)";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b + c d + / ", ret.c_str());
		};


		TEST_METHOD(Compile3)
		{
			string sourceString = "a*b*c*d";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c * d * ", ret.c_str());
		};

		TEST_METHOD(Compile4)
		{
			string sourceString = "c*(a+b)/d";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("c a b + * d / ", ret.c_str());
		};

		TEST_METHOD(Compile5)
		{
			string sourceString = "(a*b+c)*d*(e/f)";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			Assert::AreEqual("a b * c + d * e f / * ", ret.c_str());
		};

		TEST_METHOD(Compile6)
		{
			string sourceString = "a+b*(c-d/(10+x)+y)-e";
			RPNProcessor processor(sourceString);
			auto tokens = processor.PrepareTokens();
			auto ret = processor.Prepare();

			log("Prepare Tokens > source: ", sourceString);
			log("Prepare Tokens > target: ", tokens);
			log("RPN String > target: ", ret);
			//Assert::AreEqual("a b * c + d * e f / * ", ret.c_str());
		};
	};
}
