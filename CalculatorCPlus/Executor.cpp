#include "Executor.h"
#include "ListToken.h"
#include <climits> 

std::tuple<Number, std::list<std::shared_ptr<Token>>> Executor::calculate(std::list<std::shared_ptr<Token>> _tokens, int basePriority)
{
	ListToken myListToken(_tokens);
	auto leftToken = myListToken.getLeftToken();
	auto operandToken = myListToken.getOperandToken();
	auto rightTokens = myListToken.getRighToken();
	auto allButFirst = myListToken.getNoFirtsElement();
	//if (!leftToken)
	//	return std::make_tuple(Number(0), allButFirst);
	Number* leftNumber = dynamic_cast<Number*>(leftToken.get());
	std::tuple<Number, std::list<std::shared_ptr<Token>>> result;
	if ((leftNumber != nullptr))
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
				if (!std::get<1>(result).empty() && nextToken.getLeftToken()->accept(&visiterPriority) != INT_MAX)
				{
					//basePriority = 0;
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
			return std::make_tuple(*leftNumber, rightTokens);
	}
	else
	{
		UnaryOperand* operand = dynamic_cast<UnaryOperand*>(operandToken.get());
    	//если не левая скобка
		if (!dynamic_cast<LeftBracketOperand*>(operandToken.get()))
		{
			auto tuple = calculate(allButFirst, basePriority);
			result = std::make_tuple(operand->calculate(std::get<0>(tuple)), std::get<1>(tuple));
		}
		else
		{
			auto dividedTuple = getokensBeforeRightBracket(allButFirst);
			auto tuple = calculate(std::get<0>(dividedTuple));
			result = std::make_tuple(std::get<0>(tuple), std::get<1>(dividedTuple));
		}
		
	}
	return result;
}

std::tuple<std::list<std::shared_ptr<Token>>, std::list<std::shared_ptr<Token>>> Executor::getokensBeforeRightBracket(std::list<std::shared_ptr<Token>> _tokens)
{
	std::list<std::shared_ptr<Token>> beforeRightBracket;
	std::list<std::shared_ptr<Token>> afterRightBracket;
	bool start_initialise_after_right_bracket = false;
	try
	{
		int counterLeftBracket = 1;
		for (auto elem = _tokens.begin(); elem != _tokens.end(); elem++)
		{
			if (dynamic_cast<LeftBracketOperand*>(elem->get()))
			{
				counterLeftBracket++;
			}
			if (dynamic_cast<RightBracketOperand*>(elem->get()))
			{
				counterLeftBracket--;
			}
			if (dynamic_cast<RightBracketOperand*>(elem->get()) && counterLeftBracket == 0)
			{
				start_initialise_after_right_bracket = true;
				elem++;
				afterRightBracket.assign(elem, _tokens.end());
				break;
			}
			beforeRightBracket.push_back(*elem);
		}
		if(!start_initialise_after_right_bracket)
			throw std::out_of_range("Didn't find corresponsable right bracket");
	}
	catch (std::out_of_range& ex)
	{
		std::cout << "Exceptions occured: " << ex.what() << std::endl;
	}
	return std::make_tuple(beforeRightBracket, afterRightBracket);
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

int VisiterPriority::visit(LeftBracketOperand* op)
{
	return op->getPriority();
}

int VisiterPriority::visit(RightBracketOperand* op)
{
	return op->getPriority();
}

Executor::Executor()
{
}

void VisiterCalculator::visit(Number*)
{
}

std::tuple<Number, std::list<std::shared_ptr<Token>>> VisiterCalculator::visit(UnarySubOperand* operand)
{
	Executor myExecutor;
	auto tuple = myExecutor.calculate(localTokens, 0);
	return std::make_tuple(operand->calculate(std::get<0>(tuple)), std::get<1>(tuple));
}

