#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdarg.h>
#define MIN_ROOM_SIZE 8

pthread_mutex_t printf_mutex;

void drawRoom(int nStudents, int hasDean);
int getSideSize(int nStudents);
int sync_printf(const char *format, ...);
void graphics_init();
