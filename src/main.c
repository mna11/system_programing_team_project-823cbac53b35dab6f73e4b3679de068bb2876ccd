#include "postfix.h"
#include "multiply.h"
#include "minus.h"
#include "plus.h"

LINK evaluate(queue* postfix);

int main(void) {
	printf("[ ======= Welcome to infinite calulator made by TEAM 7! ======= ] \n");
	printf("Enter the expression in infix notation.\n");
	printf("Input  : ");
	queue* postfix = toPostFix(); //ť������ postfix�� �������
	digit_matching(postfix); //�ڸ��� ������
	//print_queue(postfix); //�׽�Ʈ��
	LINK result = evaluate(postfix); 
	printf("Result : ");
	print_list(result); //��� ��� ���
	putchar('\n');
	free_all(result);
	return 0;
}

LINK evaluate(queue* postfix) {
	stack* stk = (stack*)malloc(sizeof(stack));
	initStack(stk);
	LINK res = (LINK)malloc(sizeof(LINK));
	for (LINK p = postfix->front; p != NULL; p = p->next_rear) {
		if (p->d == '+' && p->cnt > 1 || p->d == '-' && p->cnt > 1) { //���ڰ� ���� ��� ���ÿ� �־���
			stack_push(p, stk);
		}
		else { //�����ڰ� ���� ���
			LINK d1;
			LINK d2;
			d2 = stack_pop(stk); // ������ ������ �� ���� ������
			d1 = stack_pop(stk);

			//�����ڿ� ���� ��ȣ�� ���ؼ� �˸��� ��� �Լ��� ȣ����
			if (p->d == '+') {
				if (d1->d == '+' && d2->d == '+') {
					res = plus(d1, d2);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					res = minus(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d1->d = '+';
					res = minus(d2, d1);
				}
				else { // d1->d == '-' && d2->d == '-'
					res = plus(d1, d2);
				}
			}
			else if (p->d == '-') {
				if (d1->d == '+' && d2->d == '+') {
					res = minus(d1, d2);
				}
				else if (d1->d == '+' && d2->d == '-') {
					d2->d = '+';
					res = plus(d1, d2);
				}
				else if (d1->d == '-' && d2->d == '+') {
					d2->d = '-';
					res = plus(d1, d2);
				}
				else { //d1->d == '-' && d2->d == '-'
					d2->d = '+';
					d1->d = '+';
					res = minus(d2, d1);
				}
			}
			else if (p->d == '*') {
				res = multiply(d1, d2);
			}
			stack_push(res, stk); //����� ���ÿ� ����
		}
	}
	res = stack_pop(stk); //���ÿ��� ��� �ϳ��� ���������Ƿ� ���� ���� ����̴�.
	free(stk);
	return res;
}