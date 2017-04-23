#include "actions.h"

void party(int timeOnParty) {
    sleep(timeOnParty);
}

void breakup() {
    sleep(2);
}

void search() {
    sleep(2);
}

void clearScreen(){
#ifdef __unix__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#endif
}
