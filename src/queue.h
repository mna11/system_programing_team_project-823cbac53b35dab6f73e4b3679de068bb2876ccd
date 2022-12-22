#pragma once
#include "function.h"

typedef struct Queue {
	int cnt; //������ ���� (�׽�Ʈ ��)
	LINK front; //���� ���� ���� �����
	LINK rear; //�����Ͱ� Ǫ�ÿ�û���ϸ� �ںκп� �ٿ����ϴ� �ڸ� ����� 
}queue;

int queEmpty(queue* que); //ť�� ����ִ��� üũ��
void queue_push(LINK d, queue* que); //ť�� FC* d�� Ǫ����
LINK queue_pop(queue* que); //ť�� front��(���� �տ� �ִ� ������) ����
void initQueue(queue* que); //ť�� �ʱ���� ����� ��
void digit_matching(queue* que); //ť�� ��ȸ�ϸ� digit_matching_list()�� ȣ���Ͽ� �ڸ��� ������ ��
void print_queue(queue* que); //ť�� ����ϴ� (�׽�Ʈ��)