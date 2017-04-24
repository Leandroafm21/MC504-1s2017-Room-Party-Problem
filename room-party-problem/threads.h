#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>
#include "actions.h"
#include "graphics.h"

/* Variaveis do Problema */
int minStudentsForBreakup, maxStudentsForSearch;

/* Protege os valores de nStudents e deanState, garantindo Exclusão Mútua */
pthread_mutex_t mutex;

/* Impede a entrada de alunos no quarto enquanto o Reitor estiver */
sem_t turn;

/* Sinaliza que o Reitor pode inspecionar o quarto */
sem_t clear;

/* Sinaliza que o Reitor (do lado de fora) pode entrar no quarto */
sem_t lieIn;

/* Impede que pessoas entrem na sala imediatamente após o Reitor sair */
int wait;

/**
 * function: deanAction
 * desc: representa a sequência de ações do Reitor
 *
 * @param: none
 * return: none
 **/
void * deanAction();

/**
 * function:
 * desc: representa a sequência de ações de um Estudante
 *
 * @param: none
 * return: none
 **/
void * studentAction();
