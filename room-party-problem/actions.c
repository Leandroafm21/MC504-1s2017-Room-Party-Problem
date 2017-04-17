#include "actions.h"

void party(int timeOnParty) {
    //printf("Festa acontecendo com %d estudantes.\n", nStudents);
    sleep(timeOnParty);
}

void breakup() {
    //printf("Festa sendo encerrada com %d estudantes.\n", nStudents);
    sleep(2);
}

void search() {
    //printf("Reitor inspecionando o quarto.\n");
    sleep(2);
}

void clearScreen(){
#ifdef __unix__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#endif
}

