#include "dataList.h"

extern UserData g_HeaderNode = {0, "__DUMMY_HEADER_NODE__"};
extern UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};
static unsigned int g_nodeCounter = 0;

/** 현재 node 에서 관리가 되고 있는 node 의 갯수 */
unsigned int getListCount() {
    return g_nodeCounter;
}

/** 초기 데이터 삽입 */
void initList(void) {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
    g_nodeCounter = 0;
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
    ++g_nodeCounter;
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
    g_nodeCounter++;
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

    --g_nodeCounter;
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

    ++g_nodeCounter;
}

UserData *deQueue(void) {
    if (isEmpty()) {
        return NULL;
    }
    UserData *pDeQueue = g_HeaderNode.pNext;
    g_HeaderNode.pNext = pDeQueue->pNext;
    pDeQueue->pNext->pPrev = pDeQueue->pPrev;

    --g_nodeCounter;
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
    if (pMin > pTemp->age) {
        *pCount = 0;
        return NULL;
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

/** index 를 생성하는 함수 -> age로 정렬해서 인덱스 배열을 반환 해준다. */
void **makeIndexAge(int *pCount) {
    /** 인자로 받은 포인터 변수의 값을 0으로 초기화 */
    *pCount = 0;
    if (isEmpty()) {
        return NULL;
    }
    /** UserData 에 대한 index 정렬해서 반환할 배열*/
    UserData **indexList = NULL;
    /** 반환할 index 배열에 대한 동적 할당 */
    indexList = malloc(sizeof(UserData *) * getListCount());
    memset(indexList, '\0', sizeof(UserData *) * getListCount());
    *pCount = getListCount();

    UserData *pTemp = g_HeaderNode.pNext;
    /** 현재 node 에 대한 정보를 가지고 있는 것을 담고 있는 index 생성 */
    for (int i = 0; pTemp != &g_TailNode; i++) {
        indexList[i] = pTemp;
        pTemp = pTemp->pNext;
    }
    int nodeTotalLength = getListCount();
    /** bubble 정렬 */
    for (int i = 0; i < nodeTotalLength - 1; ++i) {
        for (int j = i + 1; j < nodeTotalLength; ++j) {
            if (indexList[i]->age > indexList[j]->age) {
                UserData *pSwapTemp = indexList[i];
                indexList[i] = indexList[j];
                indexList[j] = pSwapTemp;
            }
        }
    }

    /** 정렬된 값을 확인하기 위한 출력 */
//    for (int i = 0; i < nodeTotalLength; i++) {
//        printf("%d, %s, %s\r\n", indexList[i]->age, indexList[i]->name, indexList[i]->phone);
//    }
    return indexList;
}

/** 해당 나이에 대한 범위를 가지고 있는 인덱스를 반환 하는 함수 */
void **searchByIndexAgeRange(int min, int max, unsigned int *pCount) {
    /** 입력 받은 갯수를 저장할 변수에 대한 0으로 초기화 */
    *pCount = 0;
    /** 전체 데이터 node 에 대한 갯수를 저장할 변수 */
    unsigned int cntTotal = 0;
    UserData **pIndexList = (UserData **) makeIndexAge(&cntTotal);
    /** 최소 값이 위치하는 값과 최대 값이 위치하는 값의 위치를 담을 변수 */
    int idxMin = -1;
    int idxMax = 0;
    /** 정렬이 되어 있는 배열이므로 다음 위치 부터 동작 시키기 위한 진행 위치에 대한 값을 저장하기 위한 변수 */
    unsigned int i = 0;

    /** 입력 받은 최소 값 범위에 존재 하는 값이 있는지 찾는 반복문 */
    for (i = 0; i < cntTotal; i++) {
        if (pIndexList[i]->age >= min) {
            idxMin = i;
            idxMax = i;
            break;
        }
    }

    /** 최소 값 범위에 맞는 값이 존재할 경우 */
    if (idxMin >= 0) {
        /** 정령이 되어 있으믈 다음 값이 찾은 값보다 크거나 같다 */
        for (; i < cntTotal; ++i) {
            if (pIndexList[i]->age <= max) {
                idxMax = i;
            } else if (pIndexList[i]->age > max) {
                break;
            }
        }

        /** 해당 되는 데이터의 갯수를 찾는 것 */
        int length = idxMax - idxMin + 1;
        /** 최대 값보다 클 경우 NULL 반환 */
        if ((*pIndexList + idxMin)->age > max) {
            printf("get list find age - %d, min range - %d max range - %d\r\n", (*pIndexList + idxMin)->age, min, max);
            return NULL;
        }
        /** 반환할 node를 담아서 줄 리스트 */
        UserData **pSelected = malloc(sizeof(void *) * length);
        memset(pSelected, '\0', sizeof(void *) * length);
        /** 범위에 해당 되는 최소 값 시작 지점 부터 최대 값이 담겨 있는 길이 만큼 메모리 복사 */
        memcpy(pSelected, pIndexList + idxMin, sizeof(void *) * length);
        /** 전체  index 를 만들어둔 메모리 해제 */
        free(pIndexList);
        /** 전체 데이터의 길이를 반환 */
        *pCount = length;
        return pSelected;
    }
    /** 값이 없을 경우 반환 */
    free(pIndexList);
    return NULL;

}
