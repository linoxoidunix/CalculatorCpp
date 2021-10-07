#include "CalculatedModule.h"
#include "Executor.h"
#include "ListToken.h"
#include <memory>
#include <exception>
#include "Token.h"


//Answer Monoplet::calculate()
//{
//    return std::make_tuple(*(dynamic_cast<Number*>(myNumber.get())), myTokens);
//}
//
//bool Monoplet::canCalculate()
//{
//    return true;
//}
//
//ListTokens Monoplet::getRest()
//{
//    return ListTokens();
//}
//
//void Monoplet::setRest(ListTokens& list)
//{
//}
//
//void Monoplet::setNumber(SmartToken& Token)
//{
//    myNumber = Token;
//}
//
//void Monoplet::setNumber(SmartToken&& Token)
//{
//}

Answer Duplet::calculate()
{
    Number buffer = castNumber(number);
    auto result = dynamic_cast<UnaryOperand*>(op.get())->calculate(buffer);
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
    Number bufferLeft = castNumber(left_number);
    Number bufferRight = castNumber(right_number);
    return std::make_tuple(dynamic_cast<BinaryOperand*>(op.get())->calculate(bufferLeft, bufferRight), expressionInTheBracket);
}

bool Triplet::canCalculate()
{
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
    return std::make_tuple(*(dynamic_cast<Number*>(myNumber.get())), myTokens);
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

bool ExpressionInTheBracket::canCalculate()
{
    return (number) ? true : false;

}

void ExpressionInTheBracket::setNumber(SmartToken& token)
{
    number = token;
}

void ExpressionInTheBracket::setNumber(SmartToken&& token)
{
    number = token;
}

ListTokens ExpressionInTheBracket::getRest()
{
    return tokensInTheBracket;
}

void ExpressionInTheBracket::setRest(ListTokens& list)
{

}

Answer ExpressionInTheBracket::calculate()
{
    Number leftPart = castNumber(number);
    Answer result = std::make_tuple(leftPart, tokensOutTheBracket);
    return result;
}
