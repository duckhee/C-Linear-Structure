#include "singleList.h"

#define SAVE_FILE_NAME          "listData.dat"

extern Node g_HeaderNode = {0};
extern Node g_TailNode = {0};

static unsigned int g_listCount = 0;

bool isEmpty();

void init() {
    g_HeaderNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeaderNode;
    g_listCount = 0;
}

int dataCount() {
    return g_listCount;
}

/** 초기화 진행하는 함수 */
void initList() {
    /** 데이터 메모리에서 삭제 */
    releaseList();
    init();
}

/** 비어 있는지 확인하는 함수 */
bool isEmpty() {
    if (g_HeaderNode.pNext == &g_TailNode) {
        return true;
    }
    return false;
}

/** 현재 메모리에 올라온 데이터 삭제하는 함수 */
void releaseList() {
    if (isEmpty()) {
        return;
    }
    Node *pTemp = g_HeaderNode.pNext;
    Node *pDeleteTemp;
    while (pTemp != NULL && pTemp != &g_TailNode) {
        pDeleteTemp = pTemp;
        pTemp = pTemp->pNext;
        /** 가져온 객체 메모리가 있을 경우 해제 */
        if (pDeleteTemp->pDataCache != NULL) {
            free(pDeleteTemp->pDataCache);
        }
        /** 삭제할 node 에 대한 메모리 해제 */
        free(pDeleteTemp);
    }
    init();
}

__attribute__((weak)) char *getKey(void *thisPointer) {
    UserData *pUser = (UserData *) thisPointer;
    return pUser->name;
}

void addNewNode(const char *pKey, const void *pData, int sizeOfData, bool isNew, unsigned int offset) {
    Node *pNewNode = calloc(1, sizeof(Node));
    /** key 로 입력 받은 인자의 길이를 담는 변수 node 의 메모리 할당을 위해서 구해야 한다. */
    int lenOfKey = (int) strlen(pKey);
    /** pszKey에 대한 작성을 위한 메모리 할당 -> +1 을 하는 이유는 문자열은 NULL 값을 마지막에 넣어줘야하므로 */
    pNewNode->pszKey = malloc(lenOfKey + 1);
    /** 초기화 */
    memset(pNewNode->pszKey, '\0', (lenOfKey + 1));
    printf("key value : %s\r\n", pKey);
    /** 입력 받은 key 값 복사 */
    strcpy(pNewNode->pszKey, pKey);
    /** 새로 입력 받은 데이터가 있고 크기가 0이상일 경우 */
    if (pData != NULL && sizeOfData > 0) {
        void *pNewData = malloc(sizeOfData);
        /** data 복사 */
        memcpy(pNewData, pData, sizeOfData);
        /** 새로 생성한 node 에 새로운 데이터를 저장 */
        pNewNode->pDataCache = pNewData;
        pNewNode->dataSize = sizeOfData;
    }
    /** 새로 저장된 데이터인지에 대한 값을 저장 */
    pNewNode->isNew = isNew;
    /** file 의 offset 값을 저장 */
    pNewNode->offset = offset;

    /** 연결 리스트에 관계 설정 */
    /** 새로 생성한 node 의 관계 설정 */
    Node *pPrevNode = g_TailNode.pPrev;
    pNewNode->pNext = &g_TailNode;
    pNewNode->pPrev = pPrevNode;
    /** 연결 리스트에 기존에 있던 node 의 관계 설정 */
    pPrevNode->pNext = pNewNode;
    g_TailNode.pPrev = pNewNode;
    /** 데이터의 갯수를 관리하는 static 변수의 값 증가 */
    ++g_listCount;
    /** 새로 생성된 데이터를 파일에 쓰기 */
    saveNodeToFile(pNewNode);
}

/** 관리 구조체에 정의된 key 값을 가지고 검색하는 함수 */
void *searchByKey(char *pszKey) {
    Node *pTempNode = g_HeaderNode.pNext;
    /** 순회하는 반복문 */
    while (pTempNode != NULL && pTempNode != &g_TailNode) {
        if (strcmp(pTempNode->pszKey, pszKey) == 0) {
            /** 읽어올 파일에 대한 구조체 포인터 */
            FILE *fp = NULL;
            /** 데이터가 저장된 파일을 바이너리 읽기 모드로 열기 */
            fp = fopen("listData.dat", "rb");
            if (fp == NULL) {
                puts("Read Data File Error");
                return NULL;
            }
            /** 파일의 시작점 부터 저장된 데이터의 위치에 대한 이동 */
            fseek(fp, (pTempNode->offset * sizeof(UserData)), SEEK_SET);
            UserData pTempUser = {0};
            /** 해당 위치에서 UserData 만큼 하나의 데이터 가져오기 */
            if (fread(&pTempUser, sizeof(UserData), 1, fp) > 0) {
                /** 메모리에 저장하기 위한 객체 크기 메모리에 부여  */
                pTempNode->pDataCache = calloc(1, sizeof(UserData));
                /** 파일에서 찾은 데이터를 메모리에 복사 */
                memcpy(pTempNode->pDataCache, &pTempUser, sizeof(UserData));
                /** 현재 데이터의 크기에 대한 변수를 변경 */
                pTempNode->dataSize = sizeof(UserData);
                /** file 객체 닫아주기 */
                fclose(fp);
                return pTempNode;
            }
            fclose(fp);
        }
        pTempNode = pTempNode->pNext;
    }
    /** 데이터를 찾지 못했을 경우 */
    return NULL;
}


int loadListFromFile(void) {
    /** 데이터를 읽어오기 전에 올라온 데이터 삭제 */
    releaseList();
    /** file 을 읽기 위한 객체 */
    FILE *fp = NULL;
    /** binary read mode 로 파일 열기 */
    fp = fopen(SAVE_FILE_NAME, "rb");
    if (fp == NULL) {
        return 0;
    }
    /** 읽어온 데이터를 저장할 임시 변수 선언 */
    UserData pTempUser = {0};
    /** 파일에 저장된 데이터의 위치 값을 저장하기 위한 변수 */
    unsigned int offset = 0;
    while (fread(&pTempUser, sizeof(UserData), 1, fp) > 0) {
        /** key 를 이름으로 설정 */
        addNewNode(pTempUser.name, NULL, 0, false, offset);
        memset(&pTempUser, '\0', sizeof(UserData));
        ++offset;
    }
    fclose(fp);
    return 1;
}

int saveNewNodeToFile(void) {
    FILE *fp = NULL;
    /** binary append mode 로 파일 열기 */
    fp = fopen(SAVE_FILE_NAME, "ab+");
    if (fp == NULL) {
        return 0;
    }
    /** 새로 생성된 데이터만 저장하기 위해서 순회 하기 위한 첫번째 위치 */
    Node *pTempNode = g_HeaderNode.pNext;
    while (pTempNode != &g_TailNode) {
        /** 새로운 node 일 경우 */
        if (pTempNode->isNew == true) {
            /** file 에 데이터 쓰기 */
            fwrite(pTempNode->pDataCache, pTempNode->dataSize, 1, fp);
            printf("file write : %s\r\n", pTempNode->pszKey);
        }
        pTempNode = pTempNode->pNext;
    }
    fclose(fp);
    return 1;
}

/** 특정 node 에 대한 변경 값을 파일에 쓰는 함수 */
int saveNodeToFile(Node *pNode) {
    /** file 을 읽어올 변수 */
    FILE *fp = NULL;
    if (pNode->pDataCache == NULL || pNode->dataSize == 0) {
        return 0;
    }
    /** 수정 가능한 읽기 모드로 파일 열기 */
    fp = fopen(SAVE_FILE_NAME, "rb+");
    if (fp == NULL) {
        return 0;
    }
    /** 해당 자료형의 위치 찾기 */
    fseek(fp, (pNode->offset * sizeof(UserData)), SEEK_SET);

    if (fwrite(pNode->pDataCache, sizeof(UserData), 1, fp) > 0) {
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}

