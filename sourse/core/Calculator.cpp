#include "Calculator.h"
#include <iostream>
#include "Token.h"
#include <algorithm>
#include "Executor.h"
#include <exception>

CalculatorNew::CalculatorNew()
{
}

ResultatCalculation CalculatorNew::operator()(std::string myExpression)
{
    std::string delimiter = " ";
    std::list<std::string> v = split(myExpression, delimiter);
    TokensFactory newTokensFactory;
    auto result = newTokensFactory.produce(v);
    ExecutorVersion2 executor;
    Printer myPrinter;
    ResultatCalculation resultat;
    try
    {
    auto outputTuple = executor.calculate(result);
    resultat = ResultatCalculation(std::get<0>(outputTuple).getNumber());
    if (!std::get<1>(outputTuple).empty())
        throw std::logic_error("Didn't calculate this: " + myPrinter.printToString(std::get<1>(outputTuple)));
    return resultat;
    }
    catch (const std::out_of_range& ex) {
        std::cout << "An exception occurred: " << ex.what() << std::endl;
    }
    catch (const std::logic_error& ex) {
        std::cout << "An exception occurred: " << ex.what() << std::endl;
    }
    catch (const std::runtime_error& ex) {
        std::cout << "An exception occurred: " << ex.what() << std::endl;
    }
    return resultat;
}

ResultatCalculation CalculatorNew::calculateDangerous(std::string myExpression)
{
    std::string delimiter = " ";
    std::list<std::string> v = split(myExpression, delimiter);
    TokensFactory newTokensFactory;
    auto result = newTokensFactory.produce(v);
    ExecutorVersion2 executor;
    Printer myPrinter;
    ResultatCalculation resultat;
    auto outputTuple = executor.calculate(result);
    resultat = ResultatCalculation(std::get<0>(outputTuple).getNumber());
    if (!std::get<1>(outputTuple).empty())
        throw std::logic_error("Didn't calculate this: " + myPrinter.printToString(std::get<1>(outputTuple)));
    return resultat;
}


std::list<std::string> CalculatorNew::split(std::string& s, std::string& delimiter)
{
    std::list<std::string> list;
    size_t beg, pos = 0;
    while ((beg = s.find_first_not_of(delimiter, pos)) != std::string::npos)
    {
        pos = s.find_first_of(delimiter, beg + 1);
        list.push_back(s.substr(beg, pos - beg));
    }
    return list;
}
