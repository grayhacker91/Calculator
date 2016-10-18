#include "calculate.h"

Calculate::Calculate()
{
	tokens=new Token[MAX];
	postFix=new Token[MAX];
}

Calculate::~Calculate()
{
	delete[] tokens;
	delete[] postFix;
}

Token* Calculate::getTokens()
{
	return tokens;
}

void Calculate::tokener(char* expression)
{
	int i=0, j=0;	//i=�ݺ��� ����, j=tokens����
	while(expression[i]!=NULL)
	{
		if(expression[i]=='(')
		{
			tokens[j].setTokenType(leftbrackets);
			tokens[j++].setValue(0);
		}
		else if(expression[i]==')')
		{
			tokens[j].setTokenType(rightbrackets);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='^')
		{
			tokens[j].setTokenType(squares);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='*')
		{
			tokens[j].setTokenType(multis);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='/')
		{
			tokens[j].setTokenType(divides);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='%')
		{
			tokens[j].setTokenType(mods);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='+')
		{
			tokens[j].setTokenType(pluss);
			tokens[j++].setValue(0);
		}
		else if(expression[i]=='-')
		{
			if(expression[0]=='-')
			{
				while(expression[i]=='-')
				{
					tokens[j].setTokenType(minusSigns);
					tokens[j++].setValue(0);
					i++;
				}
				i--;
			}
			else
			{
				if(expression[i+1]=='-')
				{
					tokens[j].setTokenType(minuss);
					tokens[j++].setValue(0);
					while(expression[i+1]=='-')
					{
						tokens[j].setTokenType(minusSigns);
						tokens[j++].setValue(0);
						i++;
					}
				}
				else
				{
					tokens[j].setTokenType(minuss);
					tokens[j++].setValue(0);
				}
			}
		}
		else if(isdigit(expression[i]))
		{
			int temp=(expression[i]-48);	//temp�ڸ��� ��ȯ �ӽú���
			while(isdigit(expression[i+1]))
			{
				temp*=10;
				temp+=(expression[i+1]-48);
				i++;
			}
			tokens[j].setTokenType(operands);
			tokens[j++].setValue(temp);	//����ǥ��
		}
		i++;
	}
}

int Calculate::priority(TokenType operation)
{
	if (operation == leftbrackets)
	{
		return 0;
	}
	else if (operation == pluss || operation == minuss)
	{
		return 1;
	}
	else if (operation == multis || operation == divides || operation == mods)
	{
		return 2;
	}
	else if(operation == squares)
	{
		return 3;
	}
	else		//���׿����� ���̳ʽ���ȣ
		return 4;
}

char Calculate::transOperate(TokenType operation)
{
	switch(operation)
	{
	case en:
		return '#';
	case leftbrackets:
		return '(';
	case rightbrackets:
		return ')';
	case minusSigns:
		return '~';
	case squares:
		return '^';
	case multis:
		return '*';
	case divides:
		return '/';
	case mods:
		return '%';
	case pluss:
		return '+';
	case minuss:
		return '-';
	case operands:
		return '0';
	}
}

void Calculate::postFixExpression()
{
	Stack<TokenType> stack;
	int i=0,j=0;	//i�� �ݺ��� ����
	for(Token x=tokens[i];x.getTokenType()!=en;i++)
	{
		x=tokens[i];
		if(x.getTokenType()==operands)
		{
			cout<<x.getValue()<<" ";
			postFix[j].setTokenType(x.getTokenType());
			postFix[j++].setValue(x.getValue());
		}
		else if(x.getTokenType()==leftbrackets)
		{
			stack.push(x.getTokenType());
		}
		else if(x.getTokenType()==rightbrackets)
		{
			while(stack.getTop()!=leftbrackets)
			{
				cout<<transOperate(stack.getTop())<<" ";
				postFix[j].setTokenType(stack.getTop());
				postFix[j++].setValue(0);
				stack.pop();
			}
			stack.pop();	//�°�ȣ ��
		}
		else
		{
			while((!stack.isEmpty()) && priority(stack.getTop()) >= priority(x.getTokenType()))
			{
				if(stack.getTop()==minusSigns && x.getTokenType()==minusSigns)
				{
					break;
				}
				cout<<transOperate(stack.getTop())<<" ";
				postFix[j].setTokenType(stack.getTop());
				postFix[j++].setValue(0);
				stack.pop();
			}
			stack.push(x.getTokenType());
		}
	}
	stack.pop();	//������ �ݺ������� ���̴� �� ����
	while(!stack.isEmpty())
	{
		cout<<transOperate(stack.getTop())<<" ";
		postFix[j].setTokenType(stack.getTop());
		postFix[j++].setValue(0);
		stack.pop();
	}
	cout<<endl;
}

int Calculate::eval()
{
	Stack<int> stack;
	Token x;
	int i=0;
	for(x=postFix[i];x.getTokenType()!=en;i++)
	{
		x=postFix[i];
		if(x.getTokenType()==operands)
		{
			stack.push(x.getValue());
		}
		else if(x.getTokenType()==minusSigns)
		{
			int temp;	//���̳ʽ���ȣ ��� �ӽú���
			temp=stack.getTop();
			stack.pop();
			temp*=-1;
			stack.push(temp);
		}
		else if(x.getTokenType()==squares)
		{
			int temp1, temp2, temp3;	//���� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			temp3=temp2;
			for(int j=1;j<temp1;j++)
			{
				temp3=temp3*temp2;
			}
			stack.push(temp3);
		}
		else if(x.getTokenType()==multis)
		{
			int temp1, temp2;	//���� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			temp2*=temp1;
			stack.push(temp2);
		}
		else if(x.getTokenType()==divides)
		{
			int temp1, temp2;	//���� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			if(temp1==0)
			{
				cout<<"[����]������� �и� 0�� �ɼ� �����ϴ�"<<endl;
				return 0;
			}
			temp2/=temp1;
			stack.push(temp2);
		}
		else if(x.getTokenType()==mods)
		{
			int temp1, temp2;	//���� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			if(temp1==0)
			{
				cout<<"[����]������� �и� 0�� �ɼ� �����ϴ�"<<endl;
				return 0;
			}
			temp2%=temp1;
			stack.push(temp2);
		}
		else if(x.getTokenType()==pluss)
		{
			int temp1, temp2;	//���ϱ� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			temp2+=temp1;
			stack.push(temp2);
		}
		else if(x.getTokenType()==minuss)
		{
			int temp1, temp2;	//���� ��� �ӽú���
			temp1=stack.getTop();
			stack.pop();
			temp2=stack.getTop();
			stack.pop();
			temp2-=temp1;
			stack.push(temp2);
		}
	}
	return stack.getTop();
}

bool Calculate::exception(char *expression)
{
	int i=0;
	int leftcount=0, rightcount=0;	//�°�ȣ ���ȣ ����
	while(expression[i]!=0)
	{
		if(!((expression[i]>=48 && expression[i]<=57) || expression[i]==' ' || expression[i]=='%' || 
			expression[i]=='(' || expression[i]==')' || expression[i]=='*' || expression[i]=='+' ||
			expression[i]=='-' || expression[i]=='/' || expression[i]=='^'))	//�ٸ����� �Է� ����ó��
		{
			return false;
		}
		if(expression[i]=='%' || expression[i]=='*' || expression[i]=='+' ||
			expression[i]=='/' || expression[i]=='^' || expression[i]=='-')
		{
			if(expression[i+1]=='%' || expression[i+1]=='*' || expression[i+1]=='+' ||
				expression[i+1]=='/' || expression[i+1]=='^' || expression[i+1]=='-')	//������ ���޾� �Է� ����ó��
			{
				if(!(expression[i]=='-' && expression[i+1]=='-'))	//--�ΰ�� ����
				{
					return false;
				}
			}
			else if(expression[i+1]==')')	//������ ���� ���ȣ�Է� ����ó��
			{
				return false;
			}
		}
		if((expression[i]>=48 && expression[i]<=57))	//�ǿ����� ���޾� �Է� ����ó��
		{
			if(expression[i+1]==' ')
			{
				if((expression[i+2]>=48 && expression[i+2]<=57))
				{
					return false;
				}
			}
			else if(expression[i+1]=='(')	//�ǿ����� ���� �ٷ� �°�ȣ�� �ð��
			{
				return false;
			}
		}
		if(expression[i]=='(')
		{
			leftcount++;
			if(expression[i+1]=='%' || expression[i+1]=='*' || expression[i+1]=='+' ||
				expression[i+1]=='/' || expression[i+1]=='^' || expression[i+1]=='-')	//�°�ȣ ���� ������ ����ó��
			{
				return false;
			}
			
		}
		else if(expression[i]==')')
		{
			rightcount++;
			for(int j=0;j<=i;j++)	//���ȣ ���� �������� Ȯ��
			{
				if(expression[j]=='(')
				{
					break;
				}
				else if(j==i)
				{
					return false;
				}
			}
			if(!(expression[i+1]=='%' || expression[i+1]=='*' || expression[i+1]=='+' ||
				expression[i+1]=='/' || expression[i+1]=='^' || expression[i+1]=='-' || expression[i+1]==0))	//���ȣ �ڿ� �ǿ����� ����
			{
				return false;
			}
		}

		i++;
	}
	if(leftcount!=rightcount)
	{
		return false;
	}
	return true;
}

bool Calculate::bracketException(Token *expression)
{
	int i=0;
	while(expression[i].getTokenType()!=en)
	{
		if(expression[i].getTokenType()==leftbrackets)
		{
			if(expression[i+1].getTokenType()==rightbrackets)	//�°�ȣ �� �ٷ� ���ȣ�� �� ���
			{
				return false;
			}
			else if(expression[i+1].getTokenType()==operands)
			{
				if(expression[i+2].getTokenType()==rightbrackets)
				{
					return false;
				}
			}
		}
		i++;
	}
	return true;
}