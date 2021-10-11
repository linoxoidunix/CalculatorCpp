#include "Token.h"
#include "Executor.h"
#include <algorithm>
#include <stdexcept> 

int Number::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}
TypeToken Number::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

int NoOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}
TypeToken NoOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

int MulOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken MulOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& MulOperand::calculate(Number& left, Number& right)
{
	return left * right;
}

int SubOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken SubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& SubOperand::calculate(Number& left, Number& right)
{
	return left - right;
}

int SumOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken SumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& SumOperand::calculate(Number& left, Number& right)
{
	return left + right;
}

int DivOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken DivOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& DivOperand::calculate(Number& left, Number& right)
{
	if (right.getNumber() == 0)
		throw std::out_of_range("divided by 0");
	return left / right;
}

int UnarySubOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken UnarySubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& UnarySubOperand::calculate(Number& number)
{
	return number * Number(-1);
}

ListTokens TokensFactory::produce(std::list<std::string> fullExpression) const
{
	ListTokens result;
	std::shared_ptr<Token> prev_ptr;
	auto filler = [&result, &prev_ptr](const std::string currentToken)
	{
		BinaryTokenFactory binaryFactory;
		UnaryTokenFactory  unaryFactory;
		TokenIsOperandNew tokenIsOperand;
		bool _prevTokenIsOperand = (prev_ptr) ? (prev_ptr->accept(&tokenIsOperand) != TypeToken::TYPE_NUMBER && prev_ptr->accept(&tokenIsOperand) != TypeToken::TYPE_RIGHT_BRACKET) : false;
		bool _prevTokenExist = (prev_ptr) ? true : false;
		auto binaryPtr = binaryFactory.produce(currentToken);
		auto unaryPtr = unaryFactory.produce(currentToken);

		if (unaryPtr)
		{
			if (_prevTokenIsOperand || (!prev_ptr))
				result.push_back(unaryPtr);
			else
				if(binaryPtr)
					result.push_back(binaryPtr);
				else
					result.push_back(unaryPtr);
		}
		else
			result.push_back(binaryPtr);
		prev_ptr = result.back();
	};
	std::for_each(fullExpression.begin(), fullExpression.end(), filler);
	return result;
}

int UnarySumOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken UnarySumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number& UnarySumOperand::calculate(Number& number)
{
	return number;
}

int LeftBracketOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken LeftBracketOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

int RightBracketOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

TypeToken RightBracketOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
