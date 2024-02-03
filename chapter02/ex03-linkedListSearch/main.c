#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;


void addNode(int age, const char *pName, const char *pPhone);

void printNode(UserData *pNode);

void releaseNode(UserData *pNode);

/** 찾은 데이터의 주소 값을 반환 */
UserData *searchByName(const char *pName);

UserData *g_pHeaderNode = NULL;

void initDumpyData() {
    addNode(10, "Hoon", "010-1111-1111");
    addNode(11, "Choi", "010-2222-2222");
    addNode(13, "Jang", "010-3333-3333");

}

void searchNameTests() {
    searchByName("Hoon");
    searchByName("Choi");
    searchByName("Jang");
    searchByName("Kim");
}

int main() {
    initDumpyData();
    UserData *pHead = g_pHeaderNode;
    searchNameTests();
    printNode(pHead);
    releaseNode(pHead);


    return 0;
}

void addNode(int age, const char *pName, const char *pPhone) {
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    memset(newNode, '\0', sizeof(UserData));
    newNode->age = age;
    strcpy(newNode->name, pName);
    strcpy(newNode->phone, pPhone);
    newNode->pNext = NULL;
    if (g_pHeaderNode == NULL) {
        g_pHeaderNode = newNode;
    } else {
        UserData *pTail = g_pHeaderNode;
        while (pTail->pNext != NULL)
            pTail = pTail->pNext;
        pTail->pNext = newNode;
    }
}

void printNode(UserData *pNode) {
    UserData *pTemp = pNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void releaseNode(UserData *pNode) {
    UserData *pTemp = g_pHeaderNode;
    UserData *pDeletedNode = NULL;
    while (pTemp != NULL) {
        pDeletedNode = pTemp;
        pTemp = pTemp->pNext;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeletedNode, pDeletedNode->age, pDeletedNode->name,
               pDeletedNode->phone,
               pDeletedNode->pNext);
        free(pDeletedNode);
    }
    g_pHeaderNode = NULL;
}

/** 찾은 데이터의 주소 값을 반환 */
UserData *searchByName(const char *pName) {
    UserData *pTemp = g_pHeaderNode;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, pName) == 0) {
            printf("find name : %s\r\n", pName);
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    printf("not found name\r\n");
    return NULL;
}

