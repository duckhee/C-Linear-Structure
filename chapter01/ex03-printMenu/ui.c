#include <stdio.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")
//#define clear() system("clear")

typedef enum _MenuItem {
    EXIT,
    NEW,
    SEARCH,
    PRINT,
    REMOVE
} MenuItem;

MenuItem printMenu(void) {
    MenuItem input = 0;
    clear();
    printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\r\n");
    scanf("%d%*c", &input);
    return input;
}


int main() {
    MenuItem menu = 0;
    while ((menu = printMenu()) != 0) {
        switch (menu) {
            case NEW:
                break;
            case SEARCH:
                break;
            case PRINT:
                break;
            case REMOVE:
                break;
        }
    }
    return 0;
}