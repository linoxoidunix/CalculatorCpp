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

void SubOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

void SumOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}

void DivOperand::accept(IVisiter* visiter)
{
	visiter->visit(this);
}
