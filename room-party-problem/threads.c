#include "threads.h"

void * deanAction() {
    pthread_mutex_lock(&mutex);

    /* Se o número de estudantes no quarto estiver entre 0 e 10 quando
     * o Reitor chega, ele aguarda (semáforo lieIn) do lado de fora e
     * libera o semáforo mutex */
    if (nStudents > 0 && nStudents < 10) {
        deanState = waiting;
        sync_printf(nStudents, deanState == inRoom, "Dean chegou no quarto.\n");
        pthread_mutex_unlock(&mutex);
        sem_wait(&lieIn);
    }

    /* Se o número de estudantes for maior que 10, o Reitor entra e termina
     * a festa... */
    if (nStudents >= 10) {
        wait = 1;
        deanState = inRoom;
        sync_printf(nStudents, deanState == inRoom, "Dean entrou no quarto.\n");
        breakup();

        /* ...e se for menor que 15, ele inspeciona o quarto quando todos
         * sairem. */
        bool canSearch = false;
        if (nStudents < 15)
            canSearch = true;

        /* Nenhum estudante pode entrar no quarto enquanto o Reitor estiver
         * (semáforo turn) */
        sem_wait(&turn);
        pthread_mutex_unlock(&mutex);
        sem_wait(&clear);
        sem_post(&turn);

        /* Inspeciona o quarto quando todos sairem */
        if (canSearch == true)
            search();
        wait = 0;
    }

    /* Se o número de estudantes for 0, o Reitor simplesmente inspeciona o
     * quarto */
    else {
        wait = 1;
        search();
        wait = 0;
    }

    deanState = notInRoom;
    sync_printf(nStudents, deanState == inRoom, "Dean saiu do quarto.\n");
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void * studentAction() {
    pthread_mutex_lock(&mutex);

    /* Se o Reitor estiver no quarto, o Estudante espera que ele saia */
    if (deanState == inRoom) {
        pthread_mutex_unlock(&mutex);
        sem_wait(&turn);
        sem_post(&turn);
        pthread_mutex_lock(&mutex);
    }

    /* Estudante entra no quarto */
    nStudents += 1;
    sync_printf(nStudents, deanState == inRoom, "Estudante entrou no Quarto. Total: %d\n", nStudents);

    /* Se ele for o 10º Estudante a chegar, o Reitor (se estiver do lado de
     * fora) é avisado de que pode entrar (semáforo lieIn)... */
    if (nStudents == 10 && deanState == waiting)
        sem_post(&lieIn);
    else
        pthread_mutex_unlock(&mutex);

    /* ...senão, ele simplesmente entra e curte a festa por i segundos (a
     * thread dorme por i segundos, 5 <= i <= 30). */
    int random = (rand() % 26) + 5;
    party(random);

    /* Depois de curtir, o estudante vai embora */
    pthread_mutex_lock(&mutex);
    nStudents -= 1;
    sync_printf(nStudents, deanState == inRoom, "Estudante saiu do Quarto. Total: %d\n", nStudents);

    /* Se ele for o último estudante a sair e o Reitor estiver do lado de fora,
     * este é avisado de que pode entrar (semáforo lieIn).
     * Se ele for o último e o Reitor estiver do lado de dentro, este é avisado
     * de que pode inspecionar o quarto (semáforo clear).
     * Senão, tudo continua normalmente. */
    if (nStudents == 0 && deanState == waiting)
        sem_post(&lieIn);
    else if (nStudents == 0 && deanState == inRoom)
        sem_post(&clear);
    else
        pthread_mutex_unlock(&mutex);

    return NULL;
}
