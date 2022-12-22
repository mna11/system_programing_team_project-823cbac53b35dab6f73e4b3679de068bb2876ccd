#include "minus.h"

LINK minus(LINK a, LINK b) {

    /////////////////////////////////////////////////////////////
    //�����
    LINK ans;
    LINK num_copy;
    LINK num1;
    LINK num2;
    char buho = 1; //��ȣ (+,- : 1,0)
    char big_num; //�񱳰� (1,2,3)
    unsigned long long int point_count = 0; //���� ��ġ(0~)
    char now = 0; // �����Ʈ������ ���簪
    char down = 0; // �����Ʈ������ ������

    /////////////////////////////////////////////////////////////
    //���밪�� ū ���� a�� ������ �� Ȥ�� ���� 0�̴�?
    big_num = compare(a, b);
    if (big_num == 3) { // ���� ���밪�� ���� ��
        ans = char_to_list('+');
        insert(ans, '.');
        insert(ans, '0');
        free_all(a); free_all(b);
        ans->cnt = count(ans);
        return ans;
    }

    if (big_num == 2) { // b�� �� ũ�� b�� a�� �̵�
        num_copy = a;
        a = b;
        b = num_copy;

        buho = 0;
    }
    /////////////////////////////////////////////////////////////
    //��ȣ�� a�� ��ȣ�� ���󰡵���
    //buho = a->d == '+' ? 1 : 0;  // +�� 1, -�� 0

    /////////////////////////////////////////////////////////////
    //���� ��ȣ ���ְ� ���밪����
    num1 = a->next; num1->prev = NULL; free(a);
    num2 = b->next; num2->prev = NULL; free(b);

    /////////////////////////////////////////////////////////////
    //�Ҽ��� �� ���߱�
    num2 = small_fill(num1, num2);

    ////////////////////////////////////////////////////////////
    //�Ҽ��� �Ʒ� ���߱�
    downzero(num1, num2);

    ////////////////////////////////////////////////////////////
    //�Ҽ��� �ڸ��� ���� �� ����
    a = last_link(num1);
    b = num2;
    for (; a->d != '.'; a = a->prev) point_count++; del_link(a);
    for (; b->d != '.'; b = b->next); del_link(b);

    ///////////////////////////////////////////////////////////
    //���
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

    ans = copy_link(num1);
    free_all(num1); free_all(num2);
    ////////////////////////////////////////////////////////////
    //�� ���̱�
    a = last_link(ans);
    for (int _ = point_count; _ > 0; _--) a = a->prev; //[�մ�κ�] point_count�� ����ϱ� ���ؼ�
    insert(a, '.');

    ////////////////////////////////////////////////////////////
    //�� 0 ���ֱ�
    ans->dot = point_count; //[�մ�κ�] �Ҽ��� �ڸ� ������ ���� �߰���
    erase(ans); //[�մ�κ�] erase() ���ο��� �ݺ��� �ѹ� �������� ans->dot--
    point_count = ans->dot; //[�մ�κ�]

    ///////////////////////////////////////////////////////////
    //��ȣ ���̱�
    a = ans;
    ans = char_to_list(buho ? '+' : '-');
    connect(ans, a);

    //�� 0 ���ֱ�
    a = ans->next;
    for (; a->next->d != '.' && a->d == '0'; a = a->next) del_link(ans->next);

    //[�մ�κ�] �����Ʈ ���� 
    ans->cnt = count(ans);
    ans->dot = ans->cnt - point_count;
    digit_matching_list(ans);
    return ans;
}