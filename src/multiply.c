#include "multiply.h"

LINK multiply(LINK num1, LINK num2) {
    // ��� �� 
    // �����
    LINK ans;
    LINK num_copy;
    LINK num1_last = last_link(num1); // num1_last : num1�� ������   //   num2_last : num2�� ������ 
    LINK num2_last = last_link(num2);
    LINK num1_int = copy_link(num1->next);
    LINK num2_int = copy_link(num2->next);
    LINK mul1;
    LINK mul2;
    LINK input;
    LINK zero_link;
    LINK save;
    char buho = 0;   // 0 -> '-'  1-> '+'
    
    // ��� �� ��ȣ ���� 
    //
    if (num1->d == num2->d)
        buho = 1;
    
    // �Ҽ��� ��� 
    //
    unsigned long long point = 0;
    num_copy = num1_last;
    for (; num_copy->d != '.'; num_copy = num_copy->prev) point++;//3 
    num_copy = num2_last;
    for (; num_copy->d != '.'; num_copy = num_copy->prev) point++;//3+4=7
    //printf("%d",point);

    // �� ����
    num_copy = num1_int;
    for (; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    num_copy = num2_int;
    for (; num_copy->d != '.'; num_copy = num_copy->next); del_link(num_copy);
    
    // ���/////////////////////////////////////////////////////////////////////
    // num2->d* num1->d .. �ؼ� ��� �� 9���� ũ�� ����ĭ�� �ø�
    // num2->next->d* num1-> .. ...���� ��� �� ĭ�� +
    // 
    mul1 = last_link(num1_int);
    unsigned long long int zero = 0;
    for (; mul1 != NULL; mul1 = mul1->prev) {
        mul2 = last_link(num2_int);
        char now = (mul1->d - '0') * (mul2->d - '0');
        char up = now / 10;
        now %= 10;

        input = char_to_list(now + '0');

        num_copy = input;
        mul2 = mul2->prev;
        for (; mul2 != NULL; mul2 = mul2->prev) {
            now = (mul1->d - '0') * (mul2->d - '0') + up;
            up = now / 10;
            now %= 10;
            insert(num_copy, now + '0');
            num_copy = num_copy->next;
        }
        if (up != 0) insert(num_copy, up + '0');
        num_copy = last_link(input);

        for (; num_copy->prev != NULL; num_copy = num_copy->prev) {
            if (num_copy->d != '0')
                break;
        }
        //�ڸ��� �߰�//////////////////////////////////////////////
        if (zero > 0) {
            zero_link = char_to_list('0');
            for (unsigned long long i = 1; i < zero; i++) {
                insert(zero_link, '0');
            }
            connect(zero_link, input);
            input = zero_link;
        }
        //������� 0 �����////////////////////////////////////////
        num_copy = last_link(input);
        while (1) {
            if (num_copy->prev == NULL || num_copy->d != '0')
                break;

            LINK save = num_copy->prev;
            del_link(num_copy);
            num_copy = save;
        }

        ///////////////////////////////////////////////////////////
        //����
        //���� ������ �Ǿ�����
        //1321 + 432 = 5641

        if (!zero) ans = copy_link(input);

        else {
            unsigned long long len1 = count(ans);
            unsigned long long len2 = count(input);
            if (len2 > len1) {
                num_copy = ans;
                ans = input;
                input = num_copy;
            }
            save = ans;
            num_copy = input;
            now = 0;
            up = 0;
            for (; num_copy != NULL; num_copy = num_copy->next) {
                now = num_copy->d - '0' + save->d - '0' + up;
                up = now / 10;
                now = now % 10;
                save->d = now + '0';
                save = save->next;
            }
            for (; up && save != NULL; save = save->next) {
                now = save->d - '0' + up;
                up = now / 10;
                now = now % 10;
                save->d = now + '0';
            }
            if (up) {
                save = last_link(ans);
                insert(save, '1');
            }
        }
        free_all(input);
        zero++;
    }

    // ��ȣ �߰��ϰ� ������ �Ҽ��� ��� �� ����ŭ �Ҽ��� �ڿ������� ī��Ʈ
    //
    unsigned long long anslen = count(ans);
    if (anslen > point) {
        num_copy = ans;
        save = ans;
        if (buho) ans = char_to_list('+');
        else ans = char_to_list('-');

        for (; num_copy != NULL; num_copy = num_copy->next) {
            insert(ans, num_copy->d);
        }
        free_all(save);

        num_copy = last_link(ans);
        while (point--) num_copy = num_copy->prev;
        insert(num_copy, '.');
    }
    else {
        num_copy = ans;
        if (buho) ans = char_to_list('+');
        else ans = char_to_list('-');
        save = ans;
        insert(save, '0'); save = save->next; insert(save, '.'); save = save->next;
        point -= anslen;
        while (point--) {
            insert(save, '0');
            save = save->next;
        }
        for (; num_copy != NULL; num_copy = num_copy->next) {
            insert(save, num_copy->d);
        }
    }
    ans->cnt = anslen;

    erase(ans);
    free_all(num1);
    free_all(num2);
    free_all(num1_int);
    free_all(num2_int);
    
    return ans;
}