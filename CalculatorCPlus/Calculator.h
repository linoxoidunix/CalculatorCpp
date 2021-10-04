#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "string"
#include <list>

class Calculator
{
public:
	Calculator();
	double operator()(std::string s);
private:
	std::list<std::string> split(std::string& s, std::string& delimiter);
};

#endif // !_CALCULATOR_H

