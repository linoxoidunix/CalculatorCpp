#include "Calculator.h"
#include <iostream>
#include "Token.h"
#include <algorithm>
#include "Executor.h"

Calculator::Calculator()
{
}

double Calculator::operator()(std::string myExpression)
{
    std::string delimiter = " ";
    std::list<std::string> v = split(myExpression, delimiter);
    TokenFactory factoryToken;
    std::list<std::shared_ptr<Token>> listTokens;
    std::for_each(v.begin(), v.end(), [&listTokens, &factoryToken](const std::string v) { auto ptr = std::shared_ptr<Token>(); ptr.reset(factoryToken.produce(v));  listTokens.push_back(ptr); });
    Executor executor;
    return std::get<0>(executor.calculate(listTokens)).getNumber();
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
