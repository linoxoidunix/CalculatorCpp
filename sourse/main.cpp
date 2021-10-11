// CalculatorCPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <list>
#include "core\Token.h"
#include "core\Executor.h"
#include "core\Calculator.h"

int main(int argc, char** argv)
{
    std::string current_exec_name = argv[0]; // Name of the current exec program
    std::list<std::string> all_args;
    std::string consoleExpression;
    if (argc > 1) {
        all_args.assign(argv + 1, argv + argc);
        for (auto elem : all_args)
        {
            consoleExpression += elem;
            consoleExpression += " ";
        }
    }
    Printer printer;
    CalculatorNew myCalculator;
    if (all_args.empty())
    {
        std::string myExpression = "( 2 / ( 1 + 1 ) - 2 / ( 1 + 1 ) ) / ( 2 - 1 ) + ( 0 )";
        printer.print(myCalculator(myExpression));
    }
    else
        printer.print(myCalculator(consoleExpression));
    return 0;
}
