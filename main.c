#include "header.h"

int main(int argc, char **argv){
    int* tasks;
    tasks = (int*) malloc(NUMBER_OF_TASKS * sizeof(int));
    FILE* file;
    file = fopen(argv[1],"rt");
    if(file != NULL){
    for(int i = 0; i < NUMBER_OF_TASKS; i++){
        fscanf(file,"%d",&tasks[i]);
    }


    if(tasks[0] == 1){
        
    }

    if(tasks[1] == 1){

    }

    if(tasks[2] == 1){

    }

    if(tasks[3] == 1){

    }

    if(tasks[4] == 1){

    }

    return 0;
}