#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

//UserData *g_pHeaderNode = NULL;
/** Dummy Node 로 변경 */
UserData g_HeaderNode = {0, "__DUMMY_NODE__"};

void addNewNode(int age, const char *pName, const char *pPhone);

void printNode();

void releaseAllNode();

UserData *searchByName(const char *searchName);

UserData *searchToRemoveNode(const char *searchName);

void removeNode(UserData *pPrevNode);

void addOneNodeAndDeleteTests() {
    printf("\r\nTests add One Node and Remove Node Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    printNode();
    printf("\r\n");
    UserData *pPrev = searchToRemoveNode("Hoon");
    if (pPrev != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void frontNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and Front Node Remove Tests\r\n\r\n");
    addNewNode(11, "Choi", "010-2222-2222");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    UserData *pPrev = searchToRemoveNode("Choi");
    if (pPrev != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void middleNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and middle Node Remove Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(13, "Jang", "010-3333-3333");
    addNewNode(11, "Choi", "010-2222-2222");
    printNode();
    printf("\r\n");
    UserData *pPrev = searchToRemoveNode("Jang");
    if (pPrev != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void endNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and end Node remove Tests\r\n\r\n");
    addNewNode(10, "Hoon", "010-1111-1111");
    addNewNode(11, "Choi", "010-2222-2222");
    addNewNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    UserData *pPrev = searchToRemoveNode("Jang");
    if (pPrev != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}


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
    /** Dummy Header Node 로 인해서 이제 Header Node 값이 NULL 일 가능성이 제거 */
    /** Stack 구조로 넣을 경우 */
//    newNode->pNext = &g_HeaderNode;
//    g_HeaderNode = *newNode;
    /** Queue 구조로 넣을 경우 */
    /** Header Node 의 자료의 주소 값을 참조하도록 해준다. */
    UserData *pTail = &g_HeaderNode;
    /** node 연결의 끝 부분 찾기 위한 while */
    while (pTail->pNext != NULL) {
        pTail = pTail->pNext;
    }
    pTail->pNext = newNode;
    return;
}

void printNode() {
    UserData *pTemp = &g_HeaderNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void releaseAllNode() {
    /** dummy ndoe 는 동적할당이 아니므로 알아서 제거가 되기 때문에 dummy node 다음 부터 삭제하도록 해야한다.*/
    UserData *pTemp = g_HeaderNode.pNext;
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
    /** Header Node 다음 값 초기화 */
    g_HeaderNode.pNext = NULL;
}


UserData *searchByName(const char *searchName) {
    UserData *pTemp = g_HeaderNode.pNext;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, searchName) == 0) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    return NULL;
}


UserData *searchToRemoveNode(const char *searchName) {
    UserData *pPrevNode = &g_HeaderNode;
    while (pPrevNode->pNext != NULL) {
        /** 조건에 맞는 node를 찾기 위한 조건문 */
        if (strcmp(pPrevNode->pNext->name, searchName) == 0) {
            printf("search to Remove : %s - %s\r\n", searchName, pPrevNode->pNext->name);
            /** 이전 노드에 대한 정보를 대입 */
            return pPrevNode;
        }
        pPrevNode = pPrevNode->pNext;
    }
    return NULL;
}


void removeNode(UserData *pPrevNode) {
    UserData *pDeleteNode = NULL;
    /** 삭제할 node 찾기*/
    pDeleteNode = pPrevNode->pNext;
    /** 삭제할 node 의 다음 node 를 삭제할 node 이전 node를 연결 시켜주는 과정 */
    pPrevNode->pNext = pDeleteNode->pNext;
    printf("removeNode() : %s\r\n", pDeleteNode->name);
    free(pDeleteNode);
}