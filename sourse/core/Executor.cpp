#include "Executor.h"
#include "ListToken.h"
#include <climits> 
#include "CalculatedModule.h"
#include "ParserListToken.h"

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

Answer ExecutorVersion2::calculate(ListTokens _tokens, int basePriority)
{
	ParserListToken new_parser(_tokens);
	SmartCalcModule module = new_parser.getNearestModule(basePriority);
	Answer myAnswer;
	if (module)
	{
		if (!dynamic_cast<MonopletWithOutRecursion*>(module.get()))
		{
			if (!module->canCalculate())
			{
				//войти в рекурсию
				Answer subExpression = calculate(module->getRest(), module->basePriority);
				module->setRest(std::get<1>(subExpression));
				SmartToken ptr = std::make_shared<Number>(std::get<0>(subExpression).getNumber());
				module->setNumber(ptr);
			}
			myAnswer = module->calculate();
			if (std::get<1>(myAnswer).size() != 0)
			{
				auto list = std::get<1>(myAnswer);
				SmartToken token = std::make_shared<Number>(std::get<0>(myAnswer).getNumber());
				list.insert(list.begin(), token);
				myAnswer = calculate(list, basePriority);
			}
		}
		else
		{
			myAnswer = module->calculate();
			return myAnswer;
		}
	}
	return myAnswer;
}
