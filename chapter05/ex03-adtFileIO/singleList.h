#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_MAX        32
#define PHONE_MAX       32

typedef struct _UserData {
    int age;
    char name[NAME_MAX];
    char phone[PHONE_MAX];
} UserData;

typedef struct _Node {
    bool isNew; // 새로운 데이터인지 이난지 확인하기 위한 변수
    char *pszKey; // primary key 와 같은 역활
    void *pDataCache;

    unsigned int dataSize; // 데이터 자료형의 크기
    unsigned int offset; // file 에서의 위치 값 -> offset

    struct _Node *pPrev;
    struct _Node *pNext;
} Node;


Node g_HeaderNode;
Node g_TailNode;

void initList();

void releaseList();

void addNewNode(const char *pKey, const void *pData, int sizeOfData, bool isNew, unsigned int offset);

void *searchByKey(char *pszKey);

void sortByAge(void);

int loadListFromFile(void);

int saveNewNodeToFile(void);

int saveNodeToFile(Node *pNode);

int dataCount();

#endif