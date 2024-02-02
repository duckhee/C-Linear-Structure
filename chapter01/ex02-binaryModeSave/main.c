#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//#pragma pack(push, 1)
typedef struct _UserData {

    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext; // 파일로 읽어서 사용할 때는 의미가 없고 새로 동적 할당을 해서 다시 부여해야한다.
} UserData;
//#pragma pack(pop)

void printData(UserData *data) {
    UserData *curNode = NULL;
    curNode = data;
    while (curNode != NULL) {
        printf("[%p] %d, %s, %s [next : %p]\r\n", curNode, curNode->age, curNode->name, curNode->phone, curNode->pNext);
        curNode = curNode->pNext;
    }
    free(curNode);
}

void loadList() {
    FILE *fp = NULL;
    /** binary file 읽기 모드로 파일 열기 */
    fp = fopen("./phoneBook.txt", "rb");
    if (fp == NULL) {
        puts("file open error \r\n");
        return;
    }
    UserData pUser = {0};
    /** UserData 의 구조체 형태로 값을 하나씩 읽어오기 -> 더이상 읽을 데이터가 없을 때 종료 */
    while (fread(&pUser, sizeof(UserData), 1, fp) > 0) {
        printf("%d, %s, %s\r\n", pUser.age, pUser.name, pUser.phone);
        /** 출력 후 변수에 대한 초기화 진행 */
        memset(&pUser, '\0', sizeof(UserData));
    }
    fclose(fp);
}

int main() {
    UserData a = {10, "hoon", "010-1234-1234"};
    UserData b;
    b = a;
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
    printData(&userLists[0]);
    printf("\r\n");
    printData(userLists);

    /** text file save */
    FILE *fp = NULL;
    /** binary mode 로 파일 생성 */
    fp = fopen("./phoneBook.txt", "wb");
    if (fp == NULL) {
        puts("file open error \r\n");
        return -1;
    }
    UserData *pUser = NULL;
    pUser = &userLists[0];
    while (pUser != NULL) {
        fwrite(pUser, sizeof(UserData), 1, fp);
        pUser = pUser->pNext;
    }
    fclose(fp);
    printf("\r\nRead Binary file \r\n\r\n");
    loadList();
    return 0;
}