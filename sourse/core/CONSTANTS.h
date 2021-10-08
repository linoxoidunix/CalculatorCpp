#ifndef _CONSTATNTS_CALCULATOR_
#define _CONSTATNTS_CALCULATOR_

#include <list>
#include <memory>
#include <tuple>

class Token;
class Number;
class ICalculatedModule;

typedef std::shared_ptr<Token> SmartToken;
typedef std::list<std::shared_ptr<Token>> ListTokens;
typedef std::tuple<Number, ListTokens> Answer;
typedef std::shared_ptr<ICalculatedModule> SmartCalcModule;


#endif // !_CONSTATNTS_CALCULATOR_

