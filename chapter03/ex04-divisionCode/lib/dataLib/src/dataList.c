#include "dataList.h"

extern UserData g_HeaderNode = {0, "__DUMMY_HEADER_NODE__"};
extern UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};

/** 초기 데이터 삽입 */
void initList(void) {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
}

/** 데이터 정리 및 삭제 */
void releaseList(void) {
    UserData *pTemp = g_HeaderNode.pNext;
    UserData *pDeleteNode = NULL;
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pDeleteNode = pTemp;
        pTemp = pTemp->pNext;
        free(pDeleteNode);
    }
    initList();
}

bool isEmpty() {
    if (g_HeaderNode.pNext == &g_TailNode) {
        return true;
    }
    return false;
}

/** FILO First In Last Out */
void push(UserData *pNewUser) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    memcpy(pNewNode, pNewUser, sizeof(UserData));
    pNewNode->pNext = NULL;
    pNewNode->pPrev = NULL;

    /** 먼저 들어간 데이터 밑에 쌓이는 구조를 가져야 하므로 Header 부터 값이 들어 가야 한다. */
    pNewNode->pPrev = &g_HeaderNode;
    pNewNode->pNext = g_HeaderNode.pNext;

    /** HeaderNode 에 대한 관계를 재 정의 */
    g_HeaderNode.pNext->pPrev = pNewNode;
    g_HeaderNode.pNext = pNewNode;
}

UserData *pop(void) {
    if (isEmpty()) {
        return NULL;
    }
    /** 반환할 node 에 대한 정의 */
    UserData *pPopNode = g_HeaderNode.pNext;
    /** 데이터 삭제를 위한 위치 재 조정 */
    g_HeaderNode.pNext = pPopNode->pNext;
    pPopNode->pNext->pPrev = pPopNode->pPrev;
    return pPopNode;
}

/** FIFO First In First Out */
void enQueue(UserData *pNewUser) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    memcpy(pNewNode, pNewUser, sizeof(UserData));
    pNewNode->pNext = NULL;
    pNewNode->pPrev = NULL;

    /** queue 형태는 먼저 들어간 node 가 먼저 나오는 구조를 가져야 하므로 Tail 부터 값이 들어 가야 한다. */
    pNewNode->pNext = &g_TailNode;
    pNewNode->pPrev = g_TailNode.pPrev;
    /** Tail 에 대한 관계 재 조정 */
    UserData *pPrevTail = g_TailNode.pPrev;
    pPrevTail->pNext = pNewNode;
    g_TailNode.pPrev = pNewNode;
}

UserData *deQueue(void) {
    if (isEmpty()) {
        return NULL;
    }
    UserData *pDeQueue = g_HeaderNode.pNext;
    g_HeaderNode.pNext = pDeQueue->pNext;
    pDeQueue->pNext->pPrev = pDeQueue->pPrev;
    return pDeQueue;
}

UserData *searchByName(const char *searchName) {
    UserData *pSearchNode = g_HeaderNode.pNext;
    while (pSearchNode != NULL) {
        if (strcmp(pSearchNode->name, searchName) == 0) {
            return pSearchNode;
        }
        pSearchNode = pSearchNode->pNext;
    }
    return NULL;
}