#include "graphics.h"

void drawRoom(int nStudents, int hasDean){
    int sideSize = getSideSize(nStudents) + 2;
    int studentCount = 0;

    printf("\n");

    for(int i = 0; i < sideSize; i++){
        for(int j = 0; j < sideSize; j++){
            if(j == 0 || j == sideSize - 1){
                if(i == 0 || i == sideSize - 1){
                    printf("+");
                }else{
                    printf("|");
                }
            }else if(i == 0 || i == sideSize - 1){
                if(hasDean && (i == sideSize - 1 && j == sideSize / 2)){
                    printf("D");
                }else{
                    printf("-");
                }
            }else{
                if(studentCount < nStudents){
                    printf("S");
                    studentCount++;
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }

    printf("\n");
}

int getSideSize(int nStudents){
    if(nStudents > MIN_ROOM_SIZE * MIN_ROOM_SIZE){
        for(int n = 1;; n++){
            if(n * n >= nStudents){
                return n;
            }
        }
    }else{
        return MIN_ROOM_SIZE;
    }
}
