#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "string"
#include <list>

class Calculator
{
public:
	Calculator() = default;
	double operator()(std::string s);
private:
	std::list<std::string> split(std::string& s, std::string& delimiter);
};

class CalculatorNew
{
public:
	CalculatorNew();
	//safety calculation with handling error
	double operator()(std::string s);
	//not safety/ without handling error
	double calculateDangerous(std::string s);

private:
	std::list<std::string> split(std::string& s, std::string& delimiter);
};

#endif // !_CALCULATOR_H

