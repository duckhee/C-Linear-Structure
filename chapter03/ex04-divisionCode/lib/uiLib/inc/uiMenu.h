#ifndef __UI_MENU_H__
#define __UI_MENU_H__

#include <stdio.h>
#include <stdlib.h>
#include "dataList.h"

typedef enum _Menu {
    EXIT = 0,
    NEW = 1,
    SEARCH = 2,
    PRINT = 3,
    REMOVE = 4
} Menu;

#define clear() printf("\033[H\033[J")

Menu printMenu(void);

void menuHandler(void);

/** 출력 관련 함수는 UI 에 존재 해야 하므로 UI 에 정의 되어야 한다.*/
void printNode(void);

void printNodeReverse(void);

void search(void);

#endif