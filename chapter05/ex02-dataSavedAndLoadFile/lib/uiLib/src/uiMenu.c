
#include "uiMenu.h"


void searchByAge();

Menu printMenu(void) {
    Menu inputMenuSelect = EXIT;
    clear();
    printf("[1]New\t[2]Search\t[3]Search age\t[4]Print\t[4]Remove\t[0]Exit\r\n");
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
                sortByKey();
                getchar();
                break;
            case SEARCH_RANGE:
                puts("search range node");
                getchar();
                break;
            case PRINT:
                puts("print node");
                printNode(false);
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

void printNode(bool waitFlag) {
    MyNode *pTemp = g_HeaderNode.pNext;
    UserData *pTempUser = NULL;
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pTempUser = pTemp->pData;
        printf("[%p] %d, %s, %s, key value - %s next Node -> [%p]\r\n", pTemp, pTempUser->age, pTempUser->name,
               pTempUser->phone, pTemp->GetKey(pTemp->pData),
               pTemp->pNext);
        pTemp = pTemp->pNext;
    }
    if (waitFlag) {
        getchar();
    }
}

void printNodeReverse(bool waitFlag) {
    MyNode *pTemp = g_TailNode.pPrev;
    UserData *pTempUser = NULL;
    while (pTemp != NULL && pTemp != &g_HeaderNode) {
        pTempUser = pTemp->pData;
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTempUser->age, pTemp->GetKey(pTemp->pData),
               pTempUser->phone,
               pTemp->pNext);
        pTemp = pTemp->pPrev;
    }
    if (waitFlag) {
        getchar();
    }
}
