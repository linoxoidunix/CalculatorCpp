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
TypeToken NoOperand::accept(IVisiterIsOperand* visiter)
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

TypeToken MulOperand::accept(IVisiterIsOperand* visiter)
{
	return visiter->visit(this);
}

//std::tuple<Number, std::list<std::shared_ptr<Token>>> MulOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

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

//std::tuple<Number, std::list<std::shared_ptr<Token>>> SubOperand::accept(IvisiterCalculator* visiter)
//{
//	//visiter->visit(this);
//	//return visiter->;
//	visiter->
//}

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

//std::tuple<Number, std::list<std::shared_ptr<Token>>> SumOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

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

//std::tuple<Number, std::list<std::shared_ptr<Token>>> DivOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

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

//std::tuple<Number, std::list<std::shared_ptr<Token>>> UnarySubOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

Number& UnarySubOperand::calculate(Number& number)
{
	return Number(0) - number;
}

ListTokens TokensFactory::produce(std::list<std::string> fullExpression) const
{
	ListTokens result;
	std::shared_ptr<Token> prev_ptr;
	auto filler = [&result, &prev_ptr](const std::string currentToken)
	{
		BinaryTokenFactory binaryFactory;
		UnaryTokenFactory  unaryFactory;
		TokenIsOperand tokenIsOperand;
		bool _prevTokenIsOperand = (prev_ptr) ? (prev_ptr->accept(&tokenIsOperand) != TypeToken::TYPE_NUMBER) : false;
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

//std::tuple<Number, std::list<std::shared_ptr<Token>>> UnarySumOperand::accept(IvisiterCalculator* visiter)
//{
//	return std::tuple<Number, std::list<std::shared_ptr<Token>>>();
//}

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

//void Printer::print(Number& number)
//{
//}


