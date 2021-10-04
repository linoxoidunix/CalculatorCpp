#include "pch.h"
#include "CppUnitTest.h"
#include "../CalculatorCPlus/Calculator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestOfCalculator
{
	TEST_CLASS(UnitTestOfCalculator)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("1 + 2") == 3);
			Assert::IsTrue(myCalculator("1 - 2") == -1);
			Assert::IsTrue(myCalculator("1 + 2 + 3") == 6);

		}

		TEST_METHOD(TestMethod2)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("1 - 2") == -1);
		}

		TEST_METHOD(TestMethod3)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 1 * 45 - 2") == 43);
		}

		TEST_METHOD(TestMethod4)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 45") == 45);
		}

		TEST_METHOD(TestMethod5)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("12 / 4 * 3 - 6 * 3 / 2") == 0);
		}

		TEST_METHOD(TestMethod6)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- 3") == -3);
		}

		TEST_METHOD(TestMethod7)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - 3 - - 2") == 5);
		}

		TEST_METHOD(TestMethod8)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - 3 - - - 2") == 1);
		}

		TEST_METHOD(TestMethod9)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - 3 * - - - - 2 + 1") == 7);
		}

		TEST_METHOD(TestMethod10)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - 3 * - - - - 2 + + 1") == 7);
		}

		TEST_METHOD(TestMethod11)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - 3 * - - - - 2 + + - - + 1") == 7);
		}

		TEST_METHOD(TestMethod12)
		{
			Calculator myCalculator;
			Assert::IsTrue(myCalculator("- - + + - - + + + + 12 / - - + + - - 4 * + - - 3 - - - 6 * - - 3 / - - 2 + + - - + 45") == 45);
		}


	};
}
