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
    /** header 파일에 정의가 되어 있으면 해당 함수를 넣어준다. -> 구현이 안되어 있으면 오류가 나므로 weak 로 함수를 만들어서 추후 overrinding 하여 함수를 넣는 형태로 현재는 구현이 되어 있다. */
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

void removeNodeByName(MyNode *pRemoveNode) {
    /** 삭제할 이전 노드와 삭제할 노드의 이후 노드를 연결 시켜주는 작업이 필요 */
    MyNode *pPrev = pRemoveNode->pPrev;
    MyNode *pNext = pRemoveNode->pNext;

    pPrev->pNext = pNext;
    pNext->pPrev = pPrev;
    MyNode *pDeleteNode = pRemoveNode;
    UserData *pTempUser = pDeleteNode->pData;
    printf("Remove Node - [%p] %d, %s, %s, [prev - %p][next -%p]\r\n", pRemoveNode, pTempUser->age, pTempUser->name,
           pTempUser->phone, pPrev,
           pNext);
    free(pDeleteNode->pData);
    free(pDeleteNode);

    --g_listCount;
}

MyNode *searchNodeByName(const char *pName) {
    if (isEmpty()) {
        return NULL;
    }
    MyNode *pTemp = g_HeaderNode.pNext;
    UserData *pTempUser = NULL;
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pTempUser = pTemp->pData;
        if (strcmp(pTempUser->name, pName) == 0) {
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    return NULL;
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
    /** 선택 정렬을 이용한 정렬 */
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

int savedListToFile(void) {
    /** binary write mode 로 파일 열기 */
    FILE *fp = fopen("listData.dat", "wb");
    /** file 열기 실패 */
    if (fp == NULL) {
        printf("file open Failed\r\n");
        return 0;
    }
    /** data 가 있는 부분 */
    MyNode *pTemp = g_HeaderNode.pNext;
    /** void pointer 를 UserData 로 변환 후 담을 변수 */
    UserData *pTempUser = NULL;
    while (pTemp != NULL && pTemp != &g_TailNode) {
        /** UserData 형태로 형 변환 -> 자료형 재 정의 */
        pTempUser = pTemp->pData;
        /** file 에 데이터 쓰기 */
        fwrite(pTempUser, sizeof(UserData), 1, fp);
        pTemp = pTemp->pNext;
    }
    /** file 다 쓰고 나서 file 닫아 주기 */
    fclose(fp);
    return 1;
}

int loadListFromFile(void) {

    /** binary read mode 로 파일 열기 */
    FILE *fp = fopen("listData.dat", "rb");
    if (fp == NULL) {
        printf("file open Failed\r\n");
        return 0;
    }
    /** file data 를 읽어오기 전에 리스트 초기화 */
    releaseList();
    /** 읽어온 데이터를 임시 저장할 객체 */
    UserData loadUser = {0};
    /** file 에서 데이터를 UserData 형태로 가져오기 */
    while (fread(&loadUser, sizeof(UserData), 1, fp) > 0) {
        addNewNode(loadUser.age, loadUser.name, loadUser.phone);
        memset(&loadUser, '\0', sizeof(UserData));
    }
    /** file 에서 데이터를 다 읽어온 후 file 닫기 */
    fclose(fp);
    return 1;
}