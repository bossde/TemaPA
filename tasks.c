#include "header.h"

void Task1(char **argv, Team** TeamList){
    FILE* date;
    int numberOfTeams;
    *(TeamList) = (Team*) malloc(sizeof(Team));
    date = fopen(argv[2],"rt");
    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);
    }

}

void Task2(){

}

void Task3(){

}

void Task4(){

}

