#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>
#include "actions.h"
#include "graphics.h"

/* Protege os valores de nStudents e deanState, garantindo Exclusão Mútua */
sem_t mutex;

/* Impede a entrada de alunos no quarto enquanto o Reitor estiver */
sem_t turn;

/* Sinaliza que o Reitor pode inspecionar o quarto */
sem_t clear;

/* Sinaliza que o Reitor (do lado de fora) pode entrar no quarto */
sem_t lieIn;

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
