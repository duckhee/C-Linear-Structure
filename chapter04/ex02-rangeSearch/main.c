#include <stdio.h>
#include "dataList.h"
#include "uiMenu.h"

void initDummyData() {
    UserData *pTemp = (UserData *) malloc(sizeof(UserData));
    pTemp->age = 5;
    strcpy(pTemp->name, "Kim");
    strcpy(pTemp->phone, "010-1234-1111");
    push(pTemp);
    pTemp->age = 8;
    strcpy(pTemp->name, "Chang");
    strcpy(pTemp->phone, "010-1234-7777");
    push(pTemp);
    pTemp->age = 6;
    strcpy(pTemp->name, "Hoon");
    strcpy(pTemp->phone, "010-1234-2222");
    push(pTemp);
    pTemp->age = 8;
    strcpy(pTemp->name, "Jang");
    strcpy(pTemp->phone, "010-1234-4444");
    push(pTemp);
    pTemp->age = 8;
    strcpy(pTemp->name, "Jung");
    strcpy(pTemp->phone, "010-1234-8888");
    push(pTemp);
    pTemp->age = 7;
    strcpy(pTemp->name, "Choi");
    strcpy(pTemp->phone, "010-1234-3333");
    push(pTemp);
    pTemp->age = 7;
    strcpy(pTemp->name, "Chae");
    strcpy(pTemp->phone, "010-1234-5555");
    push(pTemp);
}

int main() {
    initList();
    initDummyData();
    menuHandler();
    releaseList();
    return 0;
}