#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

UserData *g_pHeaderNode = NULL;

void addNewNode(int age, const char *pName, const char *pPhone);

void printNode(UserData *pNode);

void releaseAllNode(UserData *pNode);

void initDumpyData();

int main() {
    initDumpyData();
    UserData *pTemp = g_pHeaderNode;
    printNode(pTemp);
    releaseAllNode(pTemp);
    return 0;
}

void addNewNode(int age, const char *pName, const char *pPhone) {

    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    memset(pNewNode, '\0', sizeof(UserData));

    pNewNode->age = age;
    strcpy(pNewNode->name, pName);
    stpcpy(pNewNode->phone, pPhone);
    pNewNode->pNext = NULL;
    if (g_pHeaderNode == NULL) {
        g_pHeaderNode = pNewNode;
    } else {
        // 현재와 같은 경우는 stack 의 구조를 가진다.
//        pNewNode->pNext = g_pHeaderNode;
//        g_pHeaderNode = pNewNode;
        // 현재 구조는 Queue 의 구조를 가진다.
        UserData *pTail = g_pHeaderNode;
        while (pTail->pNext != NULL)
            pTail = pTail->pNext;

        pTail->pNext = pNewNode;
    }
}


void printNode(UserData *pNode) {
    while (pNode != NULL) {
        printf("[%p] %d, %s, %s, pNext - [%p]\r\n", pNode, pNode->age, pNode->name, pNode->phone, pNode->pNext);
        pNode = pNode->pNext;
    }
}

void releaseAllNode(UserData *pNode) {
    UserData *pTemp = pNode;
    UserData *pDeleteNode = NULL;
    while (pTemp != NULL) {
        pDeleteNode = pTemp;
        pTemp = pTemp->pNext;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeleteNode, pDeleteNode->age, pDeleteNode->name,
               pDeleteNode->phone,
               pDeleteNode->pNext);
        free(pDeleteNode);
    }

}

void initDumpyData() {
    printf("Insert dumpy data\r\n");
    addNewNode(10, "hoon", "010-1111-2222");
    addNewNode(12, "hoon2", "010-3333-2222");
    addNewNode(13, "hoon3", "010-1111-3333");
    addNewNode(13, "hoon4", "010-1111-3333");
    printf("Insert dumpy data\r\n");
}