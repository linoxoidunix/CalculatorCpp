#include "ListToken.h"
#include "Token.h"
#include <list>

ListToken::ListToken(std::list<std::shared_ptr<Token>> listTokens) : workList(listTokens)
{
	typedef std::list<structToken>::iterator locIt;
	locIt lastOperand = listStructToken.end();
	for (auto elem = workList.begin(); elem != workList.end(); elem++)
	{
		if (elem == workList.begin())
		{
			structToken token(*elem, nullptr, nullptr);
			listStructToken.push_back(token);
			NoOperand* noOperand = dynamic_cast<NoOperand*> (elem->get());
			MulOperand* mulOperand = dynamic_cast<MulOperand*>(elem->get());
			DivOperand* divOperand = dynamic_cast<DivOperand*>(elem->get());
			SumOperand* sumOperand = dynamic_cast<SumOperand*>(elem->get());
			SubOperand* subOperand = dynamic_cast<SubOperand*>(elem->get());
			if (noOperand != nullptr || mulOperand != nullptr || divOperand != nullptr || sumOperand != nullptr || subOperand != nullptr)
			{

			}
			continue;
		}
		Number* number		   = dynamic_cast<Number*>	  (elem->get());
		if (number != nullptr)
		{
			listStructToken.rbegin()->setNextNumber(*elem);
		}
		NoOperand*	noOperand  = dynamic_cast<NoOperand*> (elem->get());
		if (noOperand != nullptr)
		{
			listStructToken.rbegin()->setNextOperand(*elem);
		}
		MulOperand* mulOperand = dynamic_cast<MulOperand*>(elem->get());
		if (mulOperand != nullptr)
		{
			listStructToken.rbegin()->setNextOperand(*elem);
		}
		DivOperand* divOperand = dynamic_cast<DivOperand*>(elem->get());
		if (divOperand != nullptr)
		{
			listStructToken.rbegin()->setNextOperand(*elem);
		}
		SumOperand* sumOperand = dynamic_cast<SumOperand*>(elem->get());
		if (sumOperand != nullptr)
		{
			listStructToken.rbegin()->setNextOperand(*elem);
		}
		SubOperand* subOperand = dynamic_cast<SubOperand*>(elem->get());
		if (subOperand != nullptr)
		{
			listStructToken.rbegin()->setNextOperand(*elem);
		}
		structToken token(*elem, nullptr, nullptr);
		listStructToken.push_back(token);
	}
}
