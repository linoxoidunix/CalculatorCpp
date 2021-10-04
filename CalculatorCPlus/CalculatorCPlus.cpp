// CalculatorCPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <list>
#include "Token.h"
#include "Executor.h"
#include "Calculator.h"

int main()
{
    //std::cout << operandSum(3, 5, 6) << std::endl;
    //std::cout << operandDiv(8, 4, 2, 2) << std::endl;
    //Number a(1);
    //Number b(2);
    //Number c(3);
    //Number d(4);
    Printer printer;
    ////printer.print(a + (b - c) * d);
    //std::string myExpression = "3 + 6 * 9 + 1";
    //std::string myExpression = "3 - 6 - 9 + 9 - 3 + 6";
    //std::string myExpression = "3 + 6";
    ////std::string myExpression = "3 + 6 + 9 - 6 * 2 / 4";
    ////std::string myExpression = "- 3";
    //std::string myExpression = "12 / 4 / 3 - 1 - 1";
    //std::string myExpression = "3 - 6 / 3 - 1";
    //std::string myExpression = "12 / 4 * 3 - 6 * 3 / 2 - 1 * 6";
    //std::string myExpression = "12 / 4 * 3 - 6 * 3 / 2 + 45";
    ////std::string myExpression = "12 - 4 - 3 - 1";
    std::string myExpression = "3 * - 2 + + 1";
    Calculator myCalculator;
    printer.print(myCalculator(myExpression));
    return 0;
}
