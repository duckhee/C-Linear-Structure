#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pPrev;
    struct _UserData *pNext;
} UserData;

void addNewNode(int age, const char *name, const char *phone);

void removeNode(UserData *pRemoveNode);

void nodeDataCopy(UserData *dst, UserData *src);

void swapNode(UserData *pLeft, UserData *pRight);

bool isEmpty();

void sortNodeByName();

void printNode(bool waitFlag);

void printReverseNode();

void releaseNode();

UserData g_HeaderNode = {0, "__DUMMY_HEADER_NODE__"};
UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};

void initNode() {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
}

void initDummyData() {
    addNewNode(5, "Kim", "010-1234-1111");
    addNewNode(6, "Hoon", "010-1234-2222");
    addNewNode(7, "Choi", "010-1234-3333");
    addNewNode(8, "Jang", "010-1234-4444");
}

void sortDataNodeTests01() {
    puts("sort data node tests - 01");
    addNewNode(5, "Hoon", "010-1234-1111");
    printNode(false);
    sortNodeByName();
    puts("");
    printNode(false);
    releaseNode();
    puts("---------------------------------");
}

void sortDataNodeTests02() {
    puts("sort data node tests - 02");
    addNewNode(5, "Hoon", "010-1234-1111");
    addNewNode(5, "Hong", "010-1234-2222");
    printNode(false);
    sortNodeByName();
    puts("");
    printNode(false);
    releaseNode();
    puts("---------------------------------");
}

void sortDataNodeTests03() {
    puts("sort data node tests - 03");
    addNewNode(5, "Hoon01", "010-1234-3333");
    addNewNode(5, "Hoon", "010-1234-1111");
    printNode(false);
    sortNodeByName();
    puts("");
    printNode(false);
    releaseNode();
    puts("---------------------------------");
}

void sortDataNodeTests04() {
    puts("sort data node tests - 04");
    initDummyData();
    printNode(false);
    sortNodeByName();
    puts("");
    printNode(false);
    releaseNode();
    puts("---------------------------------");
}

int main() {
    initNode();
//    initDummyData();
//    printNode(false);
//    releaseNode();
    sortDataNodeTests01();
    /** test 실행 시 잠시 멈추기 위한 getchar */
    getchar();
    sortDataNodeTests02();
    /** test 실행 시 잠시 멈추기 위한 getchar */
    getchar();
    sortDataNodeTests03();
    /** test 실행 시 잠시 멈추기 위한 getchar */
    getchar();
    sortDataNodeTests04();
    /** test 실행 시 잠시 멈추기 위한 getchar */
    getchar();
    return 0;
}

bool isEmpty() {
    if (g_HeaderNode.pNext == &g_TailNode) {
        return true;
    }
    return false;
}

void printNode(bool waitFlag) {
    UserData *pTemp = &g_HeaderNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
    if (waitFlag) {
        getchar();
    }
}

void printReverseNode() {
    UserData *pTemp = &g_TailNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pPrev);
        pTemp = pTemp->pPrev;
    }
}

void releaseNode() {
    UserData *pTemp = g_HeaderNode.pNext;
    UserData *pDeleteNode = NULL;
    while (pTemp != &g_TailNode) {
        pDeleteNode = pTemp;
        pTemp = pTemp->pNext;
        printf("Delete: %d, %s, %s\r\n",
               pDeleteNode->age, pDeleteNode->name, pDeleteNode->phone);
        free(pDeleteNode);
    }
    initNode();
}

void addNewNode(int age, const char *name, const char *phone) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    memset(pNewNode, '\0', sizeof(UserData));
    pNewNode->age = age;
    strcpy(pNewNode->name, name);
    strcpy(pNewNode->phone, phone);
    pNewNode->pNext = NULL;
    pNewNode->pPrev = NULL;

    /** Stack 구조 */
    /** Header node 부터 값을 삽입 */
    /** new node 에 관계 설정 */
//    pNewNode->pPrev = &g_HeaderNode;
//    pNewNode->pNext = g_HeaderNode.pNext;

    /** Header node 에 관계 설정 */
//    UserData *pHeaderNextNode = g_HeaderNode.pNext;
//    g_HeaderNode.pNext = pNewNode;
//    pHeaderNextNode->pPrev = pNewNode;

    /** Queue 구조 */
    /** Tail node 부터 값을 삽입 */
    /** new node 에 관계 설정 */
    pNewNode->pNext = &g_TailNode;
    pNewNode->pPrev = g_TailNode.pPrev;

    /** Tail node 에 관계 설정 */
    UserData *pTailPrevNode = g_TailNode.pPrev;
    g_TailNode.pPrev = pNewNode;
    pTailPrevNode->pNext = pNewNode;
}

void removeNode(UserData *pRemoveNode) {
    /** deleted node 에 대한 관계 정보를 저장하기 위한 변수 */
    UserData *pDeletedPrevNode = pRemoveNode->pPrev;
    UserData *pDeletedNextNode = pRemoveNode->pNext;
    /** deleted Node */
    UserData *pDeletedNode = pRemoveNode;
    /** 관계 정리 */
    pDeletedPrevNode->pNext = pDeletedNextNode;
    pDeletedNextNode->pPrev = pDeletedPrevNode;
    printf("Deleted Node - %s\r\n", pDeletedNode->name);
    free(pDeletedNode);
}

/** src mode 의 값을 dst node 에 복사 */
void nodeDataCopy(UserData *dst, UserData *src) {
    dst->age = src->age;
    strcpy(dst->name, src->name);
    strcpy(dst->phone, src->phone);
}

/** node 의 위치를 변경 */
void swapNode(UserData *pLeft, UserData *pRight) {
    /** 주소 값만 참조하는 것이 아니라 변수를 선언해서 해당 값을 가지고 있기 위한 double pointer */
    UserData temp = *pLeft;
    nodeDataCopy(pLeft, pRight);
    nodeDataCopy(pRight, &temp);
}

/** name 기준으로 정령 */
void sortNodeByName() {
    if (isEmpty()) {
        return;
    }

    UserData *pTemp = g_HeaderNode.pNext;
    UserData *pSelectedNode = NULL;
    UserData *pCompareNode = NULL;
    /** node 를 순차적으로 방분하면서 값을 비교하기 위한 반복문 */
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pSelectedNode = pTemp;
        pCompareNode = pTemp->pNext;
        /** 비교하기 위한 값을 비교하기 위한 반복문 */
        while (pCompareNode != NULL && pCompareNode != &g_TailNode) {
            /** 순서가 빠른 문자를 정렬하기 위한 조건 문 -> pSelectedNode 의 값이 더 나중인 경우 */
            if (strcmp(pSelectedNode->name, pCompareNode->name) > 0) {
                pSelectedNode = pCompareNode;
            }
            /** 비교할 문자를 이동 */
            pCompareNode = pCompareNode->pNext;
        }
        /** 비교가 된 문자가 있을 경우 node 교환 */
        if (pTemp != pSelectedNode) {
            swapNode(pTemp, pSelectedNode);
        }
        pSelectedNode = NULL;
        pTemp = pTemp->pNext;
    }
}