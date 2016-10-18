#ifndef calculate_h_
#define calculate_h_
#define _SCL_SECURE_NO_WARNINGS

#include<iostream>
#include"stack.h"
#include"token.h"

using namespace std;

#define MAX 10000

class Calculate{
private:
	Token* tokens;	//토큰별로 끊어서 저장
	Token* postFix;	//후위표기식으로 저장
public:
	Calculate();	//생성자
	~Calculate();	//소멸자
	Token* getTokens();
	void tokener(char* expression);	//토큰단위로 끊기
	void postFixExpression();	//후위표기식 변환
	int priority(TokenType operation);	//연산자 우선순위 구별
	char transOperate(TokenType operation);	//enum형 연산자 변환
	int eval();	//후위표기식 계산
	bool exception(char* expression);	//입력시 예외처리
	bool bracketException(Token* expression);	//괄호안에 일어나는 예외처리
};

#endif