#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _UserData {
    int age;
    char name[32];
    char phone[32];
    struct _UserData *pNext;
} UserData;

void addNode(int age, const char *pName, const char *pPhone);

void printNode();

UserData *searchByName(const char *pName);

void releaseAllNode();

UserData *searchToRemove(UserData **ppPrev, const char *searchName);

void removeNode(UserData *pPrevNode);


void addNodeList(UserData **ppHead, int age, const char *pName, const char *pPhone);

void printNodeList(UserData **ppHead);

UserData *searchByNameList(UserData **ppHead, const char *pName);

void releaseAllNodeList(UserData **ppHead);

UserData *searchToRemoveList(UserData **ppHead, UserData **ppPrev, const char *searchName);

void removeNodeList(UserData **ppHead, UserData *pPrevNode);

UserData *g_pHeader = NULL;

void initDumpyData() {
    addNode(10, "Hoon", "010-1111-1111");
    addNode(11, "Choi", "010-2222-2222");
    addNode(13, "Jang", "010-3333-3333");
}

void searchNameTests() {
    searchByName("Hoon");
    searchByName("Choi");
    searchByName("Jang");
    searchByName("Kim");
}

void addOneNodeAndDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add One Node and Remove Node Tests\r\n\r\n");
    addNode(10, "Hoon", "010-1111-1111");
    printNode();
    printf("\r\n");
    if (searchToRemove(&pPrev, "Hoon") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void frontNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and Front Node Remove Tests\r\n\r\n");
    addNode(11, "Choi", "010-2222-2222");
    addNode(10, "Hoon", "010-1111-1111");
    addNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    if (searchToRemove(&pPrev, "Choi") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void middleNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and middle Node Remove Tests\r\n\r\n");
    addNode(10, "Hoon", "010-1111-1111");
    addNode(13, "Jang", "010-3333-3333");
    addNode(11, "Choi", "010-2222-2222");
    printNode();
    printf("\r\n");
    if (searchToRemove(&pPrev, "Jang") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void endNodeDeleteTests() {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and end Node remove Tests\r\n\r\n");
    addNode(10, "Hoon", "010-1111-1111");
    addNode(11, "Choi", "010-2222-2222");
    addNode(13, "Jang", "010-3333-3333");
    printNode();
    printf("\r\n");
    if (searchToRemove(&pPrev, "Jang") != NULL) {
        removeNode(pPrev);
    }
    releaseAllNode();
}

void addOneNodeAndDeleteListTests(UserData **ppHead) {
    UserData *pPrev = NULL;
    printf("\r\nTests add One Node and Remove Node Tests\r\n\r\n");
    addNodeList(ppHead, 10, "Hoon", "010-1111-1111");
    printNodeList(ppHead);
    printf("\r\n");
    if (searchToRemoveList(ppHead, &pPrev, "Hoon") != NULL) {
        removeNodeList(ppHead, pPrev);
    }
    releaseAllNodeList(ppHead);
}

void frontNodeDeleteListTests(UserData **ppHead) {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and Front Node Remove Tests\r\n\r\n");
    addNodeList(ppHead, 11, "Choi", "010-2222-2222");
    addNodeList(ppHead, 10, "Hoon", "010-1111-1111");
    addNodeList(ppHead, 13, "Jang", "010-3333-3333");
    printNodeList(ppHead);
    printf("\r\n");
    if (searchToRemoveList(ppHead, &pPrev, "Choi") != NULL) {
        removeNodeList(ppHead, pPrev);
    }
    releaseAllNodeList(ppHead);
}

void middleNodeDeleteListTests(UserData **ppHead) {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and middle Node Remove Tests\r\n\r\n");
    addNodeList(ppHead, 10, "Hoon", "010-1111-1111");
    addNodeList(ppHead, 13, "Jang", "010-3333-3333");
    addNodeList(ppHead, 11, "Choi", "010-2222-2222");
    printNodeList(ppHead);
    printf("\r\n");
    if (searchToRemoveList(ppHead, &pPrev, "Jang") != NULL) {
        removeNodeList(ppHead, pPrev);
    }
    releaseAllNode();
}

void endNodeDeleteListTests(UserData **ppHead) {
    UserData *pPrev = NULL;
    printf("\r\nTests add insert Three Node and end Node remove Tests\r\n\r\n");
    addNodeList(ppHead, 10, "Hoon", "010-1111-1111");
    addNodeList(ppHead, 11, "Choi", "010-2222-2222");
    addNodeList(ppHead, 13, "Jang", "010-3333-3333");
    printNodeList(ppHead);
    printf("\r\n");
    if (searchToRemoveList(ppHead, &pPrev, "Jang") != NULL) {
        removeNodeList(ppHead, pPrev);
    }
    releaseAllNodeList(ppHead);
}

int main() {
    UserData *pHeader = NULL;
    /** 데이터를 하나 넣고 삭제하는 테스트 */
//    addOneNodeAndDeleteTests();
    addOneNodeAndDeleteListTests(&pHeader);
    /** 세개의 노드 데이터를 넣고 맨 처음 노드에 대한 삭제하는 테스트 */
//    frontNodeDeleteTests();
    frontNodeDeleteListTests(&pHeader);
    /** 세개의 노드 데이터를 넣고 중간 노드에 대한 삭제하는 테스트 */
//    middleNodeDeleteTests();
    middleNodeDeleteListTests(&pHeader);
    /** 세개의 노드 데이터를 넣고 마지막 노드에 대한 삭제하는 테스트 */
//    endNodeDeleteTests();
    endNodeDeleteListTests(&pHeader);
    return 0;
}

void addNode(int age, const char *pName, const char *pPhone) {
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    memset(newNode, '\0', sizeof(UserData));

    newNode->age = age;
    strcpy(newNode->name, pName);
    strcpy(newNode->phone, pPhone);
    newNode->pNext = NULL;

    if (g_pHeader == NULL) {
        g_pHeader = newNode;
    } else {
        UserData *pTail = g_pHeader;
        while (pTail->pNext != NULL) {
            pTail = pTail->pNext;
        }
        pTail->pNext = newNode;
        //Stack
//        newNode->pNext = g_pHeader;
//        g_pHeader = newNode;
    }
}

void printNode() {
    UserData *pTemp = g_pHeader;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

UserData *searchByName(const char *pName) {
    UserData *pTemp = g_pHeader;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, pName) == 0) {
            printf("find name : %s\r\n", pName);

            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    printf("not found name\r\n");
    return NULL;
}

void releaseAllNode() {
    UserData *pTemp = g_pHeader;
    UserData *pDeletedNode = NULL;
    while (pTemp != NULL) {
        pDeletedNode = pTemp;
        pTemp = pTemp->pNext;

        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeletedNode, pDeletedNode->age, pDeletedNode->name,
               pDeletedNode->phone,
               pDeletedNode->pNext);

        free(pDeletedNode);
    }
    g_pHeader = NULL;

}

UserData *searchToRemove(UserData **ppPrev, const char *searchName) {
    UserData *pCurrentNode = g_pHeader;
    UserData *pPrevNode = NULL;
    while (pCurrentNode != NULL) {
        if (strcmp(pCurrentNode->name, searchName) == 0) {
            printf("search to Remove : %s - %s\r\n", searchName, pCurrentNode->name);
            /** 인자로 받은 포인터 변수에 이전 노드에 대한 정보를 넣어준다. */
            *ppPrev = pPrevNode;
            return pCurrentNode;
        }
        /** 이전 노드의 정보를 담고 있는 변수에 현재 노드를 넣어준다. */
        pPrevNode = pCurrentNode;
        /** 현재 노드의 정보를 다목 있는 노드에 다음 노드의 정보를 넣어준다. */
        pCurrentNode = pCurrentNode->pNext;
    }
    return NULL;
}

void removeNode(UserData *pPrevNode) {
    UserData *pRemove = NULL;
    if (pPrevNode == NULL) {
        if (g_pHeader == NULL) {
            return;
        } else {
            pRemove = g_pHeader;
            g_pHeader = pRemove->pNext;
            printf("RemoveNode() :  %s\r\n", pRemove->name);
            free(pRemove);
        }
        return;
    }
    pRemove = pPrevNode->pNext;
    pPrevNode->pNext = pRemove->pNext;
    printf("RemoveNode() : %s\r\n", pRemove->name);
    free(pRemove);
}


void addNodeList(UserData **ppHead, int age, const char *pName, const char *pPhone) {
    UserData *newNode = (UserData *) malloc(sizeof(UserData));
    memset(newNode, '\0', sizeof(UserData));

    newNode->age = age;
    strcpy(newNode->name, pName);
    strcmp(newNode->phone, pPhone);
    newNode->pNext = NULL;
    if (*ppHead == NULL) {
        *ppHead = newNode;
    } else {
        // Queue
        UserData *pTail = *ppHead;
        while (pTail->pNext != NULL) {
            pTail = pTail->pNext;
        }
        pTail->pNext = newNode;
        //Stack
//        newNode->pNext =  *ppHead;
//        g_pHeader = newNode;
    }
}

void printNodeList(UserData **ppHead) {
    UserData *pTemp = *ppHead;
    while (pTemp != NULL) {
        printf("[%p] %d, %s, %s, next Node -> [%p]\r\n", pTemp, pTemp->age, pTemp->name, pTemp->phone, pTemp->pNext);
        pTemp = pTemp->pNext;
    }
}

UserData *searchByNameList(UserData **ppHead, const char *pName) {
    UserData *pTemp = *ppHead;
    while (pTemp != NULL) {
        if (strcmp(pTemp->name, pName) == 0) {
            printf("find name : %s\r\n", pName);

            return pTemp;
        }
        pTemp = pTemp->pNext;
    }
    printf("not found\r\n");
}

void releaseAllNodeList(UserData **ppHead) {
    UserData *pTemp = *ppHead;
    UserData *pDeletedNode = NULL;
    while (pTemp != NULL) {
        pDeletedNode = pTemp;
        pTemp = pTemp->pNext;

        printf("Deleted : [%p] %d, %s, %s [Next - %p]\r\n", pDeletedNode, pDeletedNode->age, pDeletedNode->name,
               pDeletedNode->phone,
               pDeletedNode->pNext);

        free(pDeletedNode);
    }
    *ppHead = NULL;
}

UserData *searchToRemoveList(UserData **ppHead, UserData **ppPrev, const char *searchName) {
    UserData *pCurrentNode = *ppHead;
    UserData *pPrevNode = NULL;
    while (pCurrentNode != NULL) {
        if (strcmp(pCurrentNode->name, searchName) == 0) {
            printf("search to Remove : %s - %s\r\n", searchName, pCurrentNode->name);
            /** 인자로 받은 포인터 변수에 이전 노드에 대한 정보를 넣어준다. */
            *ppPrev = pPrevNode;
            return pCurrentNode;
        }
        /** 이전 노드의 정보를 담고 있는 변수에 현재 노드를 넣어준다. */
        pPrevNode = pCurrentNode;
        /** 현재 노드의 정보를 다목 있는 노드에 다음 노드의 정보를 넣어준다. */
        pCurrentNode = pCurrentNode->pNext;
    }
    return NULL;
}

void removeNodeList(UserData **ppHead, UserData *pPrevNode) {
    UserData *pRemove = NULL;
    if (pPrevNode == NULL) {
        if (*ppHead == NULL) {
            return;
        } else {
            pRemove = *ppHead;
            *ppHead = pRemove->pNext;
            printf("RemoveNode() :  %s\r\n", pRemove->name);
            free(pRemove);
        }
        return;
    }
    pRemove = pPrevNode->pNext;
    pPrevNode->pNext = pRemove->pNext;
    printf("RemoveNode() : %s\r\n", pRemove->name);
    free(pRemove);
}