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
	ListToken(ListTokens listTokens);
	ListToken() : ListToken(ListTokens()) {};
	std::shared_ptr<Token> getLeftToken()
	{
		if (workList.empty())
			return std::shared_ptr<Token>();
		return workList.front();
	}
	std::shared_ptr<Token> getOperandToken()
	{
		if (workList.size() < 2)
			return std::shared_ptr<Token>();
		auto iteratorBegin = workList.begin();
		if (dynamic_cast<Operand*>(iteratorBegin->get()))
			return *iteratorBegin;
		iteratorBegin++;
		return *(iteratorBegin);
	}
	ListTokens getRighToken()
	{
		if (workList.size() < 2)
			return ListTokens();
		auto iteratorBegin = workList.begin();
		if (workList.size() == 2)
		{
			iteratorBegin++;
			return ListTokens(iteratorBegin, workList.end());
		}
		iteratorBegin++;
		iteratorBegin++;
		return ListTokens(iteratorBegin, workList.end());
	}
	ListTokens getNoFirtsElement()
	{
		if (workList.size() < 2)
			return ListTokens();
		auto iteratorBegin = workList.begin();
		iteratorBegin++;
		return ListTokens(iteratorBegin, workList.end());
	}
	SmartToken getFirstToken();
	SmartToken getSecondToken();
	SmartToken getThirdToken();
	ListTokens getAllExceptFirst();
	ListTokens getAllExceptFirstAndSecond();
	SmartToken getFirstOperand();
	inline bool isEmpty() { return workList.empty(); };
	bool operator () (ListTokens& newList) { return !newList.empty(); }
	ListToken& operator =(const ListToken& list) { workList = list.workList; return *this; }
	std::list<structToken> getStructedToken() const { return listStructToken; }
private:
	ListTokens workList;
	std::list<structToken> listStructToken;
};
#endif
