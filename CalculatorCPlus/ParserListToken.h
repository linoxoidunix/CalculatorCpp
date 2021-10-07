#ifndef _PARSER_LIST_TOKEN_
#define _PARSER_LIST_TOKEN_
#include "CONSTANTS.h"


class ParserListToken
{
public:
	ParserListToken(ListTokens new_tokens) : tokens(new_tokens) {};
	SmartCalcModule getNearestModule(int base_priorite = 0);
private:
	ListTokens tokens;
	std::tuple<ListTokens, ListTokens> geTokensBeforeRightBracket(const ListTokens& _tokens);
};
#endif // !_PARSER_LIST_TOKEN_

