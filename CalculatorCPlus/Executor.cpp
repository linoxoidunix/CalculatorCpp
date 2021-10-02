#include "Executor.h"
#include "ListToken.h"

Number Executor::calculate()
{
	ListToken myListToken(tokens);
	auto leftToken = myListToken.getLeftToken();
	auto operandToken = myListToken.getOperandToken();
	auto rightTokens = myListToken.getRighToken();
	Number* leftNumber = dynamic_cast<Number*>(leftToken.get());
	if (dynamic_cast<NoOperand*>(operandToken.get()) != nullptr)
		return *leftNumber;
	Executor childExecutor(rightTokens);
	Number rightExpression = childExecutor.calculate();
	auto sumOperand = dynamic_cast<SumOperand*>(operandToken.get());
	auto mulOperand = dynamic_cast<MulOperand*>(operandToken.get());
	auto subOperand = dynamic_cast<SubOperand*>(operandToken.get());
	auto divOperand = dynamic_cast<DivOperand*>(operandToken.get());
	Number result;
	if (sumOperand)
	{
		if (leftNumber == nullptr)
		{
			result = sumOperand->operator()(Number(), rightExpression);
		}
		else
			result = sumOperand->operator()(*leftNumber, rightExpression);
	}
	if (mulOperand)
	{
		if (leftNumber == nullptr)
		{
			result = mulOperand->operator()(Number(1), rightExpression);
		}
		else
			result = mulOperand->operator()(*leftNumber, rightExpression);
	}
	if (divOperand)
	{
		if (leftNumber == nullptr)
		{
			result = divOperand->operator()(Number(1), rightExpression);
		}
		else
			result = divOperand->operator()(*leftNumber, rightExpression);
	}
	if (subOperand)
	{
		if (leftNumber == nullptr)
		{
			result = subOperand->operator()(Number(), rightExpression);
		}
		else
		{
			result = subOperand->operator()(*leftNumber, rightExpression);
		}
	}
	return result;
}

void Executor::visit(MulOperand*)
{
}

void Executor::visit(DivOperand*)
{
}

void Executor::visit(SubOperand*)
{
}

void Executor::visit(SumOperand* operand)
{
	//if (operand->)
	//result = 
}

void Executor::visit(Number* number)
{
	result = *number;

}

void Executor::visit(NoOperand*)
{
}