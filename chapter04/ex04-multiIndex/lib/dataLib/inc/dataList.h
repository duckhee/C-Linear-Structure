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

/** index 를 생성하는 함수 */
void **makeIndexAge(int *pCount);

/** 해당 나이에 대한 범위를 가지고 있는 인덱스를 반환 하는 함수 */
void **searchByIndexAgeRange(int min, int max, unsigned int *pCount);

/** 이름을 가지고 인덱스 생성하는 함수 */
void **makeIndexByName(int *pCount);

/** index 에 대한 업데이트 */
void UpdateIndexAll();

unsigned int getListCount();

UserData g_HeaderNode;
UserData g_TailNode;
UserData **g_idxListAge ;
UserData **g_idxListName;

#endif

