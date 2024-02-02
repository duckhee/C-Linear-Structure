#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <memory.h>

typedef struct _linkedList {
    struct _UserData *head;
    int size;
} LinkedList;

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

UserData *g_pHeaderNode = NULL;

// 새로운 기능을 추가할 때는 함수로 분리해서 개발하는 것이 좋다.
void addNewNode(int age, const char *pszName, const char *pszPhone) {
    // 동적할당을 했으니 해제에 대해서 고민을 해봐야한다.
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    memset(newNode, '\0', sizeof(UserData));
    memset(newNode->name, '\0', sizeof(newNode->name));
    memset(newNode->phone, '\0', sizeof(newNode->phone));
    newNode->age = age;
    // pointer에서 pointer로 옮기는 것이기 때문에 메모리 카피를 해줘야한다.
    strcpy(newNode->name, pszName);
    strcpy(newNode->phone, pszPhone);
    newNode->pNext = NULL;
    if (g_pHeaderNode == NULL) {
        printf("head is NULL\r\n");
        g_pHeaderNode = newNode;
    } else {
        newNode->pNext = g_pHeaderNode;
        g_pHeaderNode = newNode;
    }
}

/** 동작하지 않는 이유 찾기 */
// 새로운 기능을 추가할 때는 함수로 분리해서 개발하는 것이 좋다.
void addNode(UserData *pNode, int age, const char *pszName, const char *pszPhone) {
    // 동적할당을 했으니 해제에 대해서 고민을 해봐야한다.
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    memset(newNode, '\0', sizeof(UserData));
    newNode->age = age;
    // pointer에서 pointer로 옮기는 것이기 때문에 메모리 카피를 해줘야한다.
    strcpy(newNode->name, pszName);
    strcpy(newNode->phone, pszPhone);
    newNode->pNext = NULL;
    if (pNode == NULL) {
        printf("head is NULL\r\n");
        pNode = newNode;
    } else {
        printf("insert data\r\n");
        newNode->pNext = pNode;
        pNode = newNode;
    }
}

// 동적으로 생성하는 코드가 있으므로 동적으로 생성된 데이터를 삭제해주는 기능도 필요하다.
void releaseList(UserData *pNode) {
    UserData *pTemp = pNode;
    UserData *pDelete = NULL;
    while (pTemp != NULL) {
        pDelete = pTemp;
        pTemp = pTemp->pNext;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDelete, pDelete->age, pDelete->name, pDelete->phone,
               pDelete->pNext);
        free(pDelete);
    }
    pNode = NULL;
}

void printNode(UserData *pNode) {
    while (pNode != NULL) {
        printf("[%p] %d, %s, %s [Next - %p]\r\n", pNode, pNode->age, pNode->name, pNode->phone, pNode->pNext);
        pNode = pNode->pNext;
    }
}

void initDumpyData(UserData *pNode) {
    printf("Insert dumpy data\r\n");
    addNode(pNode, 10, "hoon", "010-1111-2222");
    addNode(pNode, 12, "hoon2", "010-3333-2222");
    addNode(pNode, 13, "hoon3", "010-1111-3333");
    printf("Insert dumpy data\r\n");
}

void testInitDumpyData() {
    addNewNode(10, "hoon", "010-1111-2222");
    addNewNode(12, "hoon2", "010-3333-2222");
    addNewNode(13, "hoon3", "010-1111-3333");
}

int main() {
    testInitDumpyData();
    UserData *pTemp = g_pHeaderNode;
    UserData *pLinkedList = NULL;
    // input
    initDumpyData(pLinkedList);

    // print list
    printf("call testing\r\n");
    printNode(pLinkedList);
    printf("RELEASE\r\n");
    releaseList(pLinkedList);
    printf("\r\nglobal variable\r\n");
    printNode(pTemp);
    printf("RELEASE\r\n");
    releaseList(pTemp);
    if (g_pHeaderNode == NULL) {
        printf("header node is NULL\r\n");
    }
    printf("program done\r\n");
    return 0;
}