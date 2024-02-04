#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pPrev;
    struct _UserData *pNext;
} UserData;

UserData g_HeadNode = {0, "__DUMMY_HEAD_NODE__"};
UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};

void initLinkedList();

void push(UserData *pUser);

UserData *pop();

int isEmpty();

void printStack();

void releaseAllNode();

int main() {
    initLinkedList();
    UserData user = {10, "Test01", "000-00000-0000"};
    push(&user);
    user.age = 11;
    strcpy(user.name, "test02");
    strcpy(user.phone, "010-1111-1111");
    push(&user);
    user.age = 12;
    strcpy(user.name, "test03");
    strcpy(user.phone, "010-2222-2222");
    /** stack 에 값을 넣는 함수 실행 */
    push(&user);

    for (int i = 0; i < 3; ++i) {
        /** stack 에서 값을 가져오는 함수 실행 */
        UserData *pUser = pop();
        printf("Pop[%d]: %s, %d, %s\r\n", i, pUser->name, pUser->age, pUser->phone);
        free(pUser);
    }
    printStack();
    releaseAllNode();
    return 0;
}

void initLinkedList() {
    g_HeadNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeadNode;

    /** 순환 참조로 만들기 위해서 g_tailNode 의 다음 node 를 g_headNode 를 참조하게 해준다.*/
//    g_TailNode.pNext = &g_HeadNode;
}

void releaseAllNode() {
    UserData *pTemp = g_HeadNode.pNext;
    UserData *pDeleteNode = NULL;
    /** 값이 있고, dummy tail node 가 아닐 경우 */
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pDeleteNode = pTemp;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeleteNode, pDeleteNode->age, pDeleteNode->name,
               pDeleteNode->phone,
               pDeleteNode->pNext);
        pTemp = pTemp->pNext;
        free(pDeleteNode);
    }
    initLinkedList();
}

void push(UserData *pUser) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    /** 입력 받은 값을 복사해서 새로운 node 에 값을 복사해서 넣는다. */
    memcpy(pNewNode, pUser, sizeof(UserData));
    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;

    /** */
    UserData *pNextNode = g_HeadNode.pNext;
    /** 삽입할 node 의 이전 데이터 관계 설정 */
    pNewNode->pPrev = &g_HeadNode;
    pNewNode->pNext = g_HeadNode.pNext;
    /** 삽입할 node 의 이후 데이터 관계 설정 */
    pNextNode->pPrev = pNewNode;
    g_HeadNode.pNext = pNewNode;
}

UserData *pop() {
    /** 현재 데이터가 없을 경우 */
    if (isEmpty()) {
        puts("[ERROR] Stack: underFlow");
        return NULL;
    }
    /** 반환할 node 에 대한 정의 */
    UserData *pPop = g_HeadNode.pNext;
    /** 데이터 삭제를 위한 위치 재 조정 */
    g_HeadNode.pNext = pPop->pNext;
    pPop->pNext->pPrev = pPop->pPrev;
    /** 꺼낸 데이터 반환 */
    return pPop;
}

/** 값이 있는지 확인하기 위한 함수 */
int isEmpty() {
    if (g_HeadNode.pNext == &g_TailNode) {
        return 1;
    }
    return 0;
}

/** 전체 node 의 값을 출력 하는 함수 */
void printStack() {
    UserData *pTemp = &g_HeadNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}