#ifndef __MENU_H__
#define __MENU_H__

#include <stdio.h>
#include <stdlib.h>
#include "singleList.h"

typedef enum _Menu {
    EXIT = 0,
    NEW,
    SEARCH,
    PRINT,
    REMOVE
} Menu;

#define clear() printf("\033[H\033[J")

Menu printMenu(void);

void menuHandler(void);

/** 출력 관련 함수는 UI 에 존재 해야 하므로 UI 에 정의 되어야 한다.*/
void printNode(bool waitFlag);

void printNodeReverse(bool waitFlag);

#endif
