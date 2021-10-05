#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>
#include <iostream>
#include <list>

class IVisiterPriority;
class IVisiterIsOperand;
class IvisiterCalculator;
class Number;

class Token
{
public:
	virtual ~Token() = default;
	virtual int accept(IVisiterPriority* visiter) = 0;
	virtual bool accept(IVisiterIsOperand* visiter) = 0;
	virtual std::string print() = 0;
};

class Number : public Token
{
public:
	Number(double _myNumber = 0) : myNumber(_myNumber) {};
	virtual ~Number() = default;
	double getNumber() const { return myNumber; }
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
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	
	friend std::ostream& operator<< (std::ostream& os, const Number& left)
	{
		os << left.getNumber();
		return os;
	}
	virtual std::string print() override
	{
		auto s = std::to_string(myNumber);
		if (s[s.size() - 1] == '0')
			for (size_t i = s.size() - 1; s[i] == '0'; i--)
				s.erase(i, 1);
		if (s[s.size() - 1] == '.')
			s.erase(s.size() - 1, 1);
		return s;
	}



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
	UnaryOperand(Number&& newNumber) : number(newNumber) {};
	UnaryOperand() : UnaryOperand(0) {};

	virtual ~UnaryOperand() = default;
	virtual Number& calculate(Number& number) = 0;
protected:
	Number number;
};

class UnarySubOperand : public UnaryOperand
{
public:
	UnarySubOperand(Number newNumber = 0) : UnaryOperand(newNumber) { priority = 2; };
	~UnarySubOperand() = default;
	Number operator() (Number left) { return Number(0) - left; };
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "-"; };
	virtual Number& calculate(Number& number) override;
};

class UnarySumOperand : public UnaryOperand
{
public:
	UnarySumOperand(Number newNumber = 0) : UnaryOperand(newNumber) { priority = 1; };
	~UnarySumOperand() = default;
	Number operator() (Number left) { return Number(0) + left; };
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "+"; };
	virtual Number& calculate(Number& number) override;
};

//
class NoOperand : public Operand
{
public:
	NoOperand() = default;
	virtual ~NoOperand() = default;
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	//virtual std::tuple<Number, std::list<std::shared_ptr<Token>>> accept(IvisiterCalculator* visiter) override;
};
//
class BinaryOperand : public Operand
{
public:
	BinaryOperand(Number& _left, Number& _right) : left(_left), right(_right) {};
	BinaryOperand() : left(Number(0)), right(Number(0)) {};
	virtual ~BinaryOperand() = default;
	virtual Number& calculate(Number& left, Number& right) = 0;
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
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "*"; };
	virtual Number& calculate(Number& left, Number& right) override;
};

class DivOperand : public BinaryOperand
{
public:
	DivOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 4; };
	virtual ~DivOperand() = default;
	Number operator() (Number left, Number right) { if (right.getNumber() == 0) throw std::out_of_range("divided by 0"); return left / right; };
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "/"; };
	virtual Number& calculate(Number& left, Number& right) override;
};

class SubOperand : public BinaryOperand
{
public:
	SubOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 2; };
	~SubOperand() = default;
	Number operator() (Number left, Number right) { return left - right; };
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "-"; };
	virtual Number& calculate(Number& left, Number& right) override;
};

class SumOperand : public BinaryOperand
{
public:
	SumOperand(Number _left = 0, Number _right = 0) :BinaryOperand(_left, _right) { priority = 1; };
	~SumOperand() = default;
	Number operator() (Number left, Number right) { return left + right; };
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "+"; };
	virtual Number& calculate(Number& left, Number& right) override;
};

class LeftBracketOperand : public UnaryOperand
{
public:
	LeftBracketOperand() :UnaryOperand() { priority = INT_MIN; };
	~LeftBracketOperand() = default;
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return "("; };
	virtual Number& calculate(Number& leftNumber) override { return leftNumber; };
};

class RightBracketOperand : public UnaryOperand
{
public:
	RightBracketOperand() :UnaryOperand() { priority = INT_MAX; };
	~RightBracketOperand() = default;
	virtual int accept(IVisiterPriority* visiter) override;
	virtual bool accept(IVisiterIsOperand* visiter) override;
	virtual std::string print() override { return ")"; };
	virtual Number& calculate(Number& leftNumber) override { return leftNumber; };
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
	virtual bool visit(LeftBracketOperand*) = 0;
	virtual bool visit(RightBracketOperand*) = 0;
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
	inline virtual bool visit(LeftBracketOperand*) override { return true; };
	inline virtual bool visit(RightBracketOperand*) override { return false; };
private:
	Token* myToken;
};


class TokenFactoryBase
{
public:
	virtual std::shared_ptr<Token> produce(std::string) const = 0;
	~TokenFactoryBase() = default;
};

class BinaryTokenFactory : public TokenFactoryBase
{
public:
	BinaryTokenFactory() = default;
	virtual std::shared_ptr<Token> produce(std::string expression) const override 
	{
		if (expression == "*")
			return std::make_shared<MulOperand>();
		if (expression == "/")
			return std::make_shared<DivOperand>();
		if (expression == "+")
			return std::make_shared<SumOperand>();
		if (expression == "-")
			return std::make_shared<SubOperand>();
		//if (expression == "(")
		//	return std::make_shared<LeftBracketOperand>();
		//if (expression == ")")
		//	return std::make_shared<RightBracketOperand>();
		try
		{
			double value = std::stod(expression);
			return std::make_shared<Number>(value);
		}
		catch (...)
		{

		}
		return std::shared_ptr<Token>();
	}
	~BinaryTokenFactory() = default;
};

class UnaryTokenFactory : public TokenFactoryBase
{
public:
	UnaryTokenFactory() = default;
	virtual std::shared_ptr<Token> produce(std::string expression) const override
	{
		if (expression == "+")
			return std::make_shared<UnarySumOperand>();
		if (expression == "-")
			return std::make_shared<UnarySubOperand>();
		if (expression == "(")
			return std::make_shared<LeftBracketOperand>();
		if (expression == ")")
			return std::make_shared<RightBracketOperand>();
		return std::shared_ptr<Token>();
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

#include <algorithm>

class Printer
{
public:
	Printer() = default;
	template<typename T>
	inline void print(T&& number) { std::cout << number << std::endl; };
	inline std::string printToString(const std::shared_ptr<Token>& token) { return token->print(); }
	inline std::string printToString(std::list<std::shared_ptr<Token>>& list) { std::string result;  std::for_each(list.begin(), list.end(), [&result, this](const std::shared_ptr<Token> currentToken) {result += this->printToString(currentToken); }); return result; }
};

#endif // !_TOKEN_H_
