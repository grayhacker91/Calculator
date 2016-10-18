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
		cout<<"Input Formula (exit: quit)";	//������ �Է��ϼ���
		cin.getline(expression,MAX);	//����� �Է�
		if(expression[0]==NULL)
		{
			continue;
		}
		if(!strcmp(expression,"quit"))
		{
			cout<<"�����մϴ�"<<endl;
			break;
		}
		if(!calculate.exception(expression))
		{
			cout<<"[����]�����Ҽ� ���� ����"<<endl;
			continue;
		}
		calculate.tokener(expression);	//��ū������ �ڸ���
		if(!calculate.bracketException(calculate.getTokens()))
		{
			cout<<"[����]�����Ҽ� ���� ����"<<endl;
			continue;
		}
		cout<<"����ǥ��� ������ : ";
		calculate.postFixExpression();	//����ǥ��� ��� �� ǥ��
		cout<<"����� : "<<calculate.eval()<<endl;
	}
	return 0;
}