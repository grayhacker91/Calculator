#include<iostream>
#include"stack.h"
#include"token.h"
#include"calculate.h"
#include<cstring>

using namespace std;

int main()
{
	while(1)
	{
		Calculate calculate;
		char expression[MAX];
		cout<<"Input Formula (exit: quit)";	//계산식을 입력하세요
		cin.getline(expression,MAX);	//연산식 입력
		if(expression[0]==NULL)
		{
			continue;
		}
		if(!strcmp(expression,"quit"))
		{
			cout<<"종료합니다"<<endl;
			break;
		}
		if(!calculate.exception(expression))
		{
			cout<<"[오류]이해할수 없는 계산식"<<endl;
			continue;
		}
		calculate.tokener(expression);	//토큰단위로 자르기
		if(!calculate.bracketException(calculate.getTokens()))
		{
			cout<<"[오류]이해할수 없는 계산식"<<endl;
			continue;
		}
		cout<<"후위표기식 계산식은 : ";
		calculate.postFixExpression();	//후위표기식 계산 및 표현
		cout<<"결과는 : "<<calculate.eval()<<endl;
	}
	return 0;
}