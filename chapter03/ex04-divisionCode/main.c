#include <stdio.h>
#include "dataList.h"
#include "uiMenu.h"

void initDummyData() {
    UserData pNewUser = {11, "Choi", "010-2222-2222"};

    enQueue(&pNewUser);
    pNewUser.age = 10;
    strcpy(pNewUser.name, "Hoon");
    strcpy(pNewUser.phone, "010-1111-1111");
    enQueue(&pNewUser);
    pNewUser.age = 13;
    strcpy(pNewUser.name, "Jang");
    strcpy(pNewUser.phone, "010-3333-3333");
    enQueue(&pNewUser);
}

int main() {
    initList();
    initDummyData();
    menuHandler();
    releaseList();
    return 0;
}