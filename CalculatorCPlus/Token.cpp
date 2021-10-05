#include "Token.h"
#include "Executor.h"
#include <algorithm>
#include <stdexcept> 

int Number::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}
bool Number::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
//std::tuple<Number, std::list<std::shared_ptr<Token>>> Number::accept(IvisiterCalculator* vi)
//{
//	vi->
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();;
//}
//
int NoOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}
bool NoOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
//std::tuple<Number, std::list<std::shared_ptr<Token>>> NoOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}
//
int MulOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool MulOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> MulOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

Number MulOperand::calculate(Number left, Number right)
{
	return left * right;
}

int SubOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool SubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> SubOperand::accept(IvisiterCalculator* visiter)
//{
//	//visiter->visit(this);
//	//return visiter->;
//	visiter->
//}

Number SubOperand::calculate(Number left, Number right)
{
	return left - right;
}

int SumOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool SumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> SumOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

Number SumOperand::calculate(Number left, Number right)
{
	return left + right;
}

int DivOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool DivOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> DivOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

Number DivOperand::calculate(Number left, Number right)
{
	if (right.getNumber() == 0)
		throw std::out_of_range("divided by 0");
	return left / right;
}

int UnarySubOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool UnarySubOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> UnarySubOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

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
		TokenIsOperand tokenIsOperand;
		bool prevTokenIsOperand = (prev_ptr) ? prev_ptr->accept(&tokenIsOperand) : false;
		auto binaryPtr = binaryFactory.produce(currentToken);
		auto unaryPtr = unaryFactory.produce(currentToken);

		if (unaryPtr)
		{
			if (prevTokenIsOperand || (!prev_ptr))
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

bool UnarySumOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> UnarySumOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

Number UnarySumOperand::calculate(Number number)
{
	return number;
}

int LeftBracketOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool LeftBracketOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

int RightBracketOperand::accept(IVisiterPriority* visiter)
{
	return visiter->visit(this);
}

bool RightBracketOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}
