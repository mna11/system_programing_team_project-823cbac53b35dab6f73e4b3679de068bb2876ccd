#include "division.h"

LINK division(LINK a, LINK b) {
    char check; // ũ�� ��
    boolean sign; // +�̸� 1, -�̸� 0:
    sign = (num1->d == num2->d);

    // case 1. b = 0
    if (b->next->d == '0' && b->next->next->d == '.' && b->next->next->next == NULL) {
        printf("error");
        free_all(a); free_all(b);
        break;
    }

    // case 2. a���� b�� �� ū�� Ȯ��
    check = compare(a, b);
    if (check == 2) {
        LINK quo = char_to_list('+'); insert(quo, '0');
        LINK remain = //���� �κ� �״�� ����?
            free_all(a); free_all(b);
        return quo;   //b�� �� ũ�� 0�� �������� �״�� ��ȯ
    }

    //��ȣ ���� �� ��ȣ ����

    if (check == 3) {
        LINK quo = char_to_list(buho ? '+' : '-'); insert(quo, '1');
        free_all(a); free_all(b);
        return quo;  //a�� b�� ���� ��.
    }

    else { //case 3. a�� �� Ŭ ��.
        LINK quo = minus(LINK a, LINK b);
        unsigned long long int i = 0;
        while (compare(a, b) != 1) {
            LINK quo = minus(LINK quo, LINK b);
            i++;
        }

        if (sign)
            LINK quo = char_to_list('+'); insert(quo);
        else
            LINK quo = char_to_list('-'); Insert(quo, i);
        return quo;

        free(a); free(b);
    }
}