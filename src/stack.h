#pragma once
#include "function.h"

typedef struct Stack {
	int cnt;
	LINK top; //���� ���� top�� �����
}stack;

void stack_push(LINK d, stack* stk); //���ÿ��� FC* d�� Ǫ���� 
LINK stack_pop(stack* stk); //������ top �����͸� ����
void initStack(stack* stk); //������ �ʱ���� �����
void print_stack(stack* stk); // ������ ����� (�׽�Ʈ ��)