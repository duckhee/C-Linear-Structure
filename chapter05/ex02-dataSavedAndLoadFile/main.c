#include <stdio.h>
#include "uiMenu.h"
#include "dataList.h"

void initDummyData() {
    addNewNode(15, "Kim", "010-1234-1111");
    addNewNode(10, "Jang", "010-1234-4444");
    addNewNode(5, "Hoon", "010-1234-2222");
    addNewNode(7, "Choi", "010-1234-3333");
}


int main() {
    initList();
    /** file 에 저장된 데이터가 있으면 읽어오고 없으면 dummy data 가져온다. */
    if (loadListFromFile() == 0) {
        printf("init dummy data load\r\n");
        initDummyData();
        getchar();
    }
    menuHandler();
    releaseList();
    return 0;
}