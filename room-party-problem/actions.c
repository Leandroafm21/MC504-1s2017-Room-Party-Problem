#include "actions.h"

void party(int timeOnParty) {
    printf("Festa acontecendo com %d estudantes.\n", nStudents);
    sleep(timeOnParty);
}

void breakup() {
    printf("Festa sendo encerrada com %d estudantes.\n", nStudents);
    sleep(2);
}

void search() {
    printf("Reitor inspecionando o quarto.\n");
    sleep(2);
}
