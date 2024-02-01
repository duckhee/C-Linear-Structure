#include <stdio.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

int main() {
    UserData a = {10, "hoon", "010-1234-1234"};
    UserData b;
    b = a;
    printf("%d. %s. %s.\r\n", b.age, b.name, b.phone);
    UserData userLists[4] = {
            {20, "tester01", "010-1234-1234", NULL},
            {21, "tester02", "010-1234-2222", NULL},
            {22, "tester03", "010-1234-3333", NULL},
            {23, "tester04", "010-1234-4444", NULL},
    };
    /** 연결 리스트 형태로 만들기 위한 link */
    userLists[0].pNext = &userLists[1];
    userLists[1].pNext = &userLists[2];
    userLists[2].pNext = &userLists[3];
    userLists[3].pNext = NULL;
    /** 연결에 대한 링크 과정을 이해하기 위한 이름 출력 */
    printf("%s\r\n", userLists[0].name);
    printf("%s\r\n", userLists[0].pNext->name);
    printf("%s\r\n", userLists[0].pNext->pNext->name);
    printf("%s\r\n", userLists[0].pNext->pNext->pNext->name);

    /** 연결 리스트를 출력 하는 방법 */
    UserData *cur = NULL;
    cur = &userLists[0];
    while (cur != NULL) {
        printf("[%p] %d, %s. %s. [next : %p]\r\n", cur, cur->age, cur->name, cur->phone, cur->pNext);
        cur = cur->pNext;
    }


    return 0;
}