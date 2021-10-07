#include "ListToken.h"
#include "Token.h"
#include <list>

ListToken::ListToken(ListTokens listTokens) : workList(listTokens)
{

}

SmartToken ListToken::getFirstToken()
{
	if (workList.empty())
		return SmartToken();
	return workList.front();
}

SmartToken ListToken::getSecondToken()
{
	if (workList.size() < 2)
		return SmartToken();
	auto iteratorBegin = workList.begin();
	iteratorBegin++;
	return *(iteratorBegin);
}

SmartToken ListToken::getThirdToken()
{
	if (workList.size() < 3)
		return SmartToken();
	auto iteratorBegin = workList.begin();
	iteratorBegin++;
	iteratorBegin++;
	return *(iteratorBegin);
}

ListTokens ListToken::getAllExceptFirst()
{
	if (workList.size() < 2)
		return ListTokens();
	auto iteratorBegin = workList.begin();
	iteratorBegin++;
	return ListTokens(iteratorBegin, workList.end());
}

ListTokens ListToken::getAllExceptFirstAndSecond()
{
	if (workList.size() < 3)
		return ListTokens();
	auto iteratorBegin = workList.begin();
	iteratorBegin++;
	iteratorBegin++;
	return ListTokens(iteratorBegin, workList.end());
}

SmartToken ListToken::getFirstOperand()
{
	if (workList.empty())
		return SmartToken();
	TokenIsOperand checker_is_operand;
	auto beginIterator = workList.begin();
	while (beginIterator != workList.end())
	{
		if((beginIterator->get()->accept(&checker_is_operand) == TypeToken::TYPE_BINARY_OPERAND || beginIterator->get()->accept(&checker_is_operand) == TypeToken::TYPE_UNARY_OPERAND))
			break;
		beginIterator++;
	}
	if(beginIterator != workList.end())
		return *beginIterator;
	else
		return SmartToken();
}
