#pragma once
#include "function.h"
#include "queue.h"
#include "stack.h"

DATA priority(DATA data1, DATA data2); //������ �켱���� üũ��
DATA isOperator(DATA op); //���������� �ƴ��� �Ǵ���
queue* toPostFix(); //�Է� ���� �����͸� �޾Ƽ� queue ������ postfix�� ��ȯ��