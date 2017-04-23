#include "threads.h"

/* Número de iterações do Código */
#define N_ITERATIONS 100

int main(int argc, char *argv[]) {

    /* Inicialização dos semáforos */
    pthread_mutex_init(&mutex, NULL);
    sem_init(&turn, 0, 1);
    sem_init(&clear, 0, 0);
    sem_init(&lieIn, 0, 0);
    graphics_init();

    /* Declaracao das Threads do Reitor e dos Estudantes */
    pthread_t studentThread;
    pthread_t deanThread;

    /* Inicialização da variável random, que contará de quanto em quanto tempo
     * o Reitor chegará no quarto */
    srand(time(NULL));
    int random;

    wait = 0;
    /* Início da execução do problema */
    for (int i = 0; i < 50; ) {
        random = rand() % 31;

        /* Garante que o Reitor entra no quarto algumas vezes (média 1 a cada
         * 30 iteracoes), em todas as outras quem entra são os Estudantes */
        if (wait == 0) {
            if (random == 15 && deanState == notInRoom)
                pthread_create(&deanThread, NULL, deanAction, NULL);
            else
                pthread_create(&studentThread, NULL, studentAction, NULL);
            i++;
        }
        sleep(1);
    }

    /* Suspende a execução da thread do Reitor */
    pthread_join(deanThread, NULL);

    printf("Fim da festa! Todos saem do quarto.\n");

    return 0;
}
