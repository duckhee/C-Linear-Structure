#ifndef __DATA_LIST_H__
#define __DATA_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
} UserData;

/** 관리체계의 구조체 */
typedef struct _Node {
    void *pData;
    struct _Node *pPrev;
    struct _Node *pNext;

    char *(*GetKey)(void *thisPointer);
} MyNode;

/** 초기 데이터 삽입 */
void initList(void);

/** 데이터 정리 및 삭제 */
void releaseList(void);

void addNewNode(int age, const char *name, const char *phone);

void removeNodeByName(MyNode *pRemoveNode);

void swapNode(MyNode *pLeft, MyNode *pRight);

/** 값을 검색할 때 사용자가 변경할 수 있게 해주기 위한 call back 함수 */
char *getKey(void *thisPointer);

/** search by name */
MyNode *searchNodeByName(const char *pName);

bool isEmpty();

void sortByKey();

unsigned int getListCount();

int savedListToFile(void);

int loadListFromFile(void);

MyNode g_HeaderNode;
MyNode g_TailNode;

#endif

