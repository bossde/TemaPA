#include "header.h"

void Task1(char **argv, Team** TeamList){
    FILE* date;
    char c;
    int numberOfTeams, numberOfPlayers;
    Team* Auxiliar = NULL;
    char** TeamNames;
    Team* Element = (Team*) malloc(sizeof(Team));
    date = fopen(argv[2],"rt");
    FILE* output;
    output = fopen(argv[3],"wt");
    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);
        TeamNames = (char**) malloc(sizeof(char*) * numberOfTeams);
        for(int i = 0; i < numberOfTeams; i++)
        TeamNames[i] = (char*) malloc(NAMES_LENGHT);
        for(int i = 0; i < numberOfTeams; i++){
            fscanf(date,"%d", &numberOfPlayers);
            c = fgetc(date);
            Element->name = (char*) malloc(NAMES_LENGHT);
            fscanf(date, "%[^\r]", Element->name);
            strcpy(TeamNames[i],Element->name);
            free(Element->name);

            Element->Players = (PlayerArray*) malloc(numberOfPlayers * sizeof(PlayerArray));
            Auxiliar = Element;

            for(int j = 0; j < numberOfPlayers; j++){
                Auxiliar->Players[j].player.firstName = (char*) malloc(sizeof(char));
                Auxiliar->Players[j].player.secondName = (char*) malloc(sizeof(char));
                fscanf(date,"%s",Auxiliar->Players[j].player.firstName);
                fscanf(date,"%s",Auxiliar->Players[j].player.secondName);
                fscanf(date,"%d",&Auxiliar->Players[j].player.points);             
            }
            fprintf(date,"\n");
        }
    }


    if(output != NULL){
        for(int i = numberOfTeams - 1; i >= 0; i--){
            fprintf(output,"%s\n",TeamNames[i]);
        }
    }
    fclose(output);
    fclose(date);
}

void Task2(){

}

void Task3(){

}

void Task4(){

}

