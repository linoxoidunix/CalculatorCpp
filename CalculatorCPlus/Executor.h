#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <list>
#include "Token.h"
#include "ListToken.h"

class IVisiterPriority
{
public:
	virtual int visit(MulOperand*) = 0;
	virtual int visit(DivOperand*) = 0;
	virtual int visit(SubOperand*) = 0;
	virtual int visit(SumOperand*) = 0;
	virtual int visit(Number*) = 0;
	virtual int visit(NoOperand*) = 0;
	virtual int visit(UnarySubOperand*) = 0;
	virtual int visit(UnarySumOperand*) = 0;
	virtual int visit(LeftBracketOperand*) = 0;
	virtual int visit(RightBracketOperand*) = 0;
	virtual ~IVisiterPriority() = default;
};

class VisiterPriority : public IVisiterPriority
{
public:
	virtual int visit(MulOperand*) override;
	virtual int visit(DivOperand*) override;
	virtual int visit(SubOperand*) override;
	virtual int visit(SumOperand*) override;
	virtual int visit(Number*)		override;
	virtual int visit(NoOperand*)	override;
	virtual int visit(UnarySubOperand*) override;
	virtual int visit(UnarySumOperand*) override;
	virtual int visit(LeftBracketOperand*) override;
	virtual int visit(RightBracketOperand*) override;
	virtual ~VisiterPriority() = default;
};

class IVisiterCalculator
{
public:
	virtual void visit(MulOperand*) = 0;
	virtual void visit(DivOperand*) = 0;
	virtual void visit(SubOperand*) = 0;
	virtual void visit(SumOperand*) = 0;
	virtual void visit(Number*) = 0;
	virtual void visit(NoOperand*) = 0;
	virtual Answer visit(UnarySubOperand*) = 0;
	virtual void visit(UnarySumOperand*) = 0;
	virtual ~IVisiterCalculator() = default;
protected:
	ListTokens localTokens;
};

class VisiterCalculator : public IVisiterCalculator
{
public:
	VisiterCalculator(ListTokens _tokens) {localTokens = _tokens;}
	virtual void visit(MulOperand*) override {};
	virtual void visit(DivOperand*) override {};
	virtual void visit(SubOperand*) override {};
	virtual void visit(SumOperand*) override {};
	virtual void visit(Number*)		override;
	virtual void visit(NoOperand*)	override {};
	virtual Answer visit(UnarySubOperand*) override;
	virtual void visit(UnarySumOperand*) override {};
	virtual ~VisiterCalculator() = default;

};

class IExecutor
{
public:
	virtual Answer calculate(ListTokens _tokens, int basePriority = 0) = 0;
};


class Executor : public IExecutor
{
public:
	Executor();
	virtual Answer calculate(ListTokens _tokens, int basePriority = 0) override;
	~Executor() = default;
private:
	// output.first - выражение до правой скобки
	// output.second - выражение после правой скобки
	std::tuple<ListTokens, ListTokens> getokensBeforeRightBracket(ListTokens _tokens);
};

class ExecutorVersion2 : public IExecutor
{
public:
	ExecutorVersion2() {};
	virtual Answer calculate(ListTokens _tokens, int basePriority = 0) override;
	~ExecutorVersion2() = default;

};

#endif