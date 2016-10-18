#ifndef stack_h_
#define stack_h_
#define _SCL_SECURE_NO_WARNINGS

#include<iostream>
#include"token.h"

using namespace std;

template <typename T>
class Stack{
private:
	T* stack;
	int top;
	int capacity;
public:
	Stack();	//������
	Stack(int stackCapacity);
	~Stack();
	bool isEmpty() const;	//������ ����ִ��� Ȯ��
	T& getTop() const;	//top�� ��������
	void push(const T& item);	//���ÿ� �� �ֱ�
	void pop();	//�� ����
	void changeSize(T* stack,const int capacity);	//���� ũ�⺯ȯ
};

template<typename T>
Stack<T>::Stack()
{
	capacity=10;
	stack = new T[capacity];
	top = -1;
}
template<typename T>
Stack<T>::Stack(int stackCapacity)
{
	if(stackCapacity<1) throw "Stack capacity > 0";
	stack = new T[stackCapacity];
	capacity=stackCapacity;
	top = -1;
}

template<typename T>
Stack<T>::~Stack()
{
	delete[] stack;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return top==-1;
}

template<typename T>
T& Stack<T>::getTop() const
{
	if(isEmpty()) throw "Stack is empty";
	return stack[top];
}

template<typename T>
void Stack<T>::push(const T& x)
{
	if(top==(capacity-1))
	{
		changeSize(stack,capacity);
		capacity *= 2;
	}
	stack[++top] = x;
}

template<typename T>
void Stack<T>::pop()
{
	if(isEmpty()) throw "Stack is empty";
	stack[top--].~T();
}

template<typename T>
void Stack<T>::changeSize(T* stack,const int capacity)
{
	T* temp=new T[capacity*2];
	copy(stack,stack+capacity,temp);
	delete[] stack;
	stack = temp;
}

#endif