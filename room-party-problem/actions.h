#include <stdio.h>
#include <unistd.h>

/* Variáveis de Estado */
int nStudents;                                        // Número de estudantes no quarto
int deanState;                                        // Estado do Reitor
enum deanStates {notInRoom = 0, inRoom, waiting};     // Possíveis estados

/**
 * function: party
 * desc: indica que a festa está acontecendo com nStudents estudantes
 *
 * @param: timeOnParty: inteiro (1 a 30)
                        tempo que a thread (Estudante) que chamou a função ficará
                        na festa (ou tempo que a thread dormirá enquanto na festa)
 * return: none
 **/
void party(int timeOnParty);

/**
 * function: breakup
 * desc: indica que a festa está sendo interrompida pelo Reitor
 *
 * @param: none
 * return: none
 **/
void breakup();

/**
 * function: search
 * desc: indica que o reitor está inspecionando o quarto
 *
 * @param: none
 * return: none
 **/
void search();
