#ifndef _LIST_TOKEN_H_
#define _LIST_TOKEN_H_

#include<list>
#include "Token.h"
class structToken
{
	std::shared_ptr<Token> current;
	std::shared_ptr<Token> nextNumber;
	std::shared_ptr<Token> nextOperand;
public:
	structToken(std::shared_ptr<Token> _current, std::shared_ptr<Token> _nextNumber, std::shared_ptr<Token> _nextOperand) : current(_current), nextNumber(_nextNumber), nextOperand(_nextOperand) {};
	structToken() {};
	void setNextNumber(std::shared_ptr<Token> next) { nextNumber = next; };
	void setNextOperand(std::shared_ptr<Token> next) { nextOperand = next; };
	std::shared_ptr<Token> getCurrent() { return current; };
	std::shared_ptr<Token> getNextOperand() { return nextOperand; };
};

class ListToken
{
public:
	ListToken(std::list<std::shared_ptr<Token>> listTokens);
	std::shared_ptr<Token> getLeftToken()
	{
		if (workList.empty())
			return std::make_shared<Number>();
		return workList.front();
	}
	std::shared_ptr<Token> getOperandToken()
	{
		if (workList.size() < 2)
			return std::make_shared<NoOperand>();
		auto iteratorBegin = workList.begin();
		if (dynamic_cast<Operand*>(iteratorBegin->get()))
			return *iteratorBegin;
		iteratorBegin++;
		return *(iteratorBegin);
	}
	std::list<std::shared_ptr<Token>> getRighToken()
	{
		if (workList.size() < 2)
			return { std::make_shared<Number>() };
		auto iteratorBegin = workList.begin();
		if (workList.size() == 2)
		{
			iteratorBegin++;
			return std::list<std::shared_ptr<Token>>(iteratorBegin, workList.end());
		}
		iteratorBegin++;
		iteratorBegin++;
		return std::list<std::shared_ptr<Token>>(iteratorBegin, workList.end());
	}
	std::list<structToken> getStructedToken() const { return listStructToken; }
private:
	std::list<std::shared_ptr<Token>> workList;
	std::list<structToken> listStructToken;
};
#endif
