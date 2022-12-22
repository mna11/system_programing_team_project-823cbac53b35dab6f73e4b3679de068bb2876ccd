#include "minus.h"

LINK minus(LINK a, LINK b) {
    LINK answer;
    LINK num_copy;
    LINK num1;
    LINK num2;
    char sign = 1; //��ȣ (+,- : 1,0)
    char big;
    unsigned long long int point_count = 0; //'.'��ġ ���
    char now = 0; //  ���簪
    char down = 0; //  ������

    // a =[���밪 ū ���]
    big = compare(a, b);


    if (big == 2) { // b->a (b>a)
        num_copy = a;
        a = b;
        b = num_copy;
        sign = 0;
    }

    if (big == 3) { // ���� ���밪�� ���� ��
        answer = char_to_list('+');
        insert(answer, '.');
        insert(answer, '0');
        free_all(a); free_all(b);
        answer->cnt = count(answer);
        return answer;
    }

    //���밪���� ����
    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);

    //�ڸ��� ������ ���߱�
    num2 = small_fill(num1, num2);


    //�ڸ��� �Ҽ��κ� ���߱�
    downzero(num1, num2);

    //�Ҽ��� �ڸ��� ���� �� ����
    a = last_link(num1);
    b = num2;
    for (; a->d != '.'; a = a->prev) point_count++; del_link(a);
    for (; b->d != '.'; b = b->next); del_link(b);

    //��� �ڵ�
    a = last_link(num1);
    b = last_link(num2);

    while (a != NULL) {
        char number1 = a->d - '0';
        char number2 = b->d - '0';
        char check = 0;
        if (number2 - down > number1) { number1 += 10; check = 1; };
        now = number1 - number2 + down;
        down = check ? -1 : 0;
        a->d = now + '0';
        a = a->prev;
        b = b->prev;
    }

    answer = copy_link(num1);
    free_all(num1); free_all(num2);

    //�� ���̱�
    a = last_link(answer);
    for (int _ = point_count; _ > 0; _--) a = a->prev; // point_count�� ����ϱ� ���ؼ�
    insert(a, '.');


    //�� 0 ���ֱ�
    answer->dot = point_count; //�Ҽ��� �ڸ� ������ ���� �߰���
    erase(answer); //erase() ���ο��� �ݺ��� �ѹ� �������� ans->dot--
    point_count = answer->dot;

    //��ȣ ���̱�
    a = answer;
    answer = char_to_list(sign ? '+' : '-');
    connect(answer, a);

    //�� 0 ���ֱ�
    a = answer->next;
    for (; a->next->d != '.' && a->d == '0'; a = a->next) del_link(answer->next);

    // �����Ʈ ���� 
    answer->cnt = count(answer);
    answer->dot = answer->cnt - point_count;
    digit_matching_list(answer);
    return answer;
}