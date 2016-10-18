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
	Token* tokens;	//��ū���� ��� ����
	Token* postFix;	//����ǥ������� ����
public:
	Calculate();	//������
	~Calculate();	//�Ҹ���
	Token* getTokens();
	void tokener(char* expression);	//��ū������ ����
	void postFixExpression();	//����ǥ��� ��ȯ
	int priority(TokenType operation);	//������ �켱���� ����
	char transOperate(TokenType operation);	//enum�� ������ ��ȯ
	int eval();	//����ǥ��� ���
	bool exception(char* expression);	//�Է½� ����ó��
	bool bracketException(Token* expression);	//��ȣ�ȿ� �Ͼ�� ����ó��
};

#endif