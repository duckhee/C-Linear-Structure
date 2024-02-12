#include "menu.h"
#include "singleList.h"

int main() {
    initList();
    loadListFromFile();
    menuHandler();
    saveNewNodeToFile();
    releaseList();
    return 0;
}