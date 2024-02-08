#include "dataList.h"

extern UserData g_HeaderNode = {0, "__DUMMY_HEADER_NODE__"};
extern UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};

/** 초기 데이터 삽입 */
void initList(void) {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
}

void addNewNode(int age, const char *name, const char *phone) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    memset(pNewNode, '\0', sizeof(UserData));
    pNewNode->age = age;
    strcpy(pNewNode->name, name);
    strcpy(pNewNode->phone, phone);
    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;
    /** set new node relation ship */
    pNewNode->pNext = &g_TailNode;
    pNewNode->pPrev = g_TailNode.pPrev;
    /** Tail 에 대한 관계 재 조정 */
    UserData *pPrevTail = g_TailNode.pPrev;
    pPrevTail->pNext = pNewNode;
    g_TailNode.pPrev = pNewNode;
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

/** 나이로 정렬 하는 함수 */
void sortByAge() {
    if (isEmpty()) {
        return;
    }
    UserData *pTemp = g_HeaderNode.pNext;
    UserData *pSelectedNode = NULL;
    UserData *pCompareNode = NULL;
    /** 선택 정렬이므로 반복문 두개 나온다. */
    while (pTemp != NULL && pTemp != g_TailNode.pPrev) {
        pSelectedNode = pTemp;
        pCompareNode = pTemp->pNext;
        while (pCompareNode != NULL && pCompareNode != &g_TailNode) {
            if (pSelectedNode->age > pCompareNode->age) {
                pSelectedNode = pCompareNode;
            }
            pCompareNode = pCompareNode->pNext;
        }
        if (pTemp != pSelectedNode) {
            swapNode(pTemp, pSelectedNode);
        }
        pSelectedNode = NULL;
        pTemp = pTemp->pNext;
    }
}

/** 범위 검색 */
void **searchByAgeRange(int min, int max, int *pCount) {
    /** 입력 받은 pointer 변수를 0으로 초기화 */
    *pCount = 0;
    UserData *pMin = NULL;
    UserData *pMax = NULL;
    UserData *pTemp = g_HeaderNode.pNext;
    /** 최소 값보다 큰 값이 존재 하는 데이터 찾기 */
    while (pTemp != &g_TailNode) {
        if (pTemp->age >= min) {
            pMin = pTemp;
            pMax = pTemp;
            break;
        }
        pTemp = pTemp->pNext;
    }
    /** 찾은 최소 값이 있을 경우 */
    if (pMin != NULL) {
        /** 최소 값의 다음 위치로 포인터 이동 */
        pTemp = pMin->pNext;
    } else {
        /** 최소 값을 찾지 못하면 Header node 로 이동 */
        pTemp = g_HeaderNode.pNext;
    }
    /** 범위에 대한 탐색을 위한 반복문 */
    while (pTemp != &g_TailNode) {
        /** 범위 안에 있는 값이 있을 경우 */
        if (pTemp->age >= min && pTemp->age <= max) {
            /** 최대 값 node 에 범위에 맞는 node 로 초기화 */
            pMax = pTemp;
        } else if (pTemp->age > max) {
            /** 최대 값보다 큰 값이면 반복문 탈출 */
            break;
        }
        pTemp = pTemp->pNext;
    }
    /** 최소 값과 최대 값이 있을 경우 */
    if (pMin != NULL && pMax != NULL) {
        UserData *pTmp = pMin;
        int cnt = 1;
        /** 범위에 해당 되는 node 의 숫자를 확인하기 위한 반복문 */
        while (pTmp != pMax) {
            ++cnt;
            pTmp = pTmp->pNext;
        }
        /** 총 갯수를 포인터 변수의 값에 넣어주기 */
        *pCount = cnt;
        /** 반환할 node 의 배열 */
        void **pNodePtrList = malloc(sizeof(void *) * cnt);

        pTmp = pMin;
        int i = 0;
        for (; pTmp != pMax; ++i) {
            pNodePtrList[i] = pTmp;
            pTmp = pTmp->pNext;
        }
        /** 최대 값을 배열의 마지막에 넣어준다. */
        pNodePtrList[i] = pMax;

        return pNodePtrList;
    }

    return NULL;
}