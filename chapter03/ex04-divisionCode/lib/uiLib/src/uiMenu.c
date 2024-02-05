
#include "uiMenu.h"


Menu printMenu(void) {
    Menu inputMenuSelect = EXIT;
    clear();
    printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\r\n");
    scanf("%d%*c", &inputMenuSelect);
    return inputMenuSelect;
}

void menuHandler(void) {
    Menu selectMenu = EXIT;
    /** 종료 조건이 아니면 계속 해서 출력 -> EXIT = 0*/
    while ((selectMenu = printMenu()) != EXIT) {
        switch (selectMenu) {
            case NEW:
                puts("new node add");
                getchar();
                break;
            case SEARCH:
                puts("search node");
                search();
                getchar();
                break;
            case PRINT:
                puts("print node");
                printNode();
                getchar();
                break;
            case REMOVE:
                puts("remove node");
                getchar();
                break;
            default:
                break;
        }
    }
    printf("select Menu : %d\r\n", selectMenu);
    puts("Program Done");
}

void printNode(void) {
    UserData *pTemp = &g_HeaderNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void printNodeReverse(void) {
    UserData *pTemp = &g_TailNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pPrev;
    }
}

void search(void) {
    char name[32] = {0};
    printf("search name : ");
    scanf("%s", &name);
    printf("\r\nSearch input name : %s\r\n", name);
    UserData *pFindUser = searchByName(name);
    if (pFindUser != NULL) {
        printf("find node : %d, %s, %s\r\n", pFindUser->age, pFindUser->name, pFindUser->phone);
    } else {
        printf("NOT FOUND - %s\r\n", name);
    }
    getchar();
}