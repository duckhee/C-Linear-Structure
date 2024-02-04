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
/** Dummy Node 로 변경 */
UserData g_HeaderNode = {0, "__DUMMY_HEAD_NODE__"};
UserData g_TailNode = {0, "__DUMMY_TAIL_NODE__"};

void addNewNodeAtTail(int age, const char *pName, const char *pPhone);

void printNode();

void printNodeReverse();

/** double linked list 를 초기화하기 위한 함수 */
void initLinkedList();

void releaseAllNode();

UserData *searchByName(const char *searchName);

void removeNode(UserData *pRemoveNode);

void addOneNodeAndDeleteTests() {
    printf("\r\nTests add One Node and Remove Node Tests\r\n\r\n");
    addNewNodeAtTail(10, "Hoon", "010-1111-1111");
    printNode();
    printf("\r\n");
    printNodeReverse();
    printf("\r\n");
    UserData *deleteNode = searchByName("Hoon");
    if (deleteNode != NULL) {
        removeNode(deleteNode);
    }
    releaseAllNode();
}

void frontNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and Front Node Remove Tests\r\n\r\n");
    addNewNodeAtTail(11, "Choi", "010-2222-2222");
    addNewNodeAtTail(10, "Hoon", "010-1111-1111");
    addNewNodeAtTail(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    printNodeReverse();
    printf("\r\n");
    UserData *deleteNode = searchByName("Choi");
    if (deleteNode != NULL) {
        removeNode(deleteNode);
    }
    releaseAllNode();
}

void middleNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and middle Node Remove Tests\r\n\r\n");
    addNewNodeAtTail(10, "Hoon", "010-1111-1111");
    addNewNodeAtTail(13, "Jang", "010-3333-3333");
    addNewNodeAtTail(11, "Choi", "010-2222-2222");
    printNode();
    printf("\r\n");
    printNodeReverse();
    printf("\r\n");
    UserData *deleteNode = searchByName("Jang");
    if (deleteNode != NULL) {
        removeNode(deleteNode);
    }
    releaseAllNode();
}

void endNodeDeleteTests() {
    printf("\r\nTests add insert Three Node and end Node remove Tests\r\n\r\n");
    addNewNodeAtTail(10, "Hoon", "010-1111-1111");
    addNewNodeAtTail(11, "Choi", "010-2222-2222");
    addNewNodeAtTail(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    printNodeReverse();
    printf("\r\n");
    UserData *deleteNode = searchByName("Jang");
    if (deleteNode != NULL) {
        removeNode(deleteNode);
    }
    releaseAllNode();
}

int main() {
    /** 더미 노드에 대한 초기화를 해주는 함수 */
    initLinkedList();
    /** 데이터를 하나 넣고 삭제하는 테스트 */
    addOneNodeAndDeleteTests();
    /** 세개의 노드 데이터를 넣고 맨 처음 노드에 대한 삭제하는 테스트 */
    frontNodeDeleteTests();
    /** 세개의 노드 데이터를 넣고 중간 노드에 대한 삭제하는 테스트 */
    middleNodeDeleteTests();
    /** 세개의 노드 데이터를 넣고 마지막 노드에 대한 삭제하는 테스트 */
    endNodeDeleteTests();
    return 0;
}

/** double linked list 를 초기화하기 위한 함수 */
void initLinkedList() {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
}

void addNewNodeAtTail(int age, const char *pName, const char *pPhone) {
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    /** 새로운 node 초기화 */
    memset(newNode, '\0', sizeof(UserData));
    /** 값 대입 */
    newNode->age = age;
    strcpy(newNode->name, pName);
    strcpy(newNode->phone, pPhone);
    newNode->pNext = NULL;
    newNode->pPrev = NULL;

    /** Tail Node 에 대해서 선언이 되어 있으므로 Tail에 대한 정보를 따로 찾아서 진행할 필요가 없다. */
    /** Dummy Tail Node 의 앞에 있는 값을 가져온다. */
    UserData *pPrevNode = g_TailNode.pPrev;
    /** Dummy node 앞에 있는 data node 의 다음 값을 새로 생성된 node 의 이전 값으로 정의한다. */
    newNode->pPrev = pPrevNode;
    newNode->pNext = &g_TailNode;
    /** pPrevNode 의 다음이 현재 생성된 node 인 것을 연결 */
    pPrevNode->pNext = newNode;
    /** 끝에 정의 된 Tail Node 의 이전 값은 현재 생성된 node 인것을 정의 */
    g_TailNode.pPrev = newNode;
    return;
}

void printNode() {
    UserData *pTemp = &g_HeaderNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

void printNodeReverse() {
    UserData *pTemp = &g_TailNode;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pPrev;
    }
}

void releaseAllNode() {
    UserData *pTemp = g_HeaderNode.pNext;
    UserData *pDeleteNode = NULL;
    /** g_TailNode 는 동적 할당된 값이 아니므로 삭제하지 않게 해줘야 한다. */
//    while (pTemp->pNext != NULL) {
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pDeleteNode = pTemp;
        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeleteNode, pDeleteNode->age, pDeleteNode->name,
               pDeleteNode->phone,
               pDeleteNode->pNext);
        pTemp = pTemp->pNext;
        free(pDeleteNode);
    }
//    g_HeaderNode.pNext = NULL;
    /** 더미 노드에 대한 초기화를 해주는 함수 */
    initLinkedList();
}

UserData *searchByName(const char *searchName) {
    UserData *pTemp = g_HeaderNode.pNext;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, searchName) == 0) {
            printf("Found name ; %s\r\n", searchName);
            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    printf("Not Found Search name : %s\r\n", searchName);
    return NULL;
}

void removeNode(UserData *pRemoveNode) {
    /** 삭제할 node 에 대한 prevNode 와 nextNode 를 구해서 해당 링크에 대한 설정 하기 위한 변수 선언 */
    UserData *pPrev = pRemoveNode->pPrev;
    UserData *pNext = pRemoveNode->pNext;
    /** 삭제할 node 에 대한 정보 값 */
    UserData *pDeletedNode = pRemoveNode;
    /** 연결 정보에 대한 재 배치 */
    pPrev->pNext = pNext;
    pNext->pPrev = pPrev;
    printf("removeNode() : %s\r\n", pDeletedNode->name);
    free(pDeletedNode);
}