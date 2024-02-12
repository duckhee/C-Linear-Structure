#include "menu.h"

void addNewUser();

void deleteUser();

void searchByKeyUser();

void editUserData(Node *pSelectedNode);

Menu printMenu(void) {
    Menu selectedMenu = 0;
    clear();
    printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
    scanf("%d", &selectedMenu);
    return selectedMenu;
}

void menuHandler(void) {
    Menu menu;
    while ((menu = printMenu()) != 0) {
        switch (menu) {
            case NEW:
                printf("NEW USER\r\n");
                addNewUser();
                getchar();
                break;

            case SEARCH:
                printf("SEARCH USER BY KEY\r\n");
                searchByKeyUser();
                getchar();
                break;

            case PRINT:
                printf("USER PRINT ALL\r\n");
                printNode(true);
                getchar();
                break;

            case REMOVE:
                deleteUser();
                getchar();
                break;

            default:
                break;
        }
    }
    puts("Bye~!");
}

/** 출력 관련 함수는 UI 에 존재 해야 하므로 UI 에 정의 되어야 한다.*/
void printNode(bool waitFlag) {
    Node *pTempNode = &g_HeaderNode;
    while (pTempNode != NULL) {
        printf("[%p] %s, new : %d, offset : %d, ", pTempNode, pTempNode->pszKey, pTempNode->isNew, pTempNode->offset);
        if (pTempNode->pDataCache != NULL) {
            UserData *pTempUser = pTempNode->pDataCache;
            printf("%d, %s [%p]\r\n", pTempUser->age, pTempUser->phone, pTempNode->pNext);
        } else {
            printf("[%p]\r\n", pTempNode->pNext);
        }
        pTempNode = pTempNode->pNext;
    }
    if (waitFlag) {
        getchar();
    }
}

void printNodeReverse(bool waitFlag) {
    Node *pTempNode = &g_TailNode;
    while (pTempNode != NULL) {
        printf("[%p] %s, new : %d, offset : %d, ", pTempNode, pTempNode->pszKey, pTempNode->isNew, pTempNode->offset);
        if (pTempNode->pDataCache != NULL) {
            UserData *pTempUser = pTempNode->pDataCache;
            printf("%d, %s [%p]\r\n", pTempUser->age, pTempUser->phone, pTempNode->pNext);
        } else {
            printf("[%p]\r\n", pTempNode->pNext);
        }
        pTempNode = pTempNode->pPrev;
    }
    if (waitFlag) {
        getchar();
    }
}

void addNewUser() {
    UserData user = {0};

    printf("age : ");
    scanf("%d", &user.age);
    printf("name : ");
    scanf("%s", user.name);
    printf("phone : ");
    scanf("%s", user.phone);
    printf("%d, %s, %s \r\n", user.age, user.name, user.phone);
    addNewNode(user.name, &user, sizeof(user), true, 0);
    saveNewNodeToFile();
}

void editUserData(Node *pSelectedNode) {
    UserData *pTempUser = pSelectedNode->pDataCache;
    char szBuffer[PHONE_MAX] = {0};
    memset(szBuffer, '\0', PHONE_MAX);
    printf("New User Phone : ");
    scanf("%s%*c", szBuffer);
//    fgets(szBuffer, PHONE_MAX, stdin);

    printf("Update Phone : %s\r\n", szBuffer);
    if (strlen(szBuffer) > 0) {
        memcpy(pTempUser->phone, szBuffer, sizeof(pTempUser->phone));
        printf("Do you want to commit now?(y/n)\n");
        char ch = fgetc(stdin);
        if (ch == 'y' || ch == 'Y') {
            saveNodeToFile(pSelectedNode);
        }
    }
}

void searchByKeyUser() {
    char searchName[NAME_MAX] = {0};
    printf("Search Key : ");
    scanf("%s%*c", searchName);
    printf("Search name : %s\r\n", searchName);
    Node *pSearchNode = searchByKey(searchName);
    if (pSearchNode != NULL) {
        UserData *pTempUser = pSearchNode->pDataCache;
        if (pTempUser != NULL) {
            printf("Found: %d, %s, %s\n",
                   pTempUser->age, pTempUser->name, pTempUser->phone);
            printf("Do you want to edit? (y/n)\n");
            char ch = fgetc(stdin);
            if (ch == 'y' || ch == 'Y') {
                editUserData(pSearchNode);
            }
        }
    }
    getchar();
}

void deleteUser() {
    char deleteUserKey[NAME_MAX] = {0};
    printf("Delete User Key : ");
    scanf("%s%*c", deleteUserKey);
    printf("Delete user name is %s\r\n", deleteUserKey);
    Node *pDeleteNodeSearch = searchByKey(deleteUserKey);
    if (pDeleteNodeSearch == NULL) {
        printf("Not Found Delete User\r\n");
        return;
    }
    removeNode(pDeleteNodeSearch);
    getchar();
}