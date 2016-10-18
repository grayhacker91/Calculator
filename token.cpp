#include "token.h"

Token::Token()
{
	token=en;
	value=0;
}
TokenType Token::getTokenType()
{
	return token;
}

int Token::getValue()
{
	return value;
}

void Token::setTokenType(TokenType token)
{
	this->token=token;
}

void Token::setValue(int val)
{
	value=val;
}