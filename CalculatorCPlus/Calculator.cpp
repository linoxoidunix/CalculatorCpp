#include "Calculator.h"
#include <iostream>
#include "Token.h"
#include <algorithm>
#include "Executor.h"
#include <exception>

Calculator::Calculator()
{
}

double Calculator::operator()(std::string myExpression)
{
    std::string delimiter = " ";
    std::list<std::string> v = split(myExpression, delimiter);
    TokensFactory newTokensFactory;
    auto result = newTokensFactory.produce(v);
    Executor executor;
    Printer myPrinter;
    double outputValue = -777;
    try
    {
        auto outputTuple = executor.calculate(result);
        outputValue = std::get<0>(outputTuple).getNumber();
        if (!std::get<1>(outputTuple).empty())
            throw std::logic_error("Didn't calculate this: " + myPrinter.printToString(std::get<1>(outputTuple)));
        return outputValue;
    }
    catch (const std::out_of_range& ex) {
        std::cout << "An exception occurred: " << ex.what() << std::endl;
    }
    catch (const std::logic_error& ex) {
        std::cout << "An exception occurred: " << ex.what() << std::endl;
    }
    return outputValue;
}

std::list<std::string> Calculator::split(std::string& s, std::string& delimiter)
{
    std::list<std::string> list;
    size_t beg, pos = 0;
    while ((beg = s.find_first_not_of(delimiter, pos)) != std::string::npos)
    {
        pos = s.find_first_of(delimiter, beg + 1);
        list.push_back(s.substr(beg, pos - beg));
        std::cout << s.substr(beg, pos - beg) << std::endl;
    }
    return list;
}
