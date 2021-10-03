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
	std::tuple<Number, std::list<std::shared_ptr<Token>>> result = std::make_tuple(*leftNumber, myListToken.getNoFirtsElement());
	if (leftNumber != nullptr)
	{
		if (dynamic_cast<Operand*>(operandToken.get()) != nullptr)
		{
			if (basePriority < dynamic_cast<Operand*>(operandToken.get())->getPriority())
			{
				auto sumOperand = dynamic_cast<SumOperand*>(operandToken.get());
				auto mulOperand = dynamic_cast<MulOperand*>(operandToken.get());
				auto subOperand = dynamic_cast<SubOperand*>(operandToken.get());
				auto divOperand = dynamic_cast<DivOperand*>(operandToken.get());

				if (sumOperand)
				{
					auto tuple = calculate(rightTokens, sumOperand->getPriority());
					result = std::make_tuple(sumOperand->operator()(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
					ListToken nextToken(std::get<1>(result));
					if (!std::get<1>(result).empty() && dynamic_cast<Operand*>(nextToken.getLeftToken().get())->getPriority() >= basePriority)
					{
						std::list<std::shared_ptr<Token>> newTokens;
						std::shared_ptr<Token> ptr;
						ptr.reset(new Number(std::get<0>(result).getNumber()));
						newTokens.push_back(ptr);
						for (auto elem : std::get<1>(tuple))
							newTokens.push_back(elem);
						result = calculate(newTokens);
					}
				}
				if (subOperand)
				{
					auto tuple = calculate(rightTokens, subOperand->getPriority());
					result = std::make_tuple(subOperand->operator()(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
					ListToken nextToken(std::get<1>(result));
					if (!std::get<1>(result).empty() && dynamic_cast<Operand*>(nextToken.getLeftToken().get())->getPriority() >= basePriority)
					{
						std::list<std::shared_ptr<Token>> newTokens;
						std::shared_ptr<Token> ptr;
						ptr.reset(new Number(std::get<0>(result).getNumber()));
						newTokens.push_back(ptr);
						for (auto elem : std::get<1>(tuple))
							newTokens.push_back(elem);
						result = calculate(newTokens);
					}
				}
				if (mulOperand)
				{
					auto tuple = calculate(rightTokens, mulOperand->getPriority());
					result = std::make_tuple(mulOperand->operator()(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
					ListToken nextToken(std::get<1>(result));
					if (!std::get<1>(result).empty() && dynamic_cast<Operand*>(nextToken.getLeftToken().get())->getPriority() >= basePriority)
					{
						std::list<std::shared_ptr<Token>> newTokens;
						std::shared_ptr<Token> ptr;
						ptr.reset(new Number(std::get<0>(result).getNumber()));
						newTokens.push_back(ptr);
						for (auto elem : std::get<1>(tuple))
							newTokens.push_back(elem);
						result = calculate(newTokens);
					}
				}
				if (divOperand)
				{
					auto tuple = calculate(rightTokens, divOperand->getPriority());
					result = std::make_tuple(divOperand->operator()(*leftNumber, std::get<0>(tuple)), std::get<1>(tuple));
					ListToken nextToken(std::get<1>(result));
					if (!std::get<1>(result).empty() && dynamic_cast<Operand*>(nextToken.getLeftToken().get())->getPriority() > basePriority)
					{
						std::list<std::shared_ptr<Token>> newTokens;
						std::shared_ptr<Token> ptr;
						ptr.reset(new Number(std::get<0>(result).getNumber()));
						newTokens.push_back(ptr);
						for (auto elem : std::get<1>(tuple))
							newTokens.push_back(elem);
						result = calculate(newTokens);
					}
				}
			}
		}
		else
		{
			return std::make_tuple(*leftNumber, std::list<std::shared_ptr<Token>>());
		}
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

Executor::Executor()
{
}
//
//std::tuple<Number, std::list<std::shared_ptr<Token>>> Executor::calculate(std::list<std::shared_ptr<Token>> _list, int basePriority)
//{
//	ListToken myListToken(tokens);
//	auto leftToken = myListToken.getLeftToken();
//	auto operandToken = myListToken.getOperandToken();
//	auto rightTokens = myListToken.getRighToken();
//	Number* leftNumber = dynamic_cast<Number*>(leftToken.get());
//	if (dynamic_cast<NoOperand*>(operandToken.get()) != nullptr)
//		return std::make_tuple(*leftNumber, std::list < std::shared_ptr<Token>>());
//	if(basePriority <= dynamic_cast<Operand*>(operandToken.get())->getPriority())
//		return std::make_tuple(*leftNumber, myListToken.getNoFirtsElement());
//	Executor childExecutor(rightTokens);
//	auto tuple = childExecutor.calculate(rightTokens, dynamic_cast<Operand*>(operandToken.get())->getPriority());
//	auto sumOperand = dynamic_cast<SumOperand*>(operandToken.get());
//	auto mulOperand = dynamic_cast<MulOperand*>(operandToken.get());
//	auto subOperand = dynamic_cast<SubOperand*>(operandToken.get());
//	auto divOperand = dynamic_cast<DivOperand*>(operandToken.get());
//	Number result;
//	if (sumOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = sumOperand->operator()(Number(), std::get<0>(tuple));
//		}
//		else
//			result = sumOperand->operator()(*leftNumber, std::get<0>(tuple));
//	}
//	if (mulOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = mulOperand->operator()(Number(1), std::get<0>(tuple));
//		}
//		else
//			result = mulOperand->operator()(*leftNumber, std::get<0>(tuple));
//	}
//	if (divOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = divOperand->operator()(Number(1), std::get<0>(tuple));
//		}
//		else
//			result = divOperand->operator()(*leftNumber, std::get<0>(tuple));
//	}
//	if (subOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = subOperand->operator()(Number(), std::get<0>(tuple));
//		}
//		else
//		{
//			result = subOperand->operator()(*leftNumber, std::get<0>(tuple));
//		}
//	}
//	return std::make_tuple(result, );
//}
