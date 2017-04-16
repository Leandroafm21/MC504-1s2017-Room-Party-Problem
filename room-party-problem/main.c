#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

/* Número de estudantes da Faculdade */
#define N_STUDENTS 100

/* Variáveis de Estado */
int nStudents;                                               // Número de estudantes no quarto
int deanState;                                               // Estado do Reitor
enum deanStates {notInRoom = 0, inRoom, waiting};            // Possíveis estados
sem_t mutex;                                                 // Protege os valores de nStudents e deanState
sem_t turn;                                                  /* Impede que alunos entrem no enquanto o
                                                                Reitor estiver */
sem_t clear;                                                 // Sinaliza que o reitor pode inspecionar o quarto
sem_t lieIn;                                                 // Sinaliza que o reitor pode entrar no quarto

void party() {
    printf("Festa acontecendo com %d estudantes.\n", nStudents);
    sleep(2);
}

void breakup() {
    printf("Festa sendo encerrada com %d estudantes.\n", nStudents);
    sleep(4);
}

void search() {
    printf("Reitor procurando o quarto, que esta com %d alunos.\n", nStudents);
    sleep(1);
}

void * deanAction() {
    sem_wait(&mutex);

    if (nStudents > 0 && nStudents < 50) {
        deanState = waiting;
        sem_post(&mutex);
        sem_wait(&lieIn);
    }

    if (nStudents >= 50) {
        deanState = inRoom;
        breakup();
        sem_wait(&turn);
        sem_post(&mutex);
        sem_wait(&clear);
        sem_post(&turn);
    }

    else {
        search();
    }

    deanState = notInRoom;
    sem_post(&mutex);

    return NULL;
}

void * studentAction() {
    sem_wait(&mutex);

    if (deanState == inRoom) {
        sem_post(&mutex);
        sem_wait(&turn);
        sem_post(&turn);
        sem_wait(&mutex);
    }

    nStudents += 1;

    if (nStudents == 50 && deanState == waiting)
        sem_post(&lieIn);
    else
        sem_post(&mutex);

    party();

    sem_wait(&mutex);

    nStudents -= 1;

    if (nStudents == 0 && deanState == waiting)
        sem_post(&lieIn);
    else if (nStudents == 0 && deanState == inRoom)
        sem_post(&clear);
    else
        sem_post(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {

}
