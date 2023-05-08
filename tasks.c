#include "header.h"

void Task1(char **argv, Team** TeamList){
    FILE* date;
    int numberOfTeams;
    *TeamList = (Team*) malloc(sizeof(Team));
    Team* Element = (Team*) malloc(sizeof(Team));
    Team* AuxElem = NULL;
    date = fopen(argv[2],"rt");
    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);
        for(int i = 0; i < numberOfTeams; i++){
            Element->name = (char*) malloc(NAMES_LENGHT);
            fscanf(date, "%d", &Element->number_of_players);
            fscanf(date, "%s", Element->name);
            if(*TeamList == NULL){
                *TeamList = Element;
            }
            else{
                AuxElem = *TeamList;
                *TeamList = Element;
                (*TeamList)->nextTeam = AuxElem;
            }
        }
    }
    FILE* outputfile;
    outputfile = fopen(argv[3],"wt");
    if(outputfile != NULL){
        while(*TeamList){
            fprintf(outputfile,"%s\n",(*TeamList)->name);
        }
    }
    fclose(outputfile);
    fclose(date);
}

void Task2(){

}

void Task3(){

}

void Task4(){

}

