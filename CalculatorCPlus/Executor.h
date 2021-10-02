#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <list>
#include "Token.h"
#include "ListToken.h"

class IVisiter
{
public:
	virtual void visit(MulOperand*) = 0;
	virtual void visit(DivOperand*) = 0;
	virtual void visit(SubOperand*) = 0;
	virtual void visit(SumOperand*) = 0;
	virtual void visit(Number*) = 0;
	virtual void visit(NoOperand*) = 0;
	virtual ~IVisiter() = default;
};


class Executor : public IVisiter
{
public:
	Executor(std::list<std::shared_ptr<Token>> _tokens) : tokens(_tokens) {};
	Number calculate();
	virtual void visit(MulOperand*) override;
	virtual void visit(DivOperand*) override;
	virtual void visit(SubOperand*) override;
	virtual void visit(SumOperand*) override;
	virtual void visit(Number*)		override;
	virtual void visit(NoOperand*)	override;
private:
	std::list<std::shared_ptr<Token>> tokens;
	Number result;
	Number calculate(std::list<structToken>)
	{
		ListToken myListToken(tokens);
		auto listStructedToken = myListToken.getStructedToken();
		listStructedToken.front().getCurrent().get()->accept(this);
		return result;
	}
	
};



#endif

//
//Number calculate()
//{
//	ListToken myListToken(tokens);
//	auto listStructedToken = myListToken.getStructedToken();
//	//for(auto token : listStructedToken)
//	listStructedToken.front().getCurrent().get()->accept(this);
//
//	//myListToken.get().getCurrent()->accept(this);
//
//
//	auto leftToken = myListToken.getLeftToken();
//	auto leftNumber = dynamic_cast<Number*>(leftToken.get());
//	auto operandToken = myListToken.getOperandToken();
//	auto rightTokens = myListToken.getRighToken();
//	if (dynamic_cast<NoOperand*>(operandToken.get()) != nullptr)
//		return *leftNumber;
//	Executor childExecutor(rightTokens);
//	Number rightExpression = childExecutor.calculate();
//	auto sumOperand = dynamic_cast<SumOperand*>(operandToken.get());
//	auto mulOperand = dynamic_cast<MulOperand*>(operandToken.get());
//	auto subOperand = dynamic_cast<SubOperand*>(operandToken.get());
//	auto divOperand = dynamic_cast<DivOperand*>(operandToken.get());
//	Number result;
//	if (sumOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = sumOperand->operator()(Number(), rightExpression);
//		}
//		else
//			result = sumOperand->operator()(*leftNumber, rightExpression);
//	}
//	if (mulOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = mulOperand->operator()(Number(1), rightExpression);
//		}
//		else
//			result = mulOperand->operator()(*leftNumber, rightExpression);
//	}
//	if (divOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = divOperand->operator()(Number(1), rightExpression);
//		}
//		else
//			result = divOperand->operator()(*leftNumber, rightExpression);
//	}
//	if (subOperand)
//	{
//		if (leftNumber == nullptr)
//		{
//			result = subOperand->operator()(Number(), rightExpression);
//		}
//		else
//			result = subOperand->operator()(*leftNumber, rightExpression);
//	}
//	return result;
//}