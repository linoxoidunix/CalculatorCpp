#include "CalculatedModule.h"
#include "ParserListToken.h"
#include "Executor.h"
#include "ListToken.h"
#include <memory>
#include <exception>
#include "Token.h"

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
    //шанс что число
    if (expressionInTheBracket.size() == 1)
    {
        TokenIsOperandNew checker_is_operand;
        if (expressionInTheBracket.front()->accept(&checker_is_operand) == TypeToken::TYPE_NUMBER)
        {
            right_number = expressionInTheBracket.front();
            expressionInTheBracket.clear();
            return true;
        }
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
    Answer answer;
    TokenIsOperandNew checker_token;
    if (myNumber)
    {
        if (myNumber->accept(&checker_token) != TypeToken::TYPE_NUMBER)
            throw std::runtime_error("Expect a number. But " + myNumber->print() + " isn't number");
    }
    else
        throw std::runtime_error("Expect a number");
    answer = std::make_tuple(*(dynamic_cast<Number*>(myNumber.get())), myTokens);
    return answer;
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

Number ICalculatedModule::castNumber(SmartToken& token)
{
    MonopletWithOutRecursion plet(token);
    return std::get<0>(plet.calculate());
}

Number ICalculatedModule::castNumber(SmartToken&& token)
{
    MonopletWithOutRecursion plet(token);
    return std::get<0>(plet.calculate());
}
