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

void initQueue();

void printQueue();

void enQueue(UserData *pUser);

UserData *deQueue();

int isEmpty();

void releaseQueue();

/** dummy node */
UserData g_headNode = {0, "__DUMMY_HEAD_NODE__"};
UserData g_tailNode = {0, "__DUMMY_TAIL_NODE__"};

int main() {
    /** 초기화 */
    initQueue();
    UserData user = {10, "tester01", "010-0000-0000"};
    /** Queue 에 값을 넣기 */
    enQueue(&user);
    user.age = 11;
    strcpy(user.name, "tester02");
    strcpy(user.phone, "010-1111-1111");
    /** Queue 에 값을 넣기 */
    enQueue(&user);
    user.age = 12;
    strcpy(user.name, "tester03");
    strcpy(user.phone, "010-2222-2222");
    /** Queue 에 값을 넣기 */
    enQueue(&user);
    /** Queue 의 값을 빼기 */
    for (int i = 0; i < 3; ++i) {
        UserData *pUser = deQueue();
        printf("deQueue[%d]: %s, %d, %s\r\n", i, pUser->name, pUser->age, pUser->phone);
        free(pUser);
    }

    printQueue();
    releaseQueue();
    return 0;
}

void initQueue() {
    g_headNode.pNext = &g_tailNode;
    g_tailNode.pPrev = &g_headNode;
}

void printQueue() {
    UserData *pTemp = &g_headNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void releaseQueue() {
    UserData *pTemp = g_headNode.pNext;
    UserData *pDeleteNode = NULL;
    while (pTemp != NULL && pTemp != &g_tailNode) {
        pDeleteNode = pTemp;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeleteNode, pDeleteNode->age, pDeleteNode->name,
               pDeleteNode->phone,
               pDeleteNode->pNext);
        pTemp = pTemp->pNext;
        free(pDeleteNode);
    }
    initQueue();
}


void enQueue(UserData *pUser) {
    UserData *pNewNode = (UserData *) malloc(sizeof(UserData));
    /** 입력 받은 값을 복사해서 새로운 node 에 값을 복사해서 넣는다. */
    memcpy(pNewNode, pUser, sizeof(UserData));
    pUser->pNext = NULL;
    pUser->pPrev = NULL;
    /** 넣을 data node 의 이전 값을 가져 오기 */
    UserData *pPrevNode = g_tailNode.pPrev;
    pNewNode->pPrev = g_tailNode.pPrev;
    pNewNode->pNext = &g_tailNode;
    /** 넣을 data node 의 이전 node 에 대한 관계 재 설정 */
    pPrevNode->pNext = pNewNode;
    /** 마지막 위치 node 설정 */
    g_tailNode.pPrev = pNewNode;
    return;
}

int isEmpty() {
    if (g_headNode.pNext == &g_tailNode) {
        return 1;
    }
    return 0;
}

UserData *deQueue() {
    if (isEmpty()) {
        puts("[ERROR] Queue: underFlow");
        return NULL;
    }
    /** 가져올 node 에 대한 변수 */
    UserData *pDeQueue = g_headNode.pNext;
    /** queue 를 통한 값을 반환 하므로 관계 재조정 */
    g_headNode.pNext = pDeQueue->pNext;
    pDeQueue->pNext->pPrev = pDeQueue->pPrev;
    return pDeQueue;
}


