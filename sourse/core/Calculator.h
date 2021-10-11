#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "string"
#include <list>
#include <sstream>

class ResultatCalculation
{
public:
	ResultatCalculation() : resultat(std::string()) {};
	ResultatCalculation(double value) : resultat(std::to_string(value)) 
	{ 
		std::stringstream ss;
		ss << value;
		ss >> resultat;
	};
	friend std::ostream& operator << (std:: ostream& os, ResultatCalculation& entity) 
	{
		if (!entity.resultat.empty())
			os << entity.resultat;
		return os;
	}
	std::string resultat;
};

class CalculatorNew
{
public:
	CalculatorNew();
	//safety calculation with handling error
	ResultatCalculation operator()(std::string s);
	//not safety/ without handling error
	ResultatCalculation calculateDangerous(std::string s);
private:
	std::list<std::string> split(std::string& s, std::string& delimiter);
};

#endif // !_CALCULATOR_H

