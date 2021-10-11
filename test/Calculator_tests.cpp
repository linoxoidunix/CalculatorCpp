
#define CATCH_CONFIG_MAIN

#include "include\catch.hpp"
#include "string.h"
#include "..\sourse\core\Calculator.h"

SCENARIO("vectors can be sized and resized", "[vector]") 
{
	GIVEN("Calculator defualt") {
		CalculatorNew myCalculator;

	WHEN("Testing basic")
	{
		REQUIRE(stod(myCalculator("1 + 2").resultat) == 3);
		REQUIRE(stod(myCalculator("1 - 2").resultat) == -1);
		REQUIRE(stod(myCalculator("1 + 2 + 3").resultat) == 6);
	}


	WHEN("Testing * / + - on difficult expression without brackets")
	{
		REQUIRE(stod(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 1 * 45 - 2").resultat) == 43);
		REQUIRE(stod(myCalculator("12 / 4 * 3 - 6 * 3 / 2 + 45").resultat) == 45);
		REQUIRE(stod(myCalculator("12 / 4 * 3 - 6 * 3 / 2").resultat) == 0);

	}

	WHEN("Testing unary minus")
	{
		REQUIRE(stod(myCalculator("- 3").resultat) == -3);
		REQUIRE(stod(myCalculator("- - 3 - - 2").resultat) == 5);
		REQUIRE(stod(myCalculator("- - 3 - - - 2").resultat) == 1);
	}

	WHEN("Testing unary minus with * and +")
	{
		REQUIRE(stod(myCalculator("- - 3 * - - - - 2 + 1").resultat) == 7);
	}

	WHEN("Testing unary plus and unary minus with * and -")
	{
		REQUIRE(stod(myCalculator("- - 3 * - - - - 2 + + 1").resultat) == 7);
	}

	WHEN("Testing unary plus and unary minus with * and -")
	{
		REQUIRE(stod(myCalculator("- - 3 * - - - - 2 + + - - + 1").resultat) == 7);
		REQUIRE(stod(myCalculator("- - + + - - + + + + 12 / - - + + - - 4 * + - - 3 - - - 6 * - - 3 / - - 2 + + - - + 45").resultat) == 45);
	}

	WHEN("Testing divided by 0")
	{
		REQUIRE_THROWS_AS(stod(myCalculator.calculateDangerous("-3 / 0").resultat), std::out_of_range);
	}

	WHEN("Testing bracket")
	{
		REQUIRE(stod(myCalculator("( 2 / ( 1 + 1 ) - 2 / ( 1 + 1 ) ) / ( 2 - 1 ) + ( 0 )").resultat) == 0);
	}

	WHEN("Testing no operand before left bracket")
	{
		REQUIRE(stod(myCalculator("( 2 / ( 1 + 1 ) - 2 / ( 1 + 1 ) ) ( 2 - 1 ) + ( 0 )").resultat) == 0);
	}


};
}