#include "CalculatedModule.h"
#include "Executor.h"
#include "ListToken.h"
#include <memory>
#include <exception>
#include "Token.h"


Answer Monoplet::calculate()
{
    return std::make_tuple(*(dynamic_cast<Number*>(myNumber.get())), myTokens);
}

bool Monoplet::canCalculate()
{
    return true;
}

ListTokens Monoplet::getRest()
{
    return ListTokens();
}

void Monoplet::setRest(ListTokens& list)
{
}

void Monoplet::setNumber(SmartToken& Token)
{
    myNumber = Token;
}

void Monoplet::setNumber(SmartToken&& Token)
{
}

Answer Duplet::calculate()
{
    ListTokens emptyListTokens;
    Monoplet monoplet_left_number(emptyListTokens, number);
    Answer leftPart = monoplet_left_number.calculate();
    auto result = dynamic_cast<UnaryOperand*>(op.get())->calculate(std::get<0>(leftPart));
    return std::make_tuple(result, myTokens);
}

bool Duplet::canCalculate()
{
    return (number) ? true : false;
}

ListTokens Duplet::getRest()
{
    return myTokens;
}

void Duplet::setRest(ListTokens& list)
{
    myTokens = list;
}

void Duplet::setNumber(SmartToken& token)
{
    number = token;
}

void Duplet::setNumber(SmartToken&& token)
{
    number = token;
}

Answer Triplet::calculate()
{
    if (!right_number)
        right_number = expressionInTheBracket.front();
    ListToken analyser(expressionInTheBracket);
    ListTokens emptyListTokens;
    Monoplet monoplet_left_number(emptyListTokens, left_number);
    Answer leftPart = monoplet_left_number.calculate();
    Monoplet monoplet_right_number(emptyListTokens, right_number);
    Answer rightPart = monoplet_right_number.calculate();
    //if(expressionInTheBracket.empty())
    //    return std::make_tuple(dynamic_cast<BinaryOperand*>(op.get())->calculate(std::get<0>(leftPart), std::get<0>(rightPart)), ListTokens());
    //else
        return std::make_tuple(dynamic_cast<BinaryOperand*>(op.get())->calculate(std::get<0>(leftPart), std::get<0>(rightPart)), expressionInTheBracket);
}

bool Triplet::canCalculate()
{
    //bool result = false;
    //VisiterPriority checker_priority;
    //ListToken list(expressionInTheBracket);
    //if(list.getFirstOperand())
    //    if (op->accept(&checker_priority) >= list.getFirstOperand()->accept(&checker_priority))
    //    {
    //        result = true;
    //        return result;
    //    }
    if (expressionInTheBracket.size() == 1)
    {
        right_number = expressionInTheBracket.front();
        expressionInTheBracket.clear();
        return true;
    }
    return (right_number) ? true : false;
}

ListTokens Triplet::getRest()
{
    return expressionInTheBracket;
}

void Triplet::setRest(ListTokens& list)
{
    expressionInTheBracket = list;
}

void Triplet::setNumber(SmartToken& token)
{
    right_number = token;
}

void Triplet::setNumber(SmartToken&& token)
{
    right_number = token;
}

Answer MonopletWithOutRecursion::calculate()
{
    ListTokens emptyListTokens;
    Monoplet monoplet_left_number(emptyListTokens, myNumber);
    Number result = std::get<0>(monoplet_left_number.calculate());
    return std::make_tuple(result, myTokens);
}

bool MonopletWithOutRecursion::canCalculate()
{
    return true;
}

ListTokens MonopletWithOutRecursion::getRest()
{
    return myTokens;
}

void MonopletWithOutRecursion::setRest(ListTokens& list)
{
    myTokens = list;
}

void MonopletWithOutRecursion::setNumber(SmartToken& Token)
{
    myNumber = Token;
}

void MonopletWithOutRecursion::setNumber(SmartToken&& Token)
{
    myNumber = Token;
}
