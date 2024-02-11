#include <stdio.h>
#include "uiMenu.h"
#include "dataList.h"

void initDummyData() {
    addNewNode(15, "Kim", "010-1234-1111");
    addNewNode(10, "Jang", "010-1234-4444");
    addNewNode(5, "Hoon", "010-1234-2222");
    addNewNode(7, "Choi", "010-1234-3333");


}
char *getKey(void *thisPointer) {
    UserData *pUser = (UserData *) thisPointer;
    return pUser->phone;
}
int main() {
    initList();
    initDummyData();
    menuHandler();
    releaseList();
    return 0;
}