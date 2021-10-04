#include "Token.h"
#include "Executor.h"
#include <algorithm>

void Number::accept(IVisiter* visiter)
{
	visiter->visit(this);
}
bool Number::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
//
void NoOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}
bool NoOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
//
void MulOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool MulOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number MulOperand::calculate(Number left, Number right)
{
	return left * right;
}

void SubOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool SubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number SubOperand::calculate(Number left, Number right)
{
	return left - right;
}

void SumOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool SumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number SumOperand::calculate(Number left, Number right)
{
	return left + right;
}

void DivOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool DivOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number DivOperand::calculate(Number left, Number right)
{
	return left / right;
}

void UnarySubOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool UnarySubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number UnarySubOperand::calculate(Number number)
{
	return Number(0) - number;
}

std::list<std::shared_ptr<Token>> TokensFactory::produce(std::list<std::string> fullExpression) const
{
	std::list<std::shared_ptr<Token>> result;
	std::shared_ptr<Token> prev_ptr;
	auto filler = [&result, &prev_ptr](const std::string currentToken)
	{
		BinaryTokenFactory binaryFactory;
		UnaryTokenFactory  unaryFactory;
		auto tokenIsOperand = std::make_shared<TokenIsOperand>();;
		bool prevTokenIsOperand = (prev_ptr) ? prev_ptr->accept(tokenIsOperand.get()) : false;
		auto binaryPtr = binaryFactory.produce(currentToken);
		auto unaryPtr = unaryFactory.produce(currentToken);

		if (unaryPtr)
		{
			if (prevTokenIsOperand || (!prev_ptr))
			{
				std::shared_ptr<Token> ptr;
				ptr.reset(unaryPtr);
				result.push_back(ptr);
			}
			else
			{
				std::shared_ptr<Token> ptr;
				ptr.reset(binaryPtr);
				result.push_back(ptr);
			}
		}
		else
		{
			std::shared_ptr<Token> ptr;
			ptr.reset(binaryPtr);
			result.push_back(ptr);
		}
		prev_ptr = result.back();
	};
	std::for_each(fullExpression.begin(), fullExpression.end(), filler);
	return result;
}

void UnarySumOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

bool UnarySumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

Number UnarySumOperand::calculate(Number number)
{
	return number;
}
