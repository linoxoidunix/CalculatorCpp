#ifndef _CALCULATED_MODULE_
#define _CALCULATED_MODULE_

#include "Token.h"
#include "CONSTANTS.h"
#include <tuple>

class ICalculatedModule
{
public:
	virtual Answer calculate() = 0;
	virtual ~ICalculatedModule() = default;
	virtual bool canCalculate() = 0;
	virtual void setNumber(SmartToken& Token) = 0;
	virtual void setNumber(SmartToken&& Token) = 0;
	virtual ListTokens getRest() = 0;
	virtual void setRest(ListTokens& list) = 0;

	int basePriority = 0;
};

class Monoplet : public ICalculatedModule
{
public:
	Monoplet(ListTokens& rest_tokens, SmartToken& number) : myNumber(number), myTokens(rest_tokens) {};
	virtual Answer calculate() override;
	virtual bool canCalculate() override;
	virtual ListTokens getRest() override;
	virtual void setRest(ListTokens& list) override;
	virtual void setNumber(SmartToken& Token) override;
	virtual void setNumber(SmartToken&& Token) override;
	~Monoplet() = default;
private:
	SmartToken myNumber;
	ListTokens myTokens;
};

class MonopletWithOutRecursion : public ICalculatedModule
{
public:
	MonopletWithOutRecursion(ListTokens& rest_tokens, SmartToken& number) : myNumber(number), myTokens(rest_tokens) {};
	virtual Answer calculate() override;
	virtual bool canCalculate() override;
	virtual ListTokens getRest() override;
	virtual void setRest(ListTokens& list) override;
	virtual void setNumber(SmartToken& Token) override;
	virtual void setNumber(SmartToken&& Token) override;
	~MonopletWithOutRecursion() = default;
private:
	SmartToken myNumber;
	ListTokens myTokens;
};

class Duplet : public ICalculatedModule
{
public:
	Duplet(std::shared_ptr<Token> new_op, ListTokens rest_tokens) : op(new_op), myTokens(rest_tokens) {};
	virtual Answer calculate() override;
	virtual bool canCalculate() override;
	virtual ListTokens getRest() override;
	virtual void setRest(ListTokens& list) override;
	virtual void setNumber(SmartToken& Token) override;
	virtual void setNumber(SmartToken&& Token) override;

	~Duplet() = default;
private:
	std::shared_ptr<Token> op;
	ListTokens myTokens;
	SmartToken number;
};

//class ExpressionInTheBracket : public ICalculatedModule
//{
//public:
//	ExpressionInTheBracket(ListTokens expression) : tokensInTheBracket(expression) {};
//	ExpressionInTheBracket(ListTokens expressionInTheBracket, ListTokens expressionOutTheBracket) : tokensInTheBracket(expressionInTheBracket), tokensOutTheBracket(expressionOutTheBracket){};
//	virtual bool canCalculate() override;
//
//	virtual Answer calculate() override;
//	~ExpressionInTheBracket() = default;
//private:
//	ListTokens tokensInTheBracket;
//	ListTokens tokensOutTheBracket;
//
//};

class Triplet : public ICalculatedModule
{
public:
	Triplet(std::shared_ptr<Token> new_op, std::shared_ptr<Token> new_left_number, SmartToken _right_number) : op(new_op), left_number(new_left_number), right_number(_right_number) {};
	Triplet(std::shared_ptr<Token> new_op, std::shared_ptr<Token> new_left_number, ListTokens _expressionInTheBracket) : op(new_op), left_number(new_left_number), expressionInTheBracket(_expressionInTheBracket) {};
	virtual Answer calculate() override;
	virtual bool canCalculate() override;
	virtual ListTokens getRest() override;
	virtual void setRest(ListTokens& list) override;
	virtual void setNumber(SmartToken& Token) override;
	virtual void setNumber(SmartToken&& Token) override;
	~Triplet() = default;
private:
	std::shared_ptr<Token> op;
	SmartToken left_number;
	SmartToken right_number;
	ListTokens expressionInTheBracket;
};


#endif
