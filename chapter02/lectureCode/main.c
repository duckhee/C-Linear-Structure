#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

void addNewNode(int age, const char *pName, const char *pPhone);

void printNode();

void releaseAllNode();

UserData *searchByName(const char *searchName);

UserData *searchToRemoveNode(UserData **ppPrevNode, const char *searchName);

void removeNode(UserData *pPrevNode);

void addOneNodeAndDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add One Node and Remove Node Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    printNode();
    printf("\r\n");
    if (searchToRemoveNode(&pPrev, "Hoon") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void frontNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and Front Node Remove Tests\r\n\r\n");
    addNewNode(11, "Choi", "010-2222-2222");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    if (searchToRemoveNode(&pPrev, "Choi") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void middleNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and middle Node Remove Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(13, "Jang", "010-3333-3333");
    addNewNode(11, "Choi", "010-2222-2222");
    printNode();
    printf("\r\n");
    if (searchToRemoveNode(&pPrev, "Jang") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void endNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and end Node remove Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(11, "Choi", "010-2222-2222");
    addNewNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    if (searchToRemoveNode(&pPrev, "Jang") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

UserData *g_pHeaderNode = NULL;

int main() {
    /** 데이터를 하나 넣고 삭제하는 테스트 */
    addOneNodeAndDeleteTests();
    /** 세개의 노드 데이터를 넣고 맨 처음 노드에 대한 삭제하는 테스트 */
    frontNodeDeleteTests();
    /** 세개의 노드 데이터를 넣고 중간 노드에 대한 삭제하는 테스트 */
    middleNodeDeleteTests();
    /** 세개의 노드 데이터를 넣고 마지막 노드에 대한 삭제하는 테스트 */
    endNodeDeleteTests();
    return 0;
}


void addNewNode(int age, const char *pName, const char *pPhone) {
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    /** 새로운 node 초기화 */
    memset(newNode, '\0', sizeof(UserData));
    /** 값 대입 */
    newNode->age = age;
    strcpy(newNode->name, pName);
    strcpy(newNode->phone, pPhone);
    newNode->pNext = NULL;
    /** Header Node 값이 NULL 일 경우 */
    /** 처음 데이터 넣기 */
    if (g_pHeaderNode == NULL) {
        g_pHeaderNode = newNode;
        return;
    }
    /** Stack 구조로 넣을 경우 */
//    newNode->pNext = g_pHeaderNode;
//    g_pHeaderNode = newNode;
    /** Queue 구조로 넣을 경우 */
    UserData *pTail = g_pHeaderNode;
    /** node 연결의 끝 부분 찾기 위한 while */
    while (pTail->pNext != NULL) {
        pTail = pTail->pNext;
    }
    pTail->pNext = newNode;
    return;
}

void printNode() {
    UserData *pTemp = g_pHeaderNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void releaseAllNode() {
    UserData *pTemp = g_pHeaderNode;
    /** 지울 node 에 대한 정보를 담기 위한 객체 */
    UserData *pDeleteNode = NULL;
    while (pTemp != NULL) {
        pDeleteNode = pTemp;
        pTemp = pTemp->pNext;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeleteNode, pDeleteNode->age, pDeleteNode->name,
               pDeleteNode->phone,
               pDeleteNode->pNext);
        /** node 에 대한 삭제 */
        free(pDeleteNode);
    }
    /** Header Node 초기화 */
    g_pHeaderNode = NULL;
}


UserData *searchByName(const char *searchName) {
    UserData *pTemp = g_pHeaderNode;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, searchName) == 0) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    return NULL;
}


UserData *searchToRemoveNode(UserData **ppPrevNode, const char *searchName) {
    UserData *pCurrentNode = g_pHeaderNode;
    UserData *pPrevNode = NULL;
    while (pCurrentNode != NULL) {
        /** 조건에 맞는 node를 찾기 위한 조건문 */
        if (strcmp(pCurrentNode->name, searchName) == 0) {
            printf("search to Remove : %s - %s\r\n", searchName, pCurrentNode->name);
            /** 이전 노드에 대한 정보를 대입 */
            *ppPrevNode = pPrevNode;
            return pCurrentNode;
        }
        pPrevNode = pCurrentNode;
        pCurrentNode = pCurrentNode->pNext;
    }
    return NULL;
}


void removeNode(UserData *pPrevNode) {
    UserData *pDeleteNode = NULL;
    /** 삭제할 node의 이전 노드의 값이 NULL 일 경우 처리 */
    if (pPrevNode == NULL) {
        /** Header Node 가 NULL 일 경우 처리 */
        if (g_pHeaderNode == NULL) {
            return;
        }
        /** 삭제할 node의 이전 값이 NULL 이면서 Header Node 가 NULL 이 아닐 경우 처리 */
        /** Header Node 의 다음 node를 첫 번째 Node 로 변경해주는 것 */
        pDeleteNode = g_pHeaderNode;
        g_pHeaderNode = pDeleteNode->pNext;
        printf("removeNode() : %s\r\n", pDeleteNode->name);
        free(pDeleteNode);
        return;
    }
    /** 삭제할 node 찾기*/
    pDeleteNode = pPrevNode->pNext;
    /** 삭제할 node 의 다음 node 를 삭제할 node 이전 node를 연결 시켜주는 과정 */
    pPrevNode->pNext = pDeleteNode->pNext;
    printf("removeNode() : %s\r\n", pDeleteNode->name);
    free(pDeleteNode);
}