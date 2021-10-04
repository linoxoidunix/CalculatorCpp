#include "Token.h"
#include "Executor.h"

void Number::accept(IVisiter* visiter)
{
	visiter->visit(this);
}
//
void NoOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}
//
void MulOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

Number MulOperand::calculate(Number left, Number right)
{
	return left * right;
}

void SubOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

Number SubOperand::calculate(Number left, Number right)
{
	return left - right;
}

void SumOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

Number SumOperand::calculate(Number left, Number right)
{
	return left + right;
}

void DivOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

Number DivOperand::calculate(Number left, Number right)
{
	return left / right;
}
