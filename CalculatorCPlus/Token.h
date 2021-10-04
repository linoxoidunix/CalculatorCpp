#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>
#include <list>

class IVisiter;
class IVisiterIsOperand;

class Token
{
public:
	virtual ~Token() = default;
	virtual void accept(IVisiter* visiter) = 0;
	virtual bool accept(IVisiterIsOperand* visiter) = 0;
};

class Number : public Token
{
public:
	Number(double _myNumber = 0) : myNumber(_myNumber) {};
	virtual ~Number() = default;
	double getNumber() { return myNumber; }
	Number& operator+ (Number& rightNumber)
	{
		myNumber += rightNumber.getNumber();
		return *this;
	}
	Number& operator- (Number& rightNumber)
	{
		myNumber -= rightNumber.getNumber();
		return *this;
	}
	Number& operator* (Number& rightNumber)
	{
		myNumber *= rightNumber.getNumber();
		return *this;
	}
	Number& operator/ (Number& rightNumber)
	{
		myNumber /= rightNumber.getNumber();
		return *this;
	}
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;

private:
	double myNumber;
};

class Operand : public Token
{
public:
	virtual ~Operand() = default;
	int getPriority() { return priority; };
protected:
	int priority = 0;
};

class UnaryOperand : public Operand
{
public:
	UnaryOperand(Number& newNumber) : number(newNumber) {};
	virtual ~UnaryOperand() = default;
	virtual Number calculate(Number number) = 0;
protected:
	Number number;
};

class UnarySubOperand : public UnaryOperand
{
public:
	UnarySubOperand(Number newNumber = 0) : UnaryOperand(newNumber) { priority = 2; };
	~UnarySubOperand() = default;
	Number operator() (Number left) { return Number(0) - left; };
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number number) override;
};

class UnarySumOperand : public UnaryOperand
{
public:
	UnarySumOperand(Number newNumber = 0) : UnaryOperand(newNumber) { priority = 1; };
	~UnarySumOperand() = default;
	Number operator() (Number left) { return Number(0) + left; };
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number number) override;
};

//
class NoOperand : public Operand
{
public:
	NoOperand() = default;
	virtual ~NoOperand() = default;
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
};
//
class BinaryOperand : public Operand
{
public:
	BinaryOperand(Number& _left, Number& _right) : left(_left), right(_right) {};
	virtual ~BinaryOperand() = default;
	//virtual void accept(IVisiter* visiter) override {};
	//int getPriority() { return priority; };
	virtual Number calculate(Number left, Number right) = 0;
protected:
	Number left;
	Number right;

};
//
class MulOperand : public BinaryOperand
{
public:
	MulOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 3; };
	Number operator() (Number left, Number right) { return left * right; };
	virtual ~MulOperand() = default;
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number left, Number right) override;
};

class DivOperand : public BinaryOperand
{
public:
	DivOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 4; };
	virtual ~DivOperand() = default;
	Number operator() (Number left, Number right) { return left / right; };
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number left, Number right) override;
};

class SubOperand : public BinaryOperand
{
public:
	SubOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 2; };
	~SubOperand() = default;
	Number operator() (Number left, Number right) { return left - right; };
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number left, Number right) override;
};

class SumOperand : public BinaryOperand
{
public:
	SumOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 1; };
	~SumOperand() = default;
	Number operator() (Number left, Number right) { return left + right; };
	virtual void accept(IVisiter* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual Number calculate(Number left, Number right) override;
};

class IVisiterIsOperand
{
public:
	virtual bool visit(MulOperand*) = 0;
	virtual bool visit(DivOperand*) = 0;
	virtual bool visit(SubOperand*) = 0;
	virtual bool visit(SumOperand*) = 0;
	virtual bool visit(Number*) = 0;
	virtual bool visit(NoOperand*) = 0;
	virtual bool visit(UnarySubOperand*) = 0;
	virtual bool visit(UnarySumOperand*) = 0;
	virtual ~IVisiterIsOperand() = default;
};

class TokenIsOperand : public IVisiterIsOperand
{
public:
	TokenIsOperand() {};
	inline virtual bool visit(MulOperand*) override { return true; };
	inline virtual bool visit(DivOperand*) override { return true; };
	inline virtual bool visit(SubOperand*) override { return true; };
	inline virtual bool visit(SumOperand*) override { return true; };
	inline virtual bool visit(Number*) override { return false; };
	inline virtual bool visit(NoOperand*) override { return true; };
	inline virtual bool visit(UnarySubOperand*) override { return true; };
	inline virtual bool visit(UnarySumOperand*) override { return true; };

private:
	Token* myToken;
};


class TokenFactoryBase
{
public:
	virtual Token* produce(std::string) const = 0;
	~TokenFactoryBase() = default;
};

class BinaryTokenFactory : public TokenFactoryBase
{
public:
	BinaryTokenFactory() = default;
	virtual Token* produce(std::string expression) const override 
	{
		if (expression == "*")
			return new MulOperand();
		if (expression == "/")
			return new DivOperand();
		if (expression == "+")
			return new SumOperand();
		if (expression == "-")
			return new SubOperand();
		try
		{
			double value = std::stod(expression);
			return new Number(value);
		}
		catch (...)
		{

		}
		return new NoOperand();
	}
	~BinaryTokenFactory() = default;
};

class UnaryTokenFactory : public TokenFactoryBase
{
public:
	UnaryTokenFactory() = default;
	virtual Token* produce(std::string expression) const override
	{
		//if (expression == "*")
		//	return new MulOperand();
		//if (expression == "/")
		//	return new DivOperand();
		if (expression == "+")
			return new UnarySumOperand();
		if (expression == "-")
			return new UnarySubOperand();
		return nullptr;
		//return new NoOperand();
	}
	~UnaryTokenFactory() = default;
};


class TokensFactoryBase
{
public:
	virtual std::list<std::shared_ptr<Token>> produce(std::list<std::string> listExpression) const = 0;
	~TokensFactoryBase() = default;
};

class TokensFactory : public TokensFactoryBase
{
public:
	TokensFactory() = default;
	virtual std::list<std::shared_ptr<Token>> produce(std::list<std::string> listExpression) const override;
	~TokensFactory() = default;
};


class Printer
{
public:
	Printer() = default;
	void print(Number& number) { std::cout << number.getNumber() << std::endl; }
	void print(Number&& number) { std::cout << number.getNumber() << std::endl; }
};

#endif // !_TOKEN_H_
