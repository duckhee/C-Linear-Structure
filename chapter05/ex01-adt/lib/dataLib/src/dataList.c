#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataList.h"

extern MyNode g_HeaderNode = {0};
extern MyNode g_TailNode = {0};
/** 이 파일 안에서만 유효한 staic 변수 */
static unsigned int g_listCount = 0;

unsigned int getListCount() {
    return g_listCount;
}

bool isEmpty() {
    if (g_HeaderNode.pNext == &g_TailNode || g_HeaderNode.pNext == NULL) {
        return true;
    }
    return false;
}

void initList() {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
    g_listCount = 0;
}

void releaseList() {
    if (isEmpty()) {
        return;
    }
    MyNode *pTemp = g_HeaderNode.pNext;
    MyNode *pDeletedNode = NULL;
    /** 자료형에 구조체가 두개 이므로 두번 free 를 해줘야 한다. */
    while (pTemp != &g_TailNode) {
        pDeletedNode = pTemp;
        pTemp = pTemp->pNext;
        free(pDeletedNode->pData);
        free(pDeletedNode);
    }
    initList();
}

/** 검색할 떄 사용하는 데이터를 찾기 위한 함수 */
/** __attribute__((weak)) 를 사용한 이유는 외부에서 재 선언을 통해서 함수를 변경 하기 위한 선언이다. */
__attribute__((weak)) char *getKey(void *thisPointer) {
    UserData *pUser = (UserData *) thisPointer;
    return pUser->name;
}

void addNewNode(int age, const char *pName, const char *pPhone) {
    /** 관리 대상이 되는 구조체 데이터 */
    UserData *pNewData = calloc(1, sizeof(UserData));
    memset(pNewData, '\0', sizeof(UserData));
    pNewData->age = age;
    strcpy(pNewData->name, pName);
    strcpy(pNewData->phone, pPhone);
    printf("[%p] %d, %s, %s,\r\n", pNewData, pNewData->age, pNewData->name, pNewData->phone);

    /** 관리 하는 데이터 구조체 선언 */
    MyNode *pNewNode = calloc(1, sizeof(MyNode));
    memset(pNewNode, '\0', sizeof(MyNode));

    /** 데이터 넣어주기 */
    pNewNode->pData = pNewData;
    pNewNode->GetKey = getKey;
    /** node 의 관계에 대한 설정 */
    MyNode *pPrevNode = g_TailNode.pPrev;
    /** 새롱 생성한 노드의 관계 설정 */
    pNewNode->pPrev = pPrevNode;
    pNewNode->pNext = &g_TailNode;
    /** 기존 노드에 대한 관계 설정 */
    pPrevNode->pNext = pNewNode;
    g_TailNode.pPrev = pNewNode;

    ++g_listCount;
}

void swapNode(MyNode *pLeft, MyNode *pRight) {
    void *pTemp = pRight->pData;
    pRight->pData = pLeft->pData;
    pLeft->pData = pTemp;
}

void sortByKey() {
    if (isEmpty()) {
        return;
    }
    MyNode *pTemp = g_HeaderNode.pNext;
    MyNode *pSelectedNode = NULL;
    MyNode *pComparedNode = NULL;
    /** 비교를 위한 반복문 */
    while (pTemp != NULL && pTemp != &g_TailNode.pPrev) {
        pSelectedNode = pTemp;
        pComparedNode = pTemp->pNext;
        while (pComparedNode != NULL && pComparedNode != &g_TailNode) {
            if (strcmp(pSelectedNode->GetKey(pSelectedNode->pData), pComparedNode->GetKey(pComparedNode->pData)) > 0) {
                /** 변경할 노드에 대한 것을 비교한 노드로 설정 */
                pSelectedNode = pComparedNode;
            }
            pComparedNode = pComparedNode->pNext;
        }
        /** 비교한 값이 변경 해야할 경우 */
        if (pTemp != pSelectedNode) {
            swapNode(pTemp, pSelectedNode);
        }
        pSelectedNode = NULL;
        pTemp = pTemp->pNext;
    }
}