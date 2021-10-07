#include "ParserListToken.h"
#include "Token.h"
#include "Executor.h"
#include "ListToken.h"
#include "CalculatedModule.h"

SmartCalcModule ParserListToken::getNearestModule(int base_priority)
{
	ListToken analizer(tokens);
	SmartToken first_token = analizer.getFirstToken();
	//if (!first_token)
	//	return SmartCalcModule();
	SmartToken secon_token = analizer.getSecondToken();
	ListTokens except_first_and_second = analizer.getAllExceptFirstAndSecond();
	ListTokens except_first = analizer.getAllExceptFirst();
	TokenIsOperand checker_is_operand;
	TokenIsOperandNew checker_type_token;
	VisiterPriority checker_priority;
	TypeToken type_firts_token = first_token->accept(&checker_type_token);
	TypeToken type_second_token = (secon_token) ? secon_token->accept(&checker_type_token) : TypeToken::TYPE_NO_TOKEN;
	bool there_are_third_tokens = analizer(except_first_and_second);
	bool there_are_second_tokens = analizer(except_first);
	SmartCalcModule resultingModule = std::make_shared<Monoplet>(except_first, first_token);
	if(type_firts_token == TypeToken::TYPE_NUMBER && type_second_token == TypeToken::TYPE_NO_TOKEN)
		resultingModule = std::make_shared<Monoplet>(except_first, first_token);
	if (type_firts_token == TypeToken::TYPE_NUMBER && there_are_second_tokens && (type_second_token == TypeToken::TYPE_BINARY_OPERAND || type_second_token == TypeToken::TYPE_UNARY_OPERAND) && base_priority >= secon_token->accept(&checker_priority))
		resultingModule = std::make_shared<MonopletWithOutRecursion>(except_first, first_token);
	else
		if (type_firts_token == TypeToken::TYPE_NUMBER && (type_second_token == TypeToken::TYPE_BINARY_OPERAND || type_second_token == TypeToken::TYPE_UNARY_OPERAND))
		{
			//if(except_first_and_second.size() == 1)
			//	resultingModule = std::make_shared<Triplet>(secon_token, first_token, analizer.getThirdToken());
			//else
				resultingModule = std::make_shared<Triplet>(secon_token, first_token, except_first_and_second);
		}
	if (type_firts_token == TypeToken::TYPE_LEFT_BRACKET)
	{
		//std::tuple<ListTokens, ListTokens> result = geTokensBeforeRightBracket(tokens);
		//resultingModule = std::make_shared<Monoplet>(std::get<0>(result), std::get<1>(result));
	}
	if (type_firts_token == TypeToken::TYPE_UNARY_OPERAND)
		if(type_second_token == TypeToken::TYPE_BINARY_OPERAND)
			resultingModule = std::make_shared<MonopletWithOutRecursion>(except_first, first_token);
		else
			resultingModule = std::make_shared<Duplet>(first_token, except_first);
	if (type_firts_token == TypeToken::TYPE_NUMBER && (type_second_token == TypeToken::TYPE_LEFT_BRACKET || type_second_token == TypeToken::TYPE_RIGHT_BRACKET))
		throw std::logic_error("Number of left brackets not equal number of right brackets");
	SmartToken first_operand = analizer.getFirstOperand();
	resultingModule->basePriority = (first_operand) ? first_operand->accept(&checker_priority) : 0;
	return resultingModule;
}

std::tuple<ListTokens, ListTokens> ParserListToken::geTokensBeforeRightBracket(const ListTokens& _tokens)
{
	ListTokens beforeRightBracket;
	ListTokens afterRightBracket;
	bool start_initialise_after_right_bracket = false;
	try
	{
		int counterLeftBracket = 0;
		TokenIsOperandNew checker_type_token;
		auto elemIterator = _tokens.begin();
		for (elemIterator = _tokens.begin(); elemIterator != _tokens.end(); elemIterator++)
		{
			if (start_initialise_after_right_bracket)
				break;
			TypeToken current_type_token = elemIterator->get()->accept(&checker_type_token);
			if (current_type_token == TypeToken::TYPE_LEFT_BRACKET)
			{
				counterLeftBracket++;
			}
			if (current_type_token == TypeToken::TYPE_RIGHT_BRACKET)
			{
				counterLeftBracket--;
			}
			if (current_type_token == TypeToken::TYPE_RIGHT_BRACKET && counterLeftBracket == 0)
			{
				start_initialise_after_right_bracket = true;
			}
			beforeRightBracket.push_back(*elemIterator);
		}
		if (!start_initialise_after_right_bracket)
			throw std::out_of_range("Didn't find corresponsable right bracket");
		else
			afterRightBracket.assign(elemIterator, _tokens.end());
	}
	catch (std::out_of_range& ex)
	{
		std::cout << "Exceptions occured: " << ex.what() << std::endl;
	}
	return std::make_tuple(beforeRightBracket, afterRightBracket);
}