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
    struct _UserData *pPrev;
    struct _UserData *pNext;
} UserData;

/** 초기 데이터 삽입 */
void initList(void);

/** 데이터 정리 및 삭제 */
void releaseList(void);

void addNewNode(int age, const char *name, const char *phone);

void push(UserData *pNewUser);

UserData *pop(void);

void enQueue(UserData *pNewUser);

UserData *deQueue(void);

UserData *searchByName(const char *searchName);

bool isEmpty();

void nodeDataCopy(UserData *dst, UserData *src);

void swapNode(UserData *pLeft, UserData *pRight);
void sortByAge();

void **searchByAgeRange(int min, int max, int *pCount);

UserData g_HeaderNode;
UserData g_TailNode;

#endif

