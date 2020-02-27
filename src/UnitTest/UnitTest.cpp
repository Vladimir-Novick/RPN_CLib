#include "pch.h"
#include "CppUnitTest.h"
#include "RPNProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RPN;
using namespace std;
namespace UnitTest
{
	TEST_CLASS(Compiler)
	{
	public:

		void log(char *message, string dat) {
			Logger::WriteMessage((string(message) + dat.c_str()).c_str());
		}
		
		TEST_METHOD(Prepare)
		{
			string sourceString = "((15 / (7 - (A + 1))) * 3) - (B + (1 + 1)) ";
			RPNProcessor processor(sourceString);
			auto ret = processor.Prepare();
			
			log("prepare > source:", sourceString);
			log("prepare > target:", ret);
			

		}
	};
}
