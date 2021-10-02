#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>

class IVisiter;

class Token
{
public:
	virtual ~Token() = default;
	virtual void accept(IVisiter* visiter) = 0;
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

	//friend Number operator+ (Number& leftNumber, Number& rightNumber);
private:
	double myNumber;
};

class Operand : public Token
{
public:
	virtual ~Operand() = default;
	//virtual void accept(IVisiter* visiter) = 0;
protected:
	int priority = 0;
};

class UnaryOperand : public Operand
{
public:
	virtual ~UnaryOperand() = default;
	//virtual void accept(IVisiter* visiter) = 0;
};
//
class NoOperand : public Operand
{
public:
	NoOperand() = default;
	virtual ~NoOperand() = default;
	virtual void accept(IVisiter* visiter) override;
};
//
class BinaryOperand : public Operand
{
public:
	BinaryOperand(Number& _left, Number& _right) : left(_left), right(_right) {};
	virtual ~BinaryOperand() = default;
	//virtual void accept(IVisiter* visiter) override {};

	//virtual Number calculate() = 0;
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

};

class DivOperand : public BinaryOperand
{
public:
	DivOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 3; };
	virtual ~DivOperand() = default;
	Number operator() (Number left, Number right) { return left / right; };
	virtual void accept(IVisiter* visiter) override;
};

class SubOperand : public BinaryOperand
{
public:
	SubOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 2; };
	~SubOperand() = default;
	Number operator() (Number left, Number right) { return left - right; };
	virtual void accept(IVisiter* visiter) override;
};

class SumOperand : public BinaryOperand
{
public:
	SumOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 1; };
	~SumOperand() = default;
	Number operator() (Number left, Number right) { return left + right; };
	virtual void accept(IVisiter* visiter) override;
};

class TokenFactoryBase
{
public:
	virtual Token* produce(std::string) const = 0;
	~TokenFactoryBase() = default;
};

class TokenFactory : public TokenFactoryBase
{
public:
	TokenFactory() = default;
	virtual Token* produce(std::string expression) const override 
	{
		if (expression == "*")
			return new MulOperand();
		/*if (expression == "/")
			return new DivOperand();
		if (expression == "+")
			return new SumOperand();
		if (expression == "-")
			return new SubOperand();*/
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
	~TokenFactory() = default;
};

class Printer
{
public:
	Printer() = default;
	void print(Number& number) { std::cout << number.getNumber() << std::endl; }
	void print(Number&& number) { std::cout << number.getNumber() << std::endl; }
};

#endif // !_TOKEN_H_
