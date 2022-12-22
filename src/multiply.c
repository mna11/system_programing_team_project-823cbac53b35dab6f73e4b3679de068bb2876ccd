#include "multiply.h"

LINK multiply(LINK num1, LINK num2) {
    // 계산 값 
    // 선언부
    LINK answer;
    LINK num_copy;
    LINK num1_last = last_link(num1); // num1_last : num1의 마지막   //   num2_last : num2의 마지막 
    LINK num2_last = last_link(num2);
    LINK num1_int = copy_link(num1->next);
    LINK num2_int = copy_link(num2->next);
    LINK cal1;
    LINK cal2;
    LINK input;
    LINK zero_link;
    LINK save;
    char buho = 0;   // 0 -> '-'  1-> '+'

    // 계산 값 부호 결정 
    //
    if (num1->d == num2->d)
        buho = 1;

    // 소수점 계산 

    unsigned long long point = 0;
    unsigned long long point1 = 0;
    unsigned long long point2 = 0;

    num_copy = last_link(num1); //마지막에서 탐색 시작
    while (num_copy->d != '.') {
        num_copy = num_copy->prev;
        point1++;
    }

    num_copy = last_link(num2);
    while (num_copy->d != '.') {
        num_copy = num_copy->prev;
        point2++;
    }
    point = point1 + point2; //최종 소수점 위치 구함

        // '.' 제거
    num_copy = num1_int;
    for (; num_copy->d != '.'; num_copy = num_copy->next);
    del_link(num_copy);
    num_copy = num2_int;
    for (; num_copy->d != '.'; num_copy = num_copy->next);
    del_link(num_copy);

    //계산식 (손계사 원리 참조)
    cal1 = last_link(num1_int);
    unsigned long long int zero = 0;
    for (; cal1 != NULL; cal1 = cal1->prev) {
        cal2 = last_link(num2_int);
        char now = (cal1->d - '0') * (cal2->d - '0');
        char up = now / 10; //올림수
        now %= 10; //나머지 그대로

        input = char_to_list(now + '0');

        num_copy = input;
        cal2 = cal2->prev;
        for (; cal2 != NULL; cal2 = cal2->prev) {
            now = (cal1->d - '0') * (cal2->d - '0') + up;
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
        //자릿수 추가//////////////////////////////////////////////
        if (zero > 0) {
            zero_link = char_to_list('0');
            for (unsigned long long i = 1; i < zero; i++) {
                insert(zero_link, '0');
            }
            connect(zero_link, input);
            input = zero_link;
        }
        //쓸모없는 0 지우기////////////////////////////////////////
        num_copy = last_link(input);
        while (1) {
            if (num_copy->prev == NULL || num_copy->d != '0')
                break;

            LINK save = num_copy->prev;
            del_link(num_copy);
            num_copy = save;
        }

        ///////////////////////////////////////////////////////////
        //덧셈
        //수는 리버스 되어있음
        //1321 + 432 = 5641

        if (!zero) answer = copy_link(input);

        else {
            unsigned long long len1 = count(answer);
            unsigned long long len2 = count(input);
            if (len2 > len1) {
                num_copy = answer;
                answer = input;
                input = num_copy;
            }
            save = answer;
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
                save = last_link(answer);
                insert(save, '1');
            }
        }
        free_all(input);
        zero++;
    }


    unsigned long long anslen = count(answer); //부호 및 '.'추가 파트
    if (anslen > point) { //도출값이 point 보다 클 때(정수부 존재)
        num_copy = answer;
        save = answer;
        if (buho) //부호가 같을 경우 '+' 넣기
            answer = char_to_list('+');
        else
            answer = char_to_list('-');

        for (; num_copy != NULL; num_copy = num_copy->next) {
            insert(answer, num_copy->d);
        }
        free_all(save);

        num_copy = last_link(answer); //다시 뒤집고 '.'추가
        while (point--) num_copy = num_copy->prev;
        insert(num_copy, '.');
    }
    else { //소수부분만 
        num_copy = answer;
        if (buho)
            answer = char_to_list('+');
        else
            answer = char_to_list('-');
        save = answer;
        insert(save, '0');
        save = save->next;
        insert(save, '.');
        save = save->next; //+-(0.xx) 추가
        point -= anslen;

        while (point--) { //+-0.00...
            insert(save, '0');
            save = save->next;

        }
        for (; num_copy != NULL; num_copy = num_copy->next) {
            insert(save, num_copy->d);
        }
        answer = save;
    }
    answer->cnt = anslen;

    erase(answer);
    free_all(num1);
    free_all(num2);
    free_all(num1_int);
    free_all(num2_int);

    return answer;
}