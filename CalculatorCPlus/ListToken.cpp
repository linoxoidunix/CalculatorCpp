#include "ListToken.h"
#include "Token.h"
#include <list>

ListToken::ListToken(std::list<std::shared_ptr<Token>> listTokens) : workList(listTokens)
{

}
