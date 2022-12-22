#include "stack.h"

void stack_push(LINK d, stack* stk) {
	d->next_top = stk->top; //d�� next_top�� ���� ������ top�� ����Ŵ, d�� ���߿� �˵� ���, ���� top ��ġ�� ������Ű�� ����
	stk->top = d; //������ ž�� d�� ������ 
	stk->cnt++; //������ ������ ���� ������Ŵ 
}

LINK stack_pop(stack* stk) {
	LINK t = stk->top; //������ ž ���� FC* t�� �����Ŵ
	stk->top = stk->top->next_top; //���� ž ���� ž���� �ٲ� (������ �״´� �������� ��, ������ �ι�° �����ͷ� ž�� �ٲ۴ٴ� ����)
	stk->cnt--; //������ ������ ���� ���ҽ�Ŵ
	return t; //���� ž ���� ��ȯ�� 
}

void initStack(stack* stk) {
	stk->cnt = 0; //�ʱ���� �����̹Ƿ� ������ ���� 0�̴�.
	stk->top = NULL; //�ʱ���� �����̹Ƿ� NULL
}

void print_stack(stack* stk)
{
	for (stack* p = stk; p->top != NULL; p->top = p->top->next_top) { //������ ž�� NULL�� �ɶ����� �� �����
		print_list(p->top); //����Ʈ�� ����� 
	}
}