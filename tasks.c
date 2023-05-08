#include "header.h"

void Task1(char **argv, Team **TeamList){
    FILE* date;
    char c;
    int numberOfTeams, numberOfPlayers;

    date = fopen(argv[2],"rt");
    FILE* output;
    output = fopen(argv[3],"wt");

    if (date != NULL){
        fscanf(date,"%d", &numberOfTeams);

        for(int i = 0; i < numberOfTeams; i++){
            fscanf(date,"%d", &numberOfPlayers);
            c = fgetc(date);

            Team* Element = (Team*) malloc(sizeof(Team));
            Element->name = (char*) malloc(NAMES_LENGHT);
            Element->Players = (PlayerArray*) malloc(sizeof(PlayerArray));
            Element->nextTeam = NULL;

            fscanf(date, "%[^\r]", Element->name);

            PlayerArray* Auxiliar = Element->Players;
            for(int j = 0; j < numberOfPlayers; j++){
                Auxiliar->player.firstName = (char*) malloc(NAMES_LENGHT);
                Auxiliar->player.secondName = (char*) malloc(NAMES_LENGHT);
                fscanf(date,"%s",Auxiliar->player.firstName);
                fscanf(date,"%s",Auxiliar->player.secondName);
                fscanf(date,"%d",&Auxiliar->player.points); 

                if (j < numberOfPlayers - 1){
                    Auxiliar->next = (PlayerArray*) malloc(sizeof(PlayerArray));
                    Auxiliar = Auxiliar->next;
                } else {
                    Auxiliar->next = NULL;
                }
            }

            if (*TeamList == NULL){
                *TeamList = Element;
            } else {
                Team* Current = *TeamList;
                Element->nextTeam = Current;
                *TeamList = Element;
            }
        }

        PrintList(*TeamList,argv);
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
