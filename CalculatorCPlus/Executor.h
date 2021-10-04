#ifndef _EXECUTOR_H_
#define _EXECUTOR_H_

#include <list>
#include "Token.h"
#include "ListToken.h"

class IVisiter
{
public:
	virtual int visit(MulOperand*) = 0;
	virtual int visit(DivOperand*) = 0;
	virtual int visit(SubOperand*) = 0;
	virtual int visit(SumOperand*) = 0;
	virtual void visit(Number*) = 0;
	virtual int visit(NoOperand*) = 0;
	virtual int visit(UnarySubOperand*) = 0;
	virtual int visit(UnarySumOperand*) = 0;
	virtual ~IVisiter() = default;
};


class Executor : public IVisiter
{
public:
	Executor();
	std::tuple<Number, std::list<std::shared_ptr<Token>>> calculate(std::list<std::shared_ptr<Token>> _tokens, int basePriority = 0);
	virtual int visit(MulOperand*) override;
	virtual int visit(DivOperand*) override;
	virtual int visit(SubOperand*) override;
	virtual int visit(SumOperand*) override;
	virtual void visit(Number*)		override;
	virtual int visit(NoOperand*)	override;
	virtual int visit(UnarySubOperand*) override;
	virtual int visit(UnarySumOperand*) override;
private:

};



#endif