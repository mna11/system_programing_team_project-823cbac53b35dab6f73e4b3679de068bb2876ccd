#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef char DATA;
struct linked_list {
    DATA d;
    unsigned long long int digit, dot, cnt;
    struct linked_list* next, * prev, * next_top, *next_rear;
};
typedef struct linked_list ELEMENT;
typedef ELEMENT* LINK;


LINK char_to_list(char s); // �����Ͱ� char�� ��� �ּ�
unsigned long long int count(LINK head); // LINK ����
void print_list(LINK head); // ���Ḯ��Ʈ ���
void print_list_test(LINK head); //[�մ�κ�] �׽�Ʈ ��¿�
void erase(LINK head); // �Ҽ��� �Ʒ� �ʿ���� 0 ����
void print_answer(LINK head); // Linked list ����ϰ� ���
void digit_matching_list(LINK head); //[�մ�κ�] �ڸ��� ����
void connect(LINK a, LINK b); // a�� b ���̱�
LINK insert(LINK p1, char x);  // p1 �ڿ� x �����ֱ�
void del_link(LINK p); // p ���� (head�� �Ұ���)
LINK copy_link(LINK b); // b ���� �� ��ȯ
char compare(LINK x, LINK y); // �� �� ��,  1:a�� �� ŭ , 2:b�� �� ŭ,  3:����
LINK small_fill(LINK x, LINK y); // ���� ���� ���ڸ��� 0 ä���� ū ���� �ڸ��� ���߱�
void downzero(LINK x, LINK y); // �Ҽ��� �ڸ� 0 ä���� �����ֱ�
LINK last_link(LINK head); // Linked list�� �� ������ �ּ� ��ȯ
void free_all(LINK a); // Linked list ������ ���� free
