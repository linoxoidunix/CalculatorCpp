
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "../CalculatorCPlus/Calculator.h"

SCENARIO("vectors can be sized and resized", "[vector]") 
{
	GIVEN("Calculator defualt") {
		CalculatorNew myCalculator;

	WHEN("Testing basic")
	{
		REQUIRE(myCalculator("1 + 2") == 3);
		REQUIRE(myCalculator("1 - 2") == -1);
		REQUIRE(myCalculator("1 + 2 + 3") == 6);
	}


	WHEN("Testing * / + - on difficult expression without brackets")
	{
		REQUIRE(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 1 * 45 - 2") == 43);
		REQUIRE(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 45") == 45);
		REQUIRE(myCalculator("12 / 4 * 3 - 6 * 3 / 2") == 0);

	}

	WHEN("Testing unary minus")
	{
		REQUIRE(myCalculator("- 3") == -3);
		REQUIRE(myCalculator("- - 3 - - 2") == 5);
		REQUIRE(myCalculator("- - 3 - - - 2") == 1);
	}

	WHEN("Testing unary minus with * and +")
	{
		REQUIRE(myCalculator("- - 3 * - - - - 2 + 1") == 7);
	}

	WHEN("Testing unary plus and unary minus with * and -")
	{
		REQUIRE(myCalculator("- - 3 * - - - - 2 + + 1") == 7);
	}

	WHEN("Testing unary plus and unary minus with * and -")
	{
		REQUIRE(myCalculator("- - 3 * - - - - 2 + + - - + 1") == 7);
		REQUIRE(myCalculator("- - + + - - + + + + 12 / - - + + - - 4 * + - - 3 - - - 6 * - - 3 / - - 2 + + - - + 45") == 45);
	}

	WHEN("Testing divided by 0")
	{
		REQUIRE_THROWS_AS(myCalculator("-3 / 0"), std::out_of_range);
	}

	WHEN("Testing bracket")
	{
		REQUIRE(myCalculator("( 2 / ( 1 + 1 ) - 2 / ( 1 + 1 ) ) / ( 2 - 1 ) + ( 0 )") == 0);
	}

	WHEN("Testing no operand before left bracket")
	{
		REQUIRE_THROWS_AS(myCalculator("( 2 / ( 1 + 1 ) - 2 / ( 1 + 1 ) ) ( 2 - 1 ) + ( 0 )"), std::logic_error);
	}


};
}