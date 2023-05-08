#include "header.h"

void Task1(char **argv, Team** TeamList){
    FILE* date;
    int numberOfTeams;
    char** TeamNames;
    *TeamList = (Team*) malloc(sizeof(Team));
    Team* Element = (Team*) malloc(sizeof(Team));
    date = fopen(argv[2],"rt");
    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);
        TeamNames = (char**) malloc(sizeof(char*) * numberOfTeams);
        for(int i = 0; i < numberOfTeams; i++)
        TeamNames[i] = (char*) malloc(NAMES_LENGHT);
            fscanf(date,"%d", &Element->number_of_players);
            Element->name = (char*) malloc(NAMES_LENGHT);
            fscanf(date, "%[^\r]", Element->name);
            strcpy(TeamNames[i],Element->name);
            free(Element->name);
    }
    FILE* file;
    file = fopen(argv[3],"wt");
    if(file != NULL){
        fprintf(file,"%d\n",numberOfTeams);
        fprintf(file, "%d", Element->number_of_players);
        fprintf(file, "%s", TeamNames[0]);
    }
    fclose(file);
    fclose(date);
}

void Task2(){

}

void Task3(){

}

void Task4(){

}

