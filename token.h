#ifndef token_h_
#define token_h_
#define _SCL_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

typedef enum{
	en , leftbrackets , rightbrackets , minusSigns , squares , multis , divides , mods , pluss , minuss, operands
}TokenType;	//Á¤ÀÇ

class Token{
private:
	TokenType token;
	int value;
public:
	Token();
	void setTokenType(TokenType token);
	void setValue(int val);
	TokenType getTokenType();
	int getValue();
};

#endif

