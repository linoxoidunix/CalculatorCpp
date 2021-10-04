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
		auto operand = dynamic_cast<BinaryOperand*>(operandToken.get());
		if (operand != nullptr)
		{
			VisiterPriority visiterPriority;
			if (basePriority < operandToken->accept(&visiterPriority))
			{
				auto tuple = calculate(rightTokens, operandToken->accept(&visiterPriority));
				result = std::make_tuple(operand->calculate(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
				ListToken nextToken(std::get<1>(result));
				auto childList = std::get<1>(result);
				if (!std::get<1>(result).empty())
				{
					if (nextToken.getLeftToken()->accept(&visiterPriority) > basePriority)
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

int VisiterPriority::visit(MulOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(DivOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(SubOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(SumOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(Number* number)
{
	return 0; //???
}

int VisiterPriority::visit(NoOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(UnarySubOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(UnarySumOperand* op)
{
	return op->getPriority();
}

Executor::Executor()
{
}