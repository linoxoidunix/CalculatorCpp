// CalculatorCPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <list>
#include "Token.h"
#include "Executor.h"
#include "Calculator.h"


double operandSum()
{
    return 0;
}

double operandMul()
{
    return 1;
}

template <class ...Type>
auto operandSum(double left, Type... args)
{
    return left + operandSum(args...);
}

template <class ...Type>
auto operandSub(double left, Type... args)
{
    return ((left) - ... - args);
}

template <class ...Type>
auto operandMul(double left, Type... args)
{
    return left * operandMul(args...);
}

template <class ...Type>
auto operandDiv(double left, Type... args)
{
    return ((left) / ... / args);
}

//std::list<std::string> split(std::string& s, std::string& delimiter) {
//
//    std::list<std::string> list;
//    size_t beg, pos = 0;
//    while ((beg = s.find_first_not_of(delimiter, pos)) != std::string::npos)
//    {
//        pos = s.find_first_of(delimiter, beg + 1);
//        list.push_back(s.substr(beg, pos - beg));
//        std::cout << s.substr(beg, pos - beg) << std::endl;
//    }
//    return list;
//}

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
    std::string myExpression = "3 + 6 * 9";
    //std::string myExpression = "3 - 6 - 9 + 9 - 3 + 6";
    //std::string myExpression = "3 + 6";
    ////std::string myExpression = "3 + 6 + 9 - 6 * 2 / 4";
    ////std::string myExpression = "- 3";
    ////std::string myExpression = "12 / 4 / 3 - 1 - 1";
    ////std::string myExpression = "12 / 4 - 6 / 3 - 1";
    //std::string myExpression = "12 / 4 * 3 - 6 * 3 / 2 - 1 * 6";
    //std::string myExpression = "12 / 4 * 3 - 6 * 3 / 2 + 45";
    ////std::string myExpression = "12 - 4 - 3 - 1";
    //std::string myExpression = "- 3";
    //std::string delimiter = " ";
    //std::list<std::string> v = split(myExpression, delimiter);
    //TokenFactory factoryToken;
    //std::list<std::shared_ptr<Token>> listTokens;
    //std::for_each(v.begin(), v.end(), [&listTokens, &factoryToken](const std::string v) { auto ptr = std::shared_ptr<Token>(); ptr.reset(factoryToken.produce(v));  listTokens.push_back(ptr); });
    //Executor executor;
    ////Number number6(6);
    ////SumOperand sumOperand;
    ////Number number9(9);
    ////Number number12(12);
    ////executor.calculate(number6, sumOperand, number9, sumOperand, number12);
    Calculator myCalculator;
    printer.print(myCalculator(myExpression));
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
