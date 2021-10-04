#include "Executor.h"
#include "ListToken.h"

std::tuple<Number, std::list<std::shared_ptr<Token>>> Executor::calculate(std::list<std::shared_ptr<Token>> _tokens, int basePriority)
{
	ListToken myListToken(_tokens);
	auto leftToken = myListToken.getLeftToken();
	auto operandToken = myListToken.getOperandToken();
	auto rightTokens = myListToken.getRighToken();
	auto allButFirst = myListToken.getNoFirtsElement();
	Number* leftNumber = dynamic_cast<Number*>(leftToken.get());
	std::tuple<Number, std::list<std::shared_ptr<Token>>> result;
	if (leftNumber != nullptr)
	{
		result = std::make_tuple(*leftNumber, myListToken.getNoFirtsElement());
		if (dynamic_cast<BinaryOperand*>(operandToken.get()) != nullptr)
		{
			if (basePriority < dynamic_cast<Operand*>(operandToken.get())->getPriority())
			{
				BinaryOperand* operand =  dynamic_cast<BinaryOperand*>(operandToken.get());
				auto tuple = calculate(rightTokens, operand->getPriority());
				result = std::make_tuple(operand->calculate(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
				ListToken nextToken(std::get<1>(result));
				auto childList = std::get<1>(result);
				if (!std::get<1>(result).empty())
				{
					if (dynamic_cast<Operand*>(nextToken.getLeftToken().get())->getPriority() > basePriority)
					{
						std::shared_ptr<Token> ptr;
						ptr.reset(new Number(std::get<0>(result)));
						childList.insert(childList.begin(), ptr);
						result = calculate(childList);
					}
				}
			}
		}
		else
		{
			return std::make_tuple(*leftNumber, std::list<std::shared_ptr<Token>>());
		}
	}
	else
	{
		UnaryOperand* operand = dynamic_cast<UnaryOperand*>(operandToken.get());
		auto tuple = calculate(allButFirst, basePriority);
		result = std::make_tuple(operand->calculate(std::get<0>(tuple)), std::get<1>(tuple));
	}
	return result;
}

int Executor::visit(MulOperand* op)
{
	return op->getPriority();
}

int Executor::visit(DivOperand* op)
{
	return op->getPriority();
}

int Executor::visit(SubOperand* op)
{
	return op->getPriority();
}

int Executor::visit(SumOperand* op)
{
	return op->getPriority();
}

void Executor::visit(Number* number)
{
	//result = *number;

}

int Executor::visit(NoOperand* op)
{
	return op->getPriority();
}

int Executor::visit(UnarySubOperand* op)
{
	return op->getPriority();
}

int Executor::visit(UnarySumOperand* op)
{
	return op->getPriority();
}

Executor::Executor()
{
}